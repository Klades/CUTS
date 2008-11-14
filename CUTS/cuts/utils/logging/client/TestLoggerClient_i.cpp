// $Id$

#include "TestLoggerClient_i.h"
#include "TestLoggerFactory_i.h"
#include "Logging_Client_Options.h"
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

  policies[0] = poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = poa->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[2] = poa->create_servant_retention_policy (PortableServer::RETAIN);

  // Create the child POA for the test.
  PortableServer::POAManager_var mgr = poa->the_POAManager ();

  this->factory_poa_ =
    poa->create_POA ("TestLoggerFactory", mgr.in (), policies);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - destroying POA policies\n"));

  for (CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();

  // Get the POAManager for the newly created POA and activate it. Otherwise,
  // the factory will not be able to receive any calls.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating TestLoggerFactory POA\n"));
}

//
// ~CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::~CUTS_TestLoggerClient_i (void)
{
  this->factory_poa_->destroy (true, true);
}

//
// create
//
CUTS::TestLoggerFactory_ptr
CUTS_TestLoggerClient_i::create (const CUTS::UUID & uuid)
{
  // Extract the UUID from the object.
  ACE_Utils::UUID test_uuid;
  uuid >>= test_uuid;

  // First, let's try to located the object in the factory map. If we
  // find it for the specified test, then we can just return. Since this
  // is object is activated under the RootPOA, we know that it is
  // not multi-threaded and is void of race conditions.

  ACE_CString uuid_str = *test_uuid.to_string ();
  CUTS_TestLoggerFactory_i * servant = 0;

  if (this->factory_map_.find (uuid_str, servant) == 0)
    return servant->_this ();

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - creating logger factory for test %s\n",
              uuid_str.c_str ()));

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLoggerFactory_i (test_uuid,
                                              this->factory_poa_.in ()),
                    CORBA::NO_MEMORY ());

  PortableServer::ServantBase_var safety = servant;

  if (this->factory_map_.bind (*test_uuid.to_string (), servant) != 0)
    throw CUTS::FactoryOperationFailed ();

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating logger factory\n"));

  // Activate the newly created object and return it to the caller.
  PortableServer::ObjectId_var oid =
    this->factory_poa_->activate_object (servant);

  CORBA::Object_var obj = this->factory_poa_->id_to_reference (oid);
  CUTS::TestLoggerFactory_var factory =
    CUTS::TestLoggerFactory::_narrow (obj.in ());

  return factory._retn ();
}

//
// destroy
//
void CUTS_TestLoggerClient_i::
destroy (CUTS::TestLoggerFactory_ptr factory)
{
  // Convert the reference into a servant.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - releasing reference to test logger factory\n"));

  PortableServer::ServantBase_var servant_base =
    this->factory_poa_->reference_to_servant (factory);

  // Cast the generic servant to a factory servant.
  CUTS_TestLoggerFactory_i * servant =
    dynamic_cast <CUTS_TestLoggerFactory_i *> (servant_base.in ());

  if (servant != 0)
  {
    // Get the test number for the factory and located it.
    ACE_Utils::UUID uuid = servant->test_uuid ();
    ACE_CString uuid_str = *uuid.to_string ();

    if (servant->_refcount_value () == 1)
    {
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - all references to test logger factory for "
                  "test %s released; removing the test logger factory\n",
                  uuid_str.c_str ()));

      this->factory_map_.unbind (uuid_str);
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - servant is not a CUTS_TestLoggerFactory_i"
                " object\n"));
  }
}
