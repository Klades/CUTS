// $Id$

#include "TestLogger_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#include "TestLoggerFactory_i.h"
#include "cuts/utils/DB_Connection.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Parameter.h"
#include "cuts/utils/ODBC/ODBC_Types.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::CUTS_TestLogger_i (CUTS_TestLoggerFactory_i & parent)
  : parent_ (parent),
    lwm_msg_queue_ (25),
    hwm_msg_queue_ (50),
    msg_free_list_ (ACE_FREE_LIST_WITH_POOL, 
                    ACE_DEFAULT_FREE_LIST_PREALLOC,
                    hwm_msg_queue_)
{
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor, ACE_Reactor (), ACE_bad_alloc ());

  this->reactor (reactor);

  // Get the hostname of the logging client.
  char hostname[1024];
  ACE_OS::hostname (hostname, sizeof (hostname));
  ACE_INET_Addr inet ((u_short)0, hostname, AF_ANY);

}

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::~CUTS_TestLogger_i (void)
{
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  // Delete the reactor.
  delete reactor;
}

//
// log
//
void CUTS_TestLogger_i::log (CORBA::LongLong timestamp,
                             CORBA::Long severity,
                             const CUTS::MessageText & msg)
{
  try
  {
    // Create a new log message for the message.
    CUTS_Log_Message * message = this->msg_free_list_.remove ();

    if (message != 0)
    {
      // First, get the length of the string. This is necessary so we can
      // set the message's buffer size accordingly. This allocates more
      // memory for the text if it is needed.
      size_t length = msg.length ();
      message->text_.size (length + 1);

      // Copy the source text into the message's buffer.
      ACE_OS::memcpy (message->text_.begin (), msg.get_buffer (), length);
      message->text_[length] = '\0';

      // Initialize the remainder of the message.
      message->severity_ = severity;
      message->timestamp_ = static_cast <long> (timestamp);

      // Pass the message to the handler.
      this->handle_message (message);
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - message creation failed; dropping a message "
                  "for test %d\n",
                  this->parent_.test_number ()));
    }
  }
  catch (const ACE_bad_alloc & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s; dropping a message for test %d\n",
                ex.what (),
                this->parent_.test_number ()));

    throw CORBA::NO_MEMORY ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s; unknown exception occurred for test %d\n",
                this->parent_.test_number ()));
  }
}

//
// batch_log
//
void CUTS_TestLogger_i::batch_log (const CUTS::LogMessages & msgs)
{
  throw CORBA::NO_IMPLEMENT ();
}

//
// svc
//
int CUTS_TestLogger_i::svc (void)
{
  // Since this is a single threaded task, we have to let the reactor
  // know we are the owner. Otherwise, we will not be able to handle
  // the reactor's events, i.e., handle_event ();
  this->reactor ()->owner (ACE_OS::thr_self ());

  while (this->is_active_)
    this->reactor ()->handle_events ();

  return 0;
}

//
// handle_timeout
//
int CUTS_TestLogger_i::
handle_timeout (const ACE_Time_Value & current_time, const void * act)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - received timeout event to flush message queue for "
              "test %d\n",
              this->parent_.test_number ()));

  // Insert the messages into the database
  this->insert_messages_into_database ();

  return 0;
  ACE_UNUSED_ARG (current_time);
  ACE_UNUSED_ARG (act);
}

//
// handle_input
//
int CUTS_TestLogger_i::handle_input (ACE_HANDLE fd)
{
  // The READ_MASK event notification was sent. This means the log message
  // queue has surpassed its lower water mark. It is time to insert the
  // messages into the database.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - new message placed on test %d message queue\n",
              this->parent_.test_number ()));

  if (this->msg_queue ()->message_count () >= this->lwm_msg_queue_)
    this->insert_messages_into_database ();

  return 0;
  ACE_UNUSED_ARG (fd);
}

//
// handle_exception
//
int CUTS_TestLogger_i::handle_exception (ACE_HANDLE fd)
{
  // At this point, we are actually stoping the task. So, we need to
  // empty the contents of the message queue. We can make the assumption
  // the message queue has already been deactivated. Therefore, we just
  // need to iterate over the message queue and let the free list handle
  // deleting the actual message objects.
  ACE_ERROR ((LM_ERROR,
              "%T - %M - closing test %d; flushing message queue\n",
              this->parent_.test_number ()));

  MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();
  MESSAGE_QUEUE_EX::ITERATOR iter (*msg_queue);

  try
  {
    // Create a new database query.
    CUTS_DB_Query * query = this->parent_.connection ().create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - preparing insert statement for test %d\n",
                this->parent_.test_number ()));

    // Prepare the query for execution.
    const char * stmt = "CALL cuts.insert_log_message (?,?,?,?,?)";
    query->prepare (stmt);

    ACE_Time_Value tv;
    ACE_Date_Time date_time;
    ODBC_Date_Time timestamp;

    // Get the global/persitent information from the parent.
    long test_number = this->parent_.test_number ();

    // Initialize the persistant parameters of the statement.
    query->parameter (0)->bind (&test_number);
    query->parameter (1)->bind (this->hostname_, 0);
    query->parameter (2)->bind (&timestamp);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    size_t msg_count = this->msg_queue ()->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T - %M - inserting %d message(s) into database for test %d\n",
                msg_count,
                this->parent_.test_number ()));

    int retval;

    for ( ; !iter.done (); iter.advance ())
    {
      // Get the next message in the queue.
      retval = iter.next (msg);

      if (msg == 0)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - invalid message pointer\n"));
        }
      else if (retval == 1)
      {
        // Initialize the timestamp parameter.
        tv.msec (msg->timestamp_);
        date_time.update (tv);
        timestamp <<= date_time;

        // Bind the remaining parameters.
        query->parameter (3)->bind (&msg->severity_);
        query->parameter (4)->bind (msg->text_.begin (), 0);

        // Execute the query.
        query->execute_no_record ();

        // Place the message back on the free list.
        this->msg_free_list_.add (msg);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - already seen message for test %d; ignoring...\n",
                    this->parent_.test_number ()));
      }
    }

    // Flush the contents of the message queue.
    msg_queue->flush ();
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return 0;
  ACE_UNUSED_ARG (fd);
}

