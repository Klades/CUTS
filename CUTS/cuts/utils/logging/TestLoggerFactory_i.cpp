// $Id$

#include "TestLoggerFactory_i.h"
#include "TestLogger_i.h"
#include "Logging_Client_Options.h"
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
CUTS_TestLoggerFactory_i (long test_number, PortableServer::POA_ptr poa)
: test_number_ (test_number),
  log_count_ (0),
  default_POA_ (PortableServer::POA::_duplicate (poa))
{
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
  ostr << "TestLogger-" << this->test_number_;

  PortableServer::POAManager_var mgr = poa->the_POAManager ();

  this->logger_POA_ =
    poa->create_POA (ostr.str ().c_str (), mgr.in (), policies);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - destroying POA policies\n"));

  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();

  // Get the POAManager for the newly created POA and activate it. Otherwise,
  // the factory will not be able to receive any calls.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating POAManager for %s\n",
              ostr.str ().c_str ()));
}

//
// ~CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::~CUTS_TestLoggerFactory_i (void)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - destroying logger POA for test %d\n",
              this->test_number_));

  this->logger_POA_->destroy (true, true);
}

//
// create
//
CUTS::TestLogger_ptr CUTS_TestLoggerFactory_i::create (void)
{
  // Create a new TestLogger object and instantiate it under the
  // child POA provided in the constructor.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating a new logger for test %d\n",
              this->test_number_));

  CUTS_TestLogger_i * servant = 0;
  long logid = ++ this->log_count_;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLogger_i (logid, *this),
                    CORBA::NO_MEMORY ());

  PortableServer::ServantBase_var servant_base = servant;

  // Initialize the logger. This means, start its event loop so that
  // it can flush log messages.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - initializing new logger for test %d\n",
              this->test_number_));

  ACE_Time_Value timeout (CUTS_LOGGING_OPTIONS->timeout_);
  servant->start (timeout);

  // Activate the newly created logger servant.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating newly created logger for test %d\n",
              this->test_number_));

  PortableServer::ObjectId_var oid =
    this->logger_POA_->activate_object (servant);

  // Return ownership of the object to the client.
  CORBA::Object_var obj = this->logger_POA_->id_to_reference (oid);
  CUTS::TestLogger_var logger = CUTS::TestLogger::_narrow (obj.in ());
  return logger._retn ();
}

//
// database
//
void CUTS_TestLoggerFactory_i::connect (const ACE_CString & server_addr)
{
  try
  {
    // Establish a connection with the database.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - connecting to database on '%s'\n",
                server_addr.c_str ()));

    this->conn_.connect (CUTS_USERNAME,
                         CUTS_PASSWORD,
                         server_addr.c_str ());
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s; failed to connect to '%s'\n",
                ex.message ().c_str (),
                server_addr.c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception; failed to connect to "
                "database on %s\n",
                server_addr.c_str ()));
  }
}

//
// destroy
//
void CUTS_TestLoggerFactory_i::destroy (CUTS::TestLogger_ptr ref)
{
  PortableServer::ServantBase_var servant =
    this->logger_POA_->reference_to_servant (ref);

  CUTS_TestLogger_i * logger =
    dynamic_cast <CUTS_TestLogger_i *> (servant.in ());

  // Stop the logger. This will force it to release its resource and
  // flush its message queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - stopping a logger for test %d\n",
              this->test_number_));

  logger->stop ();
}

//
// _default_POA
//
PortableServer::POA_ptr CUTS_TestLoggerFactory_i::_default_POA (void)
{
  PortableServer::POA_var poa =
    PortableServer::POA::_duplicate (this->default_POA_.in ());

  return poa._retn ();
}
