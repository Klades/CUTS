// $Id$

#include "TestLoggerClient_i.h"
#include "Logging_Client_Options.h"
#include "Test_Logger_Map.h"
#include "TestLoggerFactory_i.h"
#include "cuts/UUID.h"

//
// CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::
CUTS_TestLoggerClient_i (PortableServer::POA_ptr poa)
{
  // Construct the policy list for the TestLoggerFactory POA.
  CORBA::PolicyList policies (3);
  policies.length (3);

  policies[0] =
    poa->create_thread_policy (PortableServer::SINGLE_THREAD_MODEL);
  policies[1] =
    poa->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[2] =
    poa->create_servant_retention_policy (PortableServer::RETAIN);

  // Create the child POA for the test logger factory servants.
  PortableServer::POAManager_var mgr = poa->the_POAManager ();
  this->factory_poa_ = poa->create_POA ("TestLoggerFactory",
                                        mgr.in (),
                                        policies);

  // Destroy the POA policies
  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();
}

//
// ~CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::~CUTS_TestLoggerClient_i (void)
{
  //this->factory_poa_->destroy (1, 1);
}

//
// register_server
//
void CUTS_TestLoggerClient_i::
register_server (const CUTS::UUID & uid,
                 CUTS::TestLoggerServer_ptr server)
{
  // Extract the UUID from the object.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  // This is not a fast path implementation. Instead, we don't want
  // allocate memory and find out UUID has already been registered.
  if (this->map_.find (*uuid.to_string ()) == 0)
    throw CUTS::DuplicationRegistration ();

  // Create the logger factory for the test.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating logger factory for test %s\n",
              uuid.to_string ()->c_str ()));

  CUTS_TestLoggerFactory_i * servant = 0;

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLoggerFactory_i (uuid, server, this->factory_poa_.in ()),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestLoggerFactory_i> auto_clean (servant);

  // Activate the factory object.
  PortableServer::ObjectId_var oid =
    this->factory_poa_->activate_object (servant);

  // Save the node in the registration map.
  int retval = this->map_.bind (*uuid.to_string (), servant);

  if (retval == 0)
  {
    // Release the auto pointer.
    auto_clean.release ();
  }
  else if (retval == 1)
  {
    // This cause should never happen, but just in case it does.
    throw CUTS::DuplicationRegistration ();
  }
  else if (retval == -1)
  {
    // Internal error.
    throw CUTS::RegistrationFailed ();
  }
}

//
// unregister_server
//
void CUTS_TestLoggerClient_i::
unregister_server (const CUTS::UUID & uid, CUTS::TestLoggerServer_ptr server)
{
  // Extract the UUID from its binary form.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - unregistering server for test %s\n",
              uuid.to_string ()->c_str ()));

  // Locate the node in the registration.
  CUTS_Test_Logger_Map::ENTRY * entry = 0;
  int retval = this->map_.find (*uuid.to_string (), entry);

  if (retval == 0)
  {
    // Get the node from the entry.
    CUTS_TestLoggerFactory_i * servant = entry->item ();

    // Validate that the server is the same as the one passed into
    // the unregister () method.
    CUTS::TestLoggerServer_var s = servant->server ();

    if (s->_is_equivalent (server))
    {
      // Deactivate the servant.
      PortableServer::ObjectId_var oid =
        this->factory_poa_->servant_to_id (servant);

      this->factory_poa_->deactivate_object (oid.in ());

      // Remove the entry from the map.
      this->map_.unbind (entry);

      // Delete the servant.
      delete servant;
    }
    else
    {
      throw CUTS::RegistrationNotFound ();
    }
  }
  else
  {
    throw CUTS::RegistrationNotFound ();
  }
}

//
// find
//
CUTS::TestLoggerFactory_ptr
CUTS_TestLoggerClient_i::find (const CUTS::UUID & uid) const
{
  // Convert the UUID.
  ACE_Utils::UUID uuid;
  uid >>= uuid;

  // Find the servant object.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - locating factory for test %s\n",
              uuid.to_string ()->c_str ()));

  CUTS_TestLoggerFactory_i * servant = 0;
  int retval = this->map_.find (*uuid.to_string (), servant);

  if (retval == 0)
  {
    // Convert the servant to a reference.
    CORBA::Object_var obj =
      this->factory_poa_->servant_to_reference (servant);

    // Narrow the object to a factory.
    CUTS::TestLoggerFactory_var f = CUTS::TestLoggerFactory::_narrow (obj.in ());
    return f._retn ();
  }
  else
  {
    throw CUTS::RegistrationNotFound ();
  }
}

