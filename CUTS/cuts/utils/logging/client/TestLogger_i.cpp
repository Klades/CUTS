// $Id$

#include "TestLogger_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#include "TestLoggerFactory_i.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"
#include <algorithm>

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::CUTS_TestLogger_i (long logid, CUTS_TestLoggerFactory_i & parent)
  : task_type (0, &log_msg_queue_1_),
    logid_ (logid),
    parent_ (parent),
    lwm_msg_queue_ (25),
    hwm_msg_queue_ (50),
    msg_free_list_ (ACE_FREE_LIST_WITH_POOL,
                    ACE_DEFAULT_FREE_LIST_PREALLOC,
                    hwm_msg_queue_),
    old_msg_queue_ (&log_msg_queue_2_)
{
  // Initialize the reactor for the logger.
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    CORBA::NO_MEMORY ());

  this->reactor (reactor);

  // Get the hostname of the logging client.
  char hostname[1024];
  ACE_OS::hostname (hostname, sizeof (hostname));
  ACE_INET_Addr inet ((u_short)0, hostname, AF_ANY);

  inet.get_host_name (this->hostname_, MAXHOSTNAMELEN);
}

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::~CUTS_TestLogger_i (void)
{
  ACE_Utils::UUID uuid = this->parent_.test_uuid ();

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
// send_messages
//
void CUTS_TestLogger_i::send_messages (void)
{
  do
  {
    // Replace the message queues.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - swapping the message queues\n"));

    ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->swap_mutex_);
    std::swap (this->msg_queue_, this->old_msg_queue_);
  } while (0);

  // Create an iterator for the message queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - sending %d message(s) in old queue to server\n",
              this->old_msg_queue_->message_count ()));

  CUTS_Log_Message * log_msg = 0;
  MESSAGE_QUEUE_EX::ITERATOR iter (*this->old_msg_queue_);

  for (; !iter.done (); iter.advance ())
  {
    // Get the next log message.
    iter.next (log_msg);

    if (log_msg != 0)
    {
      // Send the message to the server.

      // Insert the log message back onto the free list.
      this->msg_free_list_.add (log_msg);
    }
  }

  // Empty the contents of the old message queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - flushing contents of old queue\n"));
  this->old_msg_queue_->flush ();
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

    // Finally, flush the message queues.
    this->send_messages ();

    ACE_Utils::UUID uuid = this->parent_.test_uuid ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: test %d successfully released its resources\n",
                this->logid_,
                uuid.to_string ()->c_str ()));
  }

  return 0;
}

//
// handle_message
//
int CUTS_TestLogger_i::handle_message (CUTS_Log_Message * msg)
{
  // Place the message on the queue.
  int retval;

  do
  {
    ACE_READ_GUARD_RETURN (ACE_RW_Thread_Mutex,
                           guard,
                           this->swap_mutex_,
                           -1);

    retval = this->msg_queue ()->enqueue_tail (msg);
  } while (0);

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
                "%T (%t) - %M - logger %d has %d log message(s) on its queue\n",
                this->logid_,
                retval));
  }

  return retval;
}
