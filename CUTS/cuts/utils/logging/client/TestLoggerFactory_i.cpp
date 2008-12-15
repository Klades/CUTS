// $Id$

#include "TestLoggerFactory_i.h"
#include "TestLogger_i.h"
#include "Logging_Client_Options.h"
#include "cuts/Auto_Functor_T.h"
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
CUTS_TestLoggerFactory_i (const ACE_Utils::UUID & uuid,
                          CUTS::TestLoggerServer_ptr server,
                          PortableServer::POA_ptr poa)
: uuid_ (uuid),
  next_log_id_ (0),
  server_ (CUTS::TestLoggerServer::_duplicate (server))
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i (const ACE_Utils::UUID &, PortableServer::POA_ptr)");

  // Construct the policy list for the TestLoggerFactory POA.
  CORBA::PolicyList policies (3);
  policies.length (3);

  policies[0] = poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = poa->create_id_assignment_policy (PortableServer::USER_ID);
  policies[2] = poa->create_servant_retention_policy (PortableServer::RETAIN);

  // Create the child POA for the test.
  std::ostringstream ostr;
  ostr << "TestLogger-" << this->uuid_.to_string ()->c_str ();

  this->poa_ = poa->create_POA (ostr.str ().c_str (),
                                PortableServer::POAManager::_nil (),
                                policies);

  PortableServer::POAManager_var mgr = this->poa_->the_POAManager ();
  mgr->activate ();

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
  //this->poa_->destroy (0, 0);
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
              this->uuid_.to_string ()->c_str ()));

  long logid = this->next_log_id_ ++;

  CUTS_TestLogger_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLogger_i (logid, *this),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestLogger_i> auto_clean (servant);

  // Construct the object id for this logger.
  std::ostringstream ostr;
  ostr << "Logger-" << logid;

  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId (ostr.str ().c_str ());

  // Activate the object using the constructed object id.
  this->poa_->activate_object_with_id (oid.in (), servant);
  auto_clean.release ();

  // Return ownership of the object to the client.
  CORBA::Object_var obj = this->poa_->id_to_reference (oid);
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
    this->poa_->reference_to_servant (ref);

  CUTS_TestLogger_i * logger =
    dynamic_cast <CUTS_TestLogger_i *> (servant.in ());

  // Stop the logger. This will force it to release its resource and
  // flush its message queue.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - stopping a logger for test %s\n",
              this->uuid_.to_string ()->c_str ()));

  // Deactivate the object.
  std::ostringstream ostr;
  ostr << "Logger-" << logger->id ();

  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId (ostr.str ().c_str ());
  this->poa_->deactivate_object (oid.in ());
}
