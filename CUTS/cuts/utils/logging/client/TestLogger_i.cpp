// $Id$

#include "TestLogger_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#include "TestLoggerFactory_i.h"
#include "TestLoggerServer_Singleton.h"
#include "cuts/UUID.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/Reactor.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"
#include <algorithm>

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::CUTS_TestLogger_i (long logid,
                                      CUTS_TestLoggerFactory_i & parent,
                                      size_t msg_queue_size)
  : logid_ (logid),
    parent_ (parent),
    is_active_ (false),
    msg_queue_size_ (msg_queue_size),
    timer_id_ (-1),
    active_log_ (msg_logs_),
    inactive_log_ (msg_logs_ + 1)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::CUTS_TestLogger_i (long, CUTS_TestLoggerFactory_i &, size_t)");

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

  // Initialize the constant portions of the packet.
  this->packet_.hostname = CORBA::string_dup (hostname);
  this->packet_.uuid <<= this->parent_.test_uuid ();
}

//
// CUTS_TestLogger_i
//
CUTS_TestLogger_i::~CUTS_TestLogger_i (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::~CUTS_TestLogger_i (void)");

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
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::log (const CUTS::TimeValue &, CORBA::Long, const CUTS::MessageText &)");

  // Just in case we overflow the size of the message log, lets
  // prevent the cleanup thread from swapping the log message buffer.
  ACE_READ_GUARD (ACE_RW_Thread_Mutex, guard, this->swap_mutex_);

  // Get the next record in the active message log.
  msg_log_type::pointer log_msg;
  size_t used_size = this->active_log_->next_free_record (log_msg);

  // Copy the elements into the log message.
  log_msg->timestamp.sec  = tv.sec;
  log_msg->timestamp.usec = tv.usec;
  log_msg->severity = severity;

  // Resize the message buffer.
  CORBA::Long length = msg.length ();
  log_msg->message.length (length);

  // Copy the contents of the message.
  ACE_OS::memcpy (log_msg->message.get_buffer (),
                  msg.get_buffer (),
                  length);

  // Only allow one thread to invoke this
  if (used_size == this->msg_queue_size_)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - signaling cleanup thread to empty queue\n"));

    this->reactor ()->notify (this, ACE_Event_Handler::READ_MASK);
  }
}

//
// handle_input
//
int CUTS_TestLogger_i::handle_input (ACE_HANDLE)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::handle_input (ACE_HANDLE)");

  // Reset timeout interval so we don't prematurely send data to server.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - reseting timeout interval\n"));

  this->reactor ()->reset_timer_interval (this->timer_id_, this->timeout_);

  // Send the messages to the server.
  this->send_messages ();
  return 0;
}

//
// handle_exception
//
int CUTS_TestLogger_i::handle_exception (ACE_HANDLE)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::handle_exception (ACE_HANDLE)");

  if (this->timer_id_ != -1)
  {
    // Cancel the timer.
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;
  }

  // Flush the message queue.
  this->send_messages ();
  return 0;
}

//
// batch_log
//
void CUTS_TestLogger_i::batch_log (const CUTS::LogMessages & msgs)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::batch_log (const CUTS::LogMessages &)");

  throw CORBA::NO_IMPLEMENT ();
}

//
// svc
//
int CUTS_TestLogger_i::svc (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::svc (void)");

  // Since this is a single threaded task, we have to let the reactor
  // know we are the owner. Otherwise, we will not be able to handle
  // the reactor's events, i.e., handle_event ();
  this->reactor ()->owner (ACE_OS::thr_self ());

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - waiting for reactor events\n"));

  while (this->is_active_)
    this->reactor ()->handle_events ();

  return 0;
}

//
// send_messages
//
void CUTS_TestLogger_i::send_messages (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::send_messages (void)");

  do
  {
    // Replace the message queues.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - swapping the message queues\n"));

    ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->swap_mutex_);
    std::swap (this->active_log_, this->inactive_log_);
  } while (0);

  // Get the size of the message log.
  size_t used_size = this->inactive_log_->used_size ();

  if (used_size == 0)
    return;

  try
  {
    // Resize the message buffer accordingly.
    this->packet_.messages.length (used_size);

    // Get a fast iterator to the message log.
    msg_log_type::iterator iter (*this->inactive_log_);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - sending %d message(s) in old message"
                " log server\n",
                used_size));

    // Get a pointer to the packet's log message buffer.
    CUTS::LogMessages::
      value_type * ptr = this->packet_.messages.get_buffer ();

    for (; !iter.done (); iter.advance ())
      this->copy_message (*ptr ++, *iter);

    // Get a reference to the server.
    CUTS::TestLoggerServer_var server = CUTS_TESTLOGGERSERVER->get ();

    if (!CORBA::is_nil (server.in ()))
    {
      // Send the packet to the server.
      server->send_message_packet (this->packet_);
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - server connection does not exist; "
                  "dropping messages\n"));
    }

    // Empty the contents of the old message queue.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - flushing contents of old message log\n"));

    this->inactive_log_->reset_no_lock ();
  }
  catch (const CORBA::TRANSIENT & )
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - reseting the test logger singleton\n"));

    CUTS_TESTLOGGERSERVER->reset ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// start
//
int CUTS_TestLogger_i::start (const ACE_Time_Value & timeout)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::start (const ACE_Time_Value &)");

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

    if (this->timer_id_ != -1)
    {
      // Save the timeout value.
      this->timeout_ = timeout;
    }
    else
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
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::stop (void)");

  if (this->is_active_)
  {
    // Signal processing thread to stop and wait for it to return.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - notifying logger to shutdown\n"));

    this->is_active_ = false;
    this->reactor ()->notify (this, ACE_Event_Handler::EXCEPT_MASK);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - waiting for logger task to return\n"));
    this->wait ();

    ACE_Utils::UUID uuid = this->parent_.test_uuid ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - logger %d: test %d successfully released its resources\n",
                this->logid_,
                uuid.to_string ()->c_str ()));
  }

  return 0;
}

//
// copy_message
//
void CUTS_TestLogger_i::copy_message (CUTS::LogMessage & dst,
                                      const CUTS::LogMessage & src)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLogger_i::copy_message (CUTS::LogMessage &, const CUTS::LogMessage &)");

  // Copy the elements into the log message.
  dst.timestamp.sec  = src.timestamp.sec;
  dst.timestamp.usec = src.timestamp.usec;
  dst.severity = src.severity;

  // Resize the message buffer.
  CORBA::Long length = src.message.length ();
  dst.message.length (length);

  // Copy the contents of the message.
  ACE_OS::memcpy (dst.message.get_buffer (),
                  src.message.get_buffer (),
                  length);
}