//
// start
//
int CUTS_TestLogger_i::start (const ACE_Time_Value & timeout)
{
  // Activate the message queue. This will ensure that we are receiving
  // messages from the driver thread.
  MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();

  if (msg_queue->state () != ACE_Message_Queue_Base::ACTIVATED)
    msg_queue->activate ();

  // Spawn a thread that will handle the reactor's events. Right now, we are
  // spawning 1 thread to handle all the events. This should suffice, but if
  // we are going to scale this, we will need a strategy for determining the
  // number of threads to spawn.
  this->is_active_ = true;

  int retval = this->activate ();

  if (retval == 0)
  {
    // Schedule the timeout interval for flushing the queue.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - setting timeout interval to %u second(s)\n",
                timeout.sec ()));

    this->timer_id_ =
      this->reactor ()->schedule_timer (this, 0, timeout, timeout);

    if (this->timer_id_ == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to start timer; test %d will not "
                  "periodically insert messages into the database\n",
                  this->parent_.test_number ()));
    }
  }
  else if (retval == -1)
  {
    this->is_active_ = false;
  }

  return retval;
}

//
// stop
//
int CUTS_TestLogger_i::stop (void)
{
  if (this->is_active_)
  {
    // Deactivate the message queue. This will ensure that no more message
    // are placed on the queue.
    MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - deactivating the message queue\n"));

    if (msg_queue->state () != ACE_Message_Queue_Base::DEACTIVATED)
      msg_queue->deactivate ();

    // Stop the timer for the reactor.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - canceling the timer for the logger\n"));

    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;

    // Signal the processing thread to stop and wait for the thread
    // to exit.

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - notifying the logger the shutdown\n"));

    this->is_active_ = false;
    this->reactor ()->notify (this);
    this->wait ();

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - test %d successfully released its resources\n",
                this->parent_.test_number ()));
  }

  return 0;
}

//
// insert_messages_into_database
//
int CUTS_TestLogger_i::insert_messages_into_database (void)
{
  try
  {
    // Create a new database query.
    CUTS_DB_Query * query = this->parent_.connection ().create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    // Prepare the query for execution.
    const char * stmt = "CALL cuts.insert_log_message (?,?,?,?,?)";
    query->prepare (stmt);

    ACE_Time_Value tv;
    ACE_Date_Time date_time;
    ODBC_Date_Time timestamp;

    // Get global information from the parent.
    long test_number = this->parent_.test_number ();

    // Initialize the persistant parameters of the statement.
    query->parameter (0)->bind (&test_number);
    query->parameter (1)->bind (this->hostname_, 0);
    query->parameter (2)->bind (&timestamp);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    size_t msg_count = this->msg_queue ()->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - inserting %d message(s) into database for test %d\n",
                msg_count,
                test_number));

    int retval;

    for ( ; msg_count > 0; -- msg_count)
    {
      // Get the next message at the head of the queue.
      retval = this->msg_queue ()->dequeue_head (msg);

      if (msg == 0)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T - %M - invalid message pointer\n"));
        }
      else if (retval != -1)
      {
        // Initialize the timestamp parameter.
        tv.msec (msg->timestamp_);
        date_time.update (tv);
        timestamp <<= date_time;

        // Bind the remaining parameters.
        query->parameter (3)->bind (&msg->severity_);
        query->parameter (4)->bind (msg->text_.begin (), 0);

        // Execute the query.
        query->execute_no_record ();

        // Place the message back on the free list.
        this->msg_free_list_.add (msg);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - failed to dequeue message for test %d\n",
                    test_number));
      }

      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - successfully inserted %d message(s) for"
                  "test %d\n",
                  msg_count,
                  test_number));
    }

    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}

//
// handle_message
//
int CUTS_TestLogger_i::handle_message (CUTS_Log_Message * msg)
{
  // Place the message on the queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - placing new message on queue for test %d\n",
              this->parent_.test_number ()));

  int retval = this->msg_queue ()->enqueue_tail (msg);

  if (retval >= static_cast <int> (this->lwm_msg_queue_))
  {
    // Since we have pass the lower watermark we need to notify the
    // database entry thread to clear the queue. Hopefully, this will
    // prevent us from allocating any more memory.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - message queue for test %d reached its limit\n",
                this->parent_.test_number ()));

    this->reactor ()->notify (this, ACE_Event_Handler::READ_MASK);
  }
  else if (retval == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to place message on the queue; dropping "
                "log message for test %d\n",
                this->parent_.test_number ()));

    // Place the message back on the free list.
    this->msg_free_list_.add (msg);
  }

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - test %d has %d log message(s) on its queue\n",
              this->parent_.test_number (),
              retval));

  return retval;
}

//
// destory
//
void CUTS_TestLogger_i::destroy (void)
{
  this->parent_.destroy (this);
}
