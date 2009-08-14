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
  this->hostname_ = hostname;
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
handle_log_messages (const ACE_Utils::UUID & uuid,
                     const ::CUTS::LogMessages & msgs)
{
  ::CUTS::UUID test_uuid;
  test_uuid <<= uuid;

  this->server_->send_messages (this->hostname_.c_str (),
                                test_uuid,
                                msgs);
  return 0;
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
                       ACE_TEXT ("%T (%t) - %M - failed to resolve LoggingServer\n")),
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
