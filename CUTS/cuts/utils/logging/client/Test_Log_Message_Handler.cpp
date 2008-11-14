// $Id$

#include "Test_Log_Message_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Log_Message_Handler.inl"
#endif

#include "cuts/utils/DB_Connection.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Parameter.h"
#include "cuts/utils/ODBC/ODBC_Types.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/Reactor.h"

//
// CUTS_Test_Log_Message_Handler
//
CUTS_Test_Log_Message_Handler::
CUTS_Test_Log_Message_Handler (CUTS_DB_Connection & conn,
                               long test_number,
                               const char * hostname,
                               size_t lwm_msg_queue,
                               size_t hwm_msg_queue)
: ACE_Refcountable_T <ACE_RW_Thread_Mutex> (1),
  conn_ (conn),
  test_number_ (test_number),
  hostname_ (hostname),
  timer_id_ (-1),
  lwm_msg_queue_ (lwm_msg_queue),
  hwm_msg_queue_ (hwm_msg_queue),
  msg_free_list_ (ACE_FREE_LIST_WITH_POOL,
                  lwm_msg_queue,
                  lwm_msg_queue,
                  hwm_msg_queue)
{
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor, ACE_Reactor (), ACE_bad_alloc ());
  this->reactor (reactor);
}

//
// ~CUTS_Test_Log_Message_Handler
//
CUTS_Test_Log_Message_Handler::~CUTS_Test_Log_Message_Handler (void)
{
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  // Delete the reactor.
  delete reactor;
}

//
// svc
//
int CUTS_Test_Log_Message_Handler::svc (void)
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
int CUTS_Test_Log_Message_Handler::
handle_timeout (const ACE_Time_Value & current_time, const void * act)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - received timeout event to flush message queue for "
              "test %d\n",
              this->test_number_));

  // Insert the messages into the database
  this->insert_messages_into_database ();

  return 0;
  ACE_UNUSED_ARG (current_time);
  ACE_UNUSED_ARG (act);
}

//
// handle_input
//
int CUTS_Test_Log_Message_Handler::handle_input (ACE_HANDLE fd)
{
  // The READ_MASK event notification was sent. This means the log message
  // queue has surpassed its lower water mark. It is time to insert the
  // messages into the database.
  this->insert_messages_into_database ();

  return 0;
  ACE_UNUSED_ARG (fd);
}

//
// handle_exception
//
int CUTS_Test_Log_Message_Handler::handle_exception (ACE_HANDLE fd)
{
  // At this point, we are actually stoping the task. So, we need to
  // empty the contents of the message queue. We can make the assumption
  // the message queue has already been deactivated. Therefore, we just
  // need to iterate over the message queue and let the free list handle
  // deleting the actual message objects.
  ACE_ERROR ((LM_ERROR,
              "%T - %M - closing test %d; flushing message queue\n",
              this->test_number_));

  MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();
  MESSAGE_QUEUE_EX::ITERATOR iter (*msg_queue);

  try
  {
    // Create a new database query.
    CUTS_DB_Query * query = this->conn_.create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - preparing insert statement for test %d\n",
                this->test_number_));

    // Prepare the query for execution.
    const char * stmt = "CALL cuts.insert_log_message (?,?,?,?,?)";
    query->prepare (stmt);

    ACE_Time_Value tv;
    ACE_Date_Time date_time;
    ODBC_Date_Time timestamp;

    // Initialize the persistant parameters of the statement.
    query->parameter (0)->bind (&this->test_number_);
    query->parameter (1)->bind (const_cast <char *> (this->hostname_), 0);
    query->parameter (2)->bind (&timestamp);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    size_t msg_count = this->msg_queue ()->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T - %M - inserting %d message(s) into database for test %d\n",
                msg_count,
                this->test_number_));

    int retval;

    for ( ; !iter.done (); iter.advance ())
    {
      // Get the next message in the queue.
      retval = iter.next (msg);

      if (retval == 1)
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
                    this->test_number_));
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
int CUTS_Test_Log_Message_Handler::start (const ACE_Time_Value & timeout)
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
                  this->test_number_));
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
int CUTS_Test_Log_Message_Handler::stop (void)
{
  if (this->is_active_)
  {
    // Toggle the active state of the object.
    this->is_active_ = false;

    // Deactivate the message queue. This will ensure that no more message
    // are placed on the queue.
    MESSAGE_QUEUE_EX * msg_queue = this->msg_queue ();

    if (msg_queue->state () != ACE_Message_Queue_Base::DEACTIVATED)
      msg_queue->deactivate ();

    // Stop the timer for the reactor.
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;

    // Signal the processing thread to stop and wait for the thread
    // to exit.
    this->reactor ()->notify (this);
    this->wait ();

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - test %d successfully released its resources\n",
                this->test_number_));
  }

  return 0;
}

//
// insert_messages_into_database
//
int CUTS_Test_Log_Message_Handler::insert_messages_into_database (void)
{
  try
  {
    // Create a new database query.
    CUTS_DB_Query * query = this->conn_.create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - preparing insert statement for test %d\n",
                this->test_number_));

    // Prepare the query for execution.
    const char * stmt = "CALL cuts.insert_log_message (?,?,?,?,?)";
    query->prepare (stmt);

    ACE_Time_Value tv;
    ACE_Date_Time date_time;
    ODBC_Date_Time timestamp;

    // Initialize the persistant parameters of the statement.
    query->parameter (0)->bind (&this->test_number_);
    query->parameter (1)->bind (const_cast <char *> (this->hostname_), 0);
    query->parameter (2)->bind (&timestamp);

    // Determine how many messages we are going to dump into the database. If
    // the max_count == 0, then we are going to dump all that we have
    size_t msg_count = this->msg_queue ()->message_count ();

    CUTS_Log_Message * msg = 0;

    ACE_DEBUG ((LM_INFO,
                "%T - %M - inserting %d message(s) into database for test %d\n",
                msg_count,
                this->test_number_));

    int retval;

    for ( ; msg_count > 0; -- msg_count)
    {
      // Get the next message at the head of the queue.
      retval = this->msg_queue ()->dequeue_head (msg);

      if (retval != -1)
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
                    this->test_number_));
      }
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
int CUTS_Test_Log_Message_Handler::handle_message (CUTS_Log_Message * msg)
{
  // Place the message on the queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - placing new message on queue for test %d\n",
              this->test_number_));

  int retval = this->msg_queue ()->enqueue_tail (msg);

  if (retval >= static_cast <int> (this->lwm_msg_queue_))
  {
    // Since we have pass the lower watermark we need to notify the
    // database entry thread to clear the queue. Hopefully, this will
    // prevent us from allocating any more memory.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - message queue for test %d reached its limit\n",
                this->test_number_));

    this->reactor ()->notify (this, ACE_Event_Handler::READ_MASK);
  }
  else if (retval == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to place message on the queue; dropping "
                "log message for test %d\n",
                this->test_number_));

    // Place the message back on the free list.
    this->msg_free_list_.add (msg);
  }

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - test %d has %d log message(s) on its queue\n",
              this->test_number_,
              retval));
  return retval;
}

