// $Id$

#include "Logger_Task.h"

#if !defined (__CUTS_INLINE__)
#include "Logger_Task.inl"
#endif

#include "LoggingClient_i.h"
#include "cuts/UUID.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Reactor.h"

#define ACE_LOG_MESSAGE_BUFFER_SIZE 50

//
// CUTS_Logger_Task
//
CUTS_Logger_Task::CUTS_Logger_Task (void)
: index_ (0)
{
  // Initialize the reactor for the task.
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    ACE_bad_alloc ());

  this->reactor (reactor);

  // Setup the hostname for the packets.
  char hostname[1024];
  ACE_OS::hostname (hostname, sizeof (hostname));
  this->packets_[0].hostname = ::CORBA::string_dup (hostname);
  this->packets_[1].hostname = ::CORBA::string_dup (hostname);

  // Setup the message length for the buffers.
  this->packets_[0].msgs.length (ACE_LOG_MESSAGE_BUFFER_SIZE);
  this->packets_[0].msgs.length (0);

  this->packets_[1].msgs.length (ACE_LOG_MESSAGE_BUFFER_SIZE);
  this->packets_[1].msgs.length (0);

  // Setup the double buffers.
  this->buffers_.first (&this->packets_[0]);
  this->buffers_.second (&this->packets_[1]);
}

//
// ~CUTS_Logger_Task
//
CUTS_Logger_Task::~CUTS_Logger_Task (void)
{
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  delete reactor;
}

//
// handle_log_message
//
int CUTS_Logger_Task::
handle_log_message (const ACE_Utils::UUID & uuid, const ::CUTS::LogMessage & msg)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->swap_mutex_, -1);
  size_t index = this->index_ ++;

  ::CUTS::LogMessagePacket * packet = this->buffers_.first ();
  this->insert_message (packet->msgs[index], uuid, msg);

  if (this->index_ != ACE_LOG_MESSAGE_BUFFER_SIZE)
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - buffer contains %d message(s)\n"),
                this->index_));

    this->buffers_.first ()->msgs.length (this->index_);
  }
  else
  {
    // Reset the index.
    this->index_ = 0;

    // Swap the buffers.
    std::swap (this->buffers_.first (), this->buffers_.second ());
    this->buffers_.first ()->msgs.length (this->index_);

    // Force notification.
    this->reactor ()->notify (this, ACE_Event_Handler::READ_MASK);
  }

  return 0;
}


//
// handle_log_message
//
void CUTS_Logger_Task::
insert_message (::CUTS::TestLogMessage & test_logmsg,
                const ACE_Utils::UUID & uuid,
                const ::CUTS::LogMessage & msg)
{
  test_logmsg.uuid <<= uuid;
  this->copy_message (test_logmsg.logmsg, msg);
}

//
// copy_message
//
void CUTS_Logger_Task::
copy_message (::CUTS::LogMessage & dst, const ::CUTS::LogMessage & src)
{
  // Copy the timestamp of the message.
  dst.timestamp.sec = src.timestamp.sec;
  dst.timestamp.usec = src.timestamp.usec;

  // Copy the severity of the message.
  dst.severity = src.severity;

  // Copy the actual test of the message.
  dst.message.length (src.message.length ());
  ACE_OS::memcpy (dst.message.get_buffer (),
                  src.message.get_buffer (),
                  src.message.length ());
}

//
// svc
//
int CUTS_Logger_Task::svc (void)
{
  try
  {
    // Set the owner of the reactor.
    this->reactor ()->owner (ACE_OS::thr_self ());

    // Run the reactor's event loop.
    int retval = this->reactor ()->run_reactor_event_loop ();

    if (0 != retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to run reactor event loop\n")));

    // Send the final events to the server. Right now this is
    // not thread safe. We need to add a thread mutex to prevent
    // multiple threads from sending the same buffer, or a corrupted
    // buffer to the logging server.
    this->send_message_packet (*this->buffers_.first ());
    return 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception in service routine\n")));
  }

  return -1;
}

//
// handle_input
//
int CUTS_Logger_Task::handle_input (ACE_HANDLE)
{
  try
  {
    this->send_message_packet (*this->buffers_.second ());
  }
  catch (const ::CORBA::TRANSIENT &)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - connection to logging server does not exist\n")));
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return 0;
}

//
// send_message_packet
//
void CUTS_Logger_Task::
send_message_packet (const ::CUTS::LogMessagePacket & packet)
{
  if (!::CORBA::is_nil (this->server_.in ()))
  {
    // Send the log message packet to the server.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - sending %d messages to server\n"),
                packet.msgs.length ()));

    this->server_->handle_messages (packet);
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - connection to logging server does not exist\n")));
}

//
// init
//
int CUTS_Logger_Task::init (::CORBA::ORB_ptr orb)
{
  // Save the ORB.
  this->orb_ = ::CORBA::ORB::_duplicate (orb);

  // Resolve the logging server.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - resolving LoggingServer\n")));

  ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("LoggingServer");

  if (::CORBA::is_nil (obj.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve LoggingServer")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - extracting LoggingServer from reference\n")));

  this->server_ = ::CUTS::LoggingServer::_narrow (obj.in ());

  if (::CORBA::is_nil (this->server_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - object is not a CUTS::LoggingServer")),
                       -1);

  return 0;
}
