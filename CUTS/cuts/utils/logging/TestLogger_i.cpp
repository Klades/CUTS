// $Id$

#include "TestLogger_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#include "TestLoggerFactory_i.h"
#include "cuts/utils/db/DB_Connection.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/db/DB_Parameter.h"
#include "cuts/utils/db/DB_Parameter_List.h"
#include "cuts/utils/db/ODBC/ODBC_Types.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/Time.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::CUTS_TestLogger_i (long logid, CUTS_TestLoggerFactory_i & parent)
  : logid_ (logid),
    parent_ (parent),
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

  inet.get_host_name (this->hostname_, MAXHOSTNAMELEN);

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - logger client's hostname : %s\n",
              this->hostname_));
}

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::~CUTS_TestLogger_i (void)
{
  ACE_Utils::UUID uuid = this->parent_.test_uuid ();

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - logger %d: deallocating logger for test %s (refcount: %d)\n",
              this->logid_,
              uuid.to_string ()->c_str (),
              this->_refcount_value ()));

  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  // Delete the reactor.
  delete reactor;
}

//
// log
//
void CUTS_TestLogger_i::log (const CUTS::TimeValue & tv,
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

      // Initialize the message structure.
      ACE_OS::memcpy (message->text_.begin (), msg.get_buffer (), length);
      message->text_[length] = '\0';
      message->severity_ = severity;
      message->timestamp_.set (tv.sec, tv.usec);

      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - logger %d received a message\n",
                  this->logid_));

      // Pass the message to the handler.
      this->handle_message (message);
    }
    else
    {
      ACE_Utils::UUID uuid = this->parent_.test_uuid ();

      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - logger %d: message creation failed; dropping a message "
                  "for test %s\n",
                  this->logid_,
                  uuid.to_string ()->c_str ()));
    }
  }
  catch (const ACE_bad_alloc & ex)
  {
    ACE_Utils::UUID uuid = this->parent_.test_uuid ();

    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - logger %d: dropping a message for test %s [%s]\n",
                this->logid_,
                uuid.to_string ()->c_str (),
                ex.what ()));

    throw CORBA::NO_MEMORY ();
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
  ACE_Utils::UUID uuid = this->parent_.test_uuid ();

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - logger %d: received timeout event to flush message queue for "
              "test %s\n",
              this->logid_,
              uuid.to_string ()->c_str ()));

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

  this->insert_messages_into_database ();

  return 0;
  ACE_UNUSED_ARG (fd);
}

