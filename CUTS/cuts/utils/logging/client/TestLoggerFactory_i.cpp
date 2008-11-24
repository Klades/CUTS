// $Id$

#include "TestLoggerFactory_i.h"
#include "TestLogger_i.h"
#include "Logging_Client_Options.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/db/DB_Parameter.h"
#include "cuts/utils/db/DB_Parameter_List.h"
#include "cuts/utils/db/DB_Record.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Guard_T.h"
#include <sstream>

#if !defined (__CUTS_INLINE__)
#include "TestLoggerFactory_i.inl"
#endif

//
// CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::
CUTS_TestLoggerFactory_i (const ACE_Utils::UUID & test_uuid,
                          CUTS::TestLoggerServer_ptr server,
                          PortableServer::POA_ptr poa)
: test_uuid_ (test_uuid),
  log_count_ (0),
  default_POA_ (PortableServer::POA::_duplicate (poa)),
  server_ (CUTS::TestLoggerServer::_duplicate (server))
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i (const ACE_Utils::UUID &, PortableServer::POA_ptr)");

  // Construct the policy list for the TestLoggerFactory POA.
  CORBA::PolicyList policies (3);
  policies.length (3);

  policies[0] =
    poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);

  policies[1] =
    poa->create_id_assignment_policy (PortableServer::SYSTEM_ID);

  policies[2] =
    poa->create_servant_retention_policy (PortableServer::RETAIN);

  // Create the child POA for the test.
  std::ostringstream ostr;
  ostr << "TestLogger-" << this->test_uuid_.to_string ()->c_str ();

  PortableServer::POAManager_var mgr = poa->the_POAManager ();
  this->logger_POA_ = poa->create_POA (ostr.str ().c_str (),
                                       mgr.in (),
                                       policies);

  // Destroy the POA policies
  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// ~CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::~CUTS_TestLoggerFactory_i (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i::~CUTS_TestLoggerFactory_i (void)");
  this->logger_POA_->destroy (0, 0);
}

//
// create
//
CUTS::TestLogger_ptr CUTS_TestLoggerFactory_i::create (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i::create (void)");

  // Create a new TestLogger object and instantiate it under the
  // child POA provided in the constructor.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating a new logger for test %s\n",
              this->test_uuid_.to_string ()->c_str ()));

  CUTS_TestLogger_i * servant = 0;
  long logid = ++ this->log_count_;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLogger_i (logid, *this),
                    ::CORBA::NO_MEMORY ());

  PortableServer::ServantBase_var servant_base = servant;

  // Initialize the logger. This means, start its event loop so that
  // it can flush log messages.

  ACE_Time_Value timeout (CUTS_LOGGING_OPTIONS->timeout_);
  servant->start (timeout);

  // Activate the newly created logger servant.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating newly created logger for test %s\n",
              this->test_uuid_.to_string ()->c_str ()));

  PortableServer::ObjectId_var oid =
    this->logger_POA_->activate_object (servant);

  // Return ownership of the object to the client.
  CORBA::Object_var obj = this->logger_POA_->id_to_reference (oid);
  CUTS::TestLogger_var logger = CUTS::TestLogger::_narrow (obj.in ());
  return logger._retn ();
}

//
// destroy
//
void CUTS_TestLoggerFactory_i::destroy (CUTS::TestLogger_ptr ref)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i::destroy (CUTS::TestLogger_ptr)");

  PortableServer::ServantBase_var servant =
    this->logger_POA_->reference_to_servant (ref);

  CUTS_TestLogger_i * logger =
    dynamic_cast <CUTS_TestLogger_i *> (servant.in ());

  // Stop the logger. This will force it to release its resource and
  // flush its message queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - stopping a logger for test %s\n",
              this->test_uuid_.to_string ()->c_str ()));

  logger->stop ();
}

//
// _default_POA
//
PortableServer::POA_ptr CUTS_TestLoggerFactory_i::_default_POA (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i::_default_POA (void)");

  PortableServer::POA_var poa =
    PortableServer::POA::_duplicate (this->default_POA_.in ());

  return poa._retn ();
}
