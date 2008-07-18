// $Id$

#include "TestLoggerClient_i.h"
#include "TestLoggerFactory_i.h"
#include "Logging_Client_Options.h"
#include "ace/streams.h"
#include <sstream>

//
// CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::
CUTS_TestLoggerClient_i (PortableServer::POA_ptr root_poa)
: root_poa_ (PortableServer::POA::_duplicate (root_poa))
{

}

//
// ~CUTS_TestLoggerClient_i
//
CUTS_TestLoggerClient_i::~CUTS_TestLoggerClient_i (void)
{
  map_type::ITERATOR iter (this->factory_map_);

  for ( ; !iter.done (); iter.advance ())
    this->destroy_i (iter->item ());
}

//
// create
//
CUTS::TestLoggerFactory_ptr
CUTS_TestLoggerClient_i::create (CORBA::Long test_number)
{
  CUTS_TestLoggerFactory_i * servant = 0;
  PortableServer::POA_var test_poa;
  PortableServer::ObjectId_var oid;

  if (this->factory_map_.find (test_number, servant) == 0)
  {
    // Convert the servant into an object id. This is so we can get a reference
    // to the object later.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting the object id to factory for test %d\n",
                test_number));

    test_poa = servant->_default_POA ();
    oid = test_poa->servant_to_id (servant);
  }
  else
  {
    // Since we did not find the factory for the test, we need to create
    // a new one. We do not have to worry about race conditions since this
    // object can only be activated under a single-threaded POA. Therefore,
    // all client request are serialized.
    std::ostringstream ostr;
    ostr << "Test-" << test_number;

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - creating new POA with name %s\n",
                ostr.str ().c_str ()));

    // Create the thread policy for the child POA.
    PortableServer::ThreadPolicy_var threading =
      this->root_poa_->create_thread_policy (PortableServer::ORB_CTRL_MODEL);

    PortableServer::IdAssignmentPolicy_var assign =
      this->root_poa_->create_id_assignment_policy (PortableServer::SYSTEM_ID);

    PortableServer::ServantRetentionPolicy_var retention =
      this->root_poa_->create_servant_retention_policy (PortableServer::RETAIN);

    // Construct the policy list for the child POA.
    CORBA::PolicyList policies (3);
    policies.length (3);

    policies[0] =
      this->root_poa_->create_thread_policy (PortableServer::ORB_CTRL_MODEL);

    policies[1] =
      this->root_poa_->create_id_assignment_policy (PortableServer::SYSTEM_ID);

    policies[2] =
      this->root_poa_->create_servant_retention_policy (PortableServer::RETAIN);

    // Create the child POA for the test.
    test_poa =
      this->root_poa_->create_POA (ostr.str ().c_str (),
                                   PortableServer::POAManager::_nil (),
                                   policies);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying POA policies\n"));

    for (CORBA::ULong i = 0; i < policies.length (); ++ i)
      policies[i]->destroy ();

    // Get the newly created manager and activate it.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating manager for POA %s\n",
                ostr.str ().c_str ()));

    PortableServer::POAManager_var mgr = test_poa->the_POAManager ();
    mgr->activate ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - creating logger factory for test %d\n",
                test_number));

    ACE_NEW_THROW_EX (servant,
                      CUTS_TestLoggerFactory_i (*this,
                                                test_number,
                                                test_poa.in ()),
                      CORBA::NO_MEMORY ());

    ACE_Auto_Ptr <CUTS_TestLoggerFactory_i> auto_clean (servant);

    // Connect the factory to the datbase.
    servant->database (CUTS_LOGGING_OPTIONS->database_);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating factory object for test %d\n",
                test_number));

    oid = test_poa->activate_object (servant);

    if (this->factory_map_.bind (test_number, servant) == 0)
      {
        // Release the auto pointer since we stored the object.
        auto_clean.release ();
      }
    else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to store test logger factory for "
                    "test %d\n",
                    test_number));
      }
  }

  // Convert the object id to a reference.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - converting object id to factory reference\n"));

  CORBA::Object_var obj = test_poa->id_to_reference (oid.in ());

  CUTS::TestLoggerFactory_var factory =
    CUTS::TestLoggerFactory::_narrow (obj.in ());

  return factory._retn ();
}

//
// destroy
//
void CUTS_TestLoggerClient_i::destroy (CUTS_TestLoggerFactory_i * factory)
{
  map_type::ENTRY * entry;
  long test_number = factory->test_number ();

  if (this->factory_map_.find (test_number, entry) == 0)
  {
    this->destroy_i (factory);
    this->factory_map_.unbind (entry);
  }
  else
  {
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - logger factory for %d was not destroyed\n",
                test_number));
  }
}

//
// destroy_i
//
void CUTS_TestLoggerClient_i::destroy_i (CUTS_TestLoggerFactory_i * factory)
{
  // Get the object id for the servant.
  PortableServer::POA_var poa = factory->_default_POA ();
  PortableServer::ObjectId_var oid = poa->servant_to_id (factory);

  // Deactivate the object.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - deactivating logger factory for test %d\n",
              factory->test_number ()));

  poa->deactivate_object (oid);

  // Delete the object.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - removing logger factory for test %d from memory\n",
              factory->test_number ()));

  delete factory;
}
