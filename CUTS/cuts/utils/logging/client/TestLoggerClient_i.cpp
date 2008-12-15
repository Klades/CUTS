// $Id$

#include "TestLoggerClient_i.h"
#include "Logging_Client_Options.h"
#include "Test_Logger_Map.h"
#include "TestLoggerFactory_i.h"
#include "cuts/UUID.h"
#include "ace/Guard_T.h"
#include "ace/OS_NS_unistd.h"

//
// CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::
CUTS_TestLoggerClient_i (PortableServer::POA_ptr parent)
{
  // Construct the policy list for the TestLoggerFactory POA.
  CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::USER_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = parent->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA for the test logger factory servants.
  this->poa_ = parent->create_POA ("TestLoggerFactory",
                                   PortableServer::POAManager::_nil (),
                                   policies);

  // Activate the POA manager.
  PortableServer::POAManager_var mgr = this->poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// ~CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::~CUTS_TestLoggerClient_i (void)
{
  //this->poa_->destroy (1, 1);
}

//
// register_server
//
void CUTS_TestLoggerClient_i::
register_server (const CUTS::UUID & uid, CUTS::TestLoggerServer_ptr server)
{
  ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->lock_);

  // Extract the UUID from the object.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  // This is not a fast path implementation. Instead, we don't want
  // allocate memory and find out UUID has already been registered.
  if (this->tests_.find (uuid) == 0)
    throw CUTS::DuplicationRegistration ();

  // Create the logger factory for the test.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - registering test %s\n",
              uuid.to_string ()->c_str ()));

  CUTS_TestLoggerFactory_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLoggerFactory_i (uuid, server, this->poa_.in ()),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestLoggerFactory_i> auto_clean (servant);

  // Activate the servant and store the UUID. Do we really need to
  // store the UUID??
  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId (uuid.to_string ()->c_str ());

  this->poa_->activate_object_with_id (oid.in (), servant);
  this->tests_.insert (uuid);

  CORBA::String_var str = PortableServer::ObjectId_to_string (oid.in ());
  auto_clean.release ();
}

//
// unregister_server
//
void CUTS_TestLoggerClient_i::unregister_server (const CUTS::UUID & uid)
{
  ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->lock_);

  // Extract the UUID from its binary form.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  try
  {
    // Convert the UUID into an object id.
    PortableServer::ObjectId_var oid =
      PortableServer::string_to_ObjectId (uuid.to_string ()->c_str ());

    // Locate the servant with this object id.
    PortableServer::ServantBase_var servant =
      this->poa_->id_to_servant (oid.in ());

    // Deactivate the object.
    this->poa_->deactivate_object (oid);

    // Remove the UUID from the tests.
    this->tests_.remove (uuid);
  }
  catch (const PortableServer::POA::ObjectNotActive & ex)
  {
    ACE_ERROR ((LM_ERROR,
                 "%T (%t) - %M - %s\n",
                 ex._info ().c_str ()));

    throw CUTS::RegistrationNotFound ();
  }
}

//
// find
//
CUTS::TestLoggerFactory_ptr
CUTS_TestLoggerClient_i::find (const CUTS::UUID & uid) const
{
  ACE_READ_GUARD_RETURN (ACE_RW_Thread_Mutex,
                         guard,
                         this->lock_,
                         CUTS::TestLoggerFactory::_nil ());

  // Convert the UUID.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  // Find the servant object.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - locating factory for test %s\n",
              uuid.to_string ()->c_str ()));

  try
  {
    // Convert the UUID into an object reference.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - converting UUID into an object id\n"));

    PortableServer::ObjectId_var oid =
      PortableServer::string_to_ObjectId (uuid.to_string ()->c_str ());

    // Get a reference for the object id.
    CORBA::Object_var obj = this->poa_->id_to_reference (oid.in ());

    // Narrow the object to an factory object.
    CUTS::TestLoggerFactory_var factory =
      CUTS::TestLoggerFactory::_narrow (obj.in ());

    // Return the object to the client.
    return factory._retn ();
  }
  catch (const PortableServer::POA::ObjectNotActive &)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - test logger factory is not active [%s]\n",
                uuid.to_string ()->c_str ()));

    throw CUTS::RegistrationNotFound ();
  }
}