//
// flush_messages_into_database
//
void CUTS_TestLogger_i::flush_messages_into_database (void)
{
  // At this point, we are actually stoping the task. So, we need to
  // empty the contents of the message queue. We can make the assumption
  // the message queue has already been deactivated. Therefore, we just
  // need to iterate over the message queue and let the free list handle
  // deleting the actual message objects.

  ACE_Utils::UUID uuid = this->parent_.test_uuid ();

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - logger %d: closing test %s; flushing message queue\n",
              this->logid_,
              uuid.to_string ()->c_str ()));

  try
  {
    // Get the test number for this test.
    ACE_INT32 test_number = this->parent_.test_number ();

    // Create a new database query.
    CUTS_DB_Query * query = this->parent_.connection ().create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    // Prepare the query for execution.
    const char * stmt = "CALL cuts.insert_log_message (?,?,?,?,?)";
    query->prepare (stmt);

    ACE_Date_Time date_time;
    ODBC_Date_Time timestamp;

    // Initialize the persistant parameters of the statement.
    query->parameters ()[0].bind (test_number);
    query->parameters ()[1].bind (this->hostname_, 0);
    query->parameters ()[2].bind (timestamp);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();
    size_t msg_count = msg_queue->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - logger %d: inserting %d message(s) into database\n",
                this->logid_,
                msg_count));

    int retval;

    MESSAGE_QUEUE_EX::ITERATOR iter (*msg_queue);

    for ( ; !iter.done (); iter.advance ())
    {
      // Get the next message in the queue.
      retval = iter.next (msg);

      if (msg == 0)
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - logger %d: invalid message pointer\n",
                    this->logid_));
      }
      else if (retval == 1)
      {
        // Initialize the timestamp parameter.
        date_time.update (msg->timestamp_);
        timestamp.set (date_time);

        // Bind the remaining parameters.
        query->parameters ()[3].bind (msg->severity_);
        query->parameters ()[4].bind (msg->text_.begin (), 0);

        // Execute the query.
        query->execute_no_record ();

        // Place the message back on the free list.
        this->msg_free_list_.add (msg);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - logger %d: already seen message; ignoring...\n",
                    this->logid_));
      }
    }

    // Flush the contents of the message queue.
    msg_queue->flush ();
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - logger %d: %s\n",
                this->logid_,
                ex.message ().c_str ()));
  }
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
                "%T (%t) - %M - logger %d: setting timeout interval to %u second(s)\n",
                this->logid_,
                timeout.sec ()));

    this->timer_id_ =
      this->reactor ()->schedule_timer (this, 0, timeout, timeout);

    if (this->timer_id_ == -1)
    {
      ACE_Utils::UUID uuid = this->parent_.test_uuid ();

      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - logger %d: failed to start timer; test %s will not "
                  "periodically insert messages into the database\n",
                  this->logid_,
                  uuid.to_string ()->c_str ()));
    }
  }
  else if (retval == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - logger %d: failed to activate test logger\n",
                this->logid_));

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
                "%T (%t) - %M - logger %d: deactivating the message queue\n",
                this->logid_));

    if (msg_queue->state () != ACE_Message_Queue_Base::DEACTIVATED)
      msg_queue->deactivate ();

    // Stop the timer for the reactor.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: canceling the timer for the logger\n",
                this->logid_));

    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;

    // Signal the processing thread to stop and wait for the thread
    // to exit.

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: notifying the logger the shutdown\n",
                this->logid_));

    this->is_active_ = false;
    this->reactor ()->notify (this, ACE_Event_Handler::EXCEPT_MASK);
    this->wait ();

    // Finally, flush the message queues to the database.
    this->flush_messages_into_database ();

    ACE_Utils::UUID uuid = this->parent_.test_uuid ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: test %d successfully released its resources\n",
                this->logid_,
                uuid.to_string ()->c_str ()));
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

    // Get the current test's number.
    ACE_UINT32 test_number = this->parent_.test_number ();

    ACE_Date_Time dt_temp;
    ODBC_Date_Time date_time;

    // Initialize the persistant parameters of the statement.
    query->parameters ()[0].bind (test_number);
    query->parameters ()[1].bind (this->hostname_, 0);
    query->parameters ()[2].bind (date_time);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    size_t msg_count = this->msg_queue ()->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - logger %d: inserting %d message(s) into database for test %d\n",
                this->logid_,
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
                      "%T - %M - logger %d: invalid message pointer\n",
                      this->logid_));
        }
      else if (retval != -1)
      {
        // Initialize the timestamp parameter.
        dt_temp.update (msg->timestamp_);
        date_time.set (dt_temp);

        // Bind the remaining parameters.
        query->parameters ()[3].bind (msg->severity_);
        query->parameters ()[4].bind (msg->text_.begin (), 0);

        // Execute the query.
        query->execute_no_record ();

        // Place the message back on the free list.
        this->msg_free_list_.add (msg);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - logger %d: failed to dequeue message for test %d "
                    "[state: %d]\n",
                    this->logid_,
                    test_number,
                    this->msg_queue ()->state ()));
      }
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: successfully inserted %d message(s) for "
                "test %d\n",
                this->logid_,
                msg_count,
                test_number));


    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - logger %d: %s\n",
                this->logid_,
                ex.message ().c_str ()));
  }

  return -1;
}

//
// handle_message
//
int CUTS_TestLogger_i::handle_message (CUTS_Log_Message * msg)
{
  // Place the message on the queue.
  int retval = this->msg_queue ()->enqueue_tail (msg);

  if (retval >= static_cast <int> (this->lwm_msg_queue_))
  {
    // Since we have pass the lower watermark we need to notify the
    // database entry thread to clear the queue. Hopefully, this will
    // prevent us from allocating any more memory.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: message queue has reached its limit\n",
                this->logid_));

    this->reactor ()->notify (this, ACE_Event_Handler::READ_MASK);
  }
  else if (retval == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - logger %d: failed to place message on the queue; dropping "
                "log message for test %d [%s]\n",
                this->logid_,
                msg->text_.begin ()));

    // Place the message back on the free list.
    this->msg_free_list_.add (msg);
  }

  if (retval != -1)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: test %d has %d log message(s) on its queue\n",
                this->logid_,
                this->parent_.test_number (),
                retval));
  }

  return retval;
}
