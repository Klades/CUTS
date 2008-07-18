// $Id$

#include "TestLoggerClient_i.h"
#include "TestLoggerFactory_i.h"
#include "Logging_Client_Options.h"
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
                "%M (%t) - %T - getting the object id to factory for test %d\n",
                test_number));

    test_poa = servant->poa ();
    oid = test_poa->servant_to_id (servant);
  }
  else
  {
    // Since we did not find the factory for the test, we need to create
    // a new one. We do not have to worry about race conditions since this
    // object can only be activated under a single-threaded POA. Therefore,
    // all client request are serialized.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - create a POA for test %d\n",
                test_number));

    std::ostringstream ostr;
    ostr << "Test-" << test_number;

    // Create the thread policy for the child POA.
    PortableServer::ThreadPolicy_var thread_policy =
      this->root_poa_->create_thread_policy (PortableServer::ORB_CTRL_MODEL);

    // Construct the policy list for the child POA.
    CORBA::PolicyList policies (1);
    policies.length (1);
    policies[0] = thread_policy.in ();

    // Create the child POA for the test.
    test_poa =
      this->root_poa_->create_POA (ostr.str ().c_str (),
                                   PortableServer::POAManager::_nil (),
                                   policies);

    // Destroy the thread policy.
    thread_policy->destroy ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - create a test logger factory for test %d\n",
                test_number));

    ACE_NEW_THROW_EX (servant,
                      CUTS_TestLoggerFactory_i (test_number, test_poa),
                      CORBA::NO_MEMORY ());

    ACE_Auto_Ptr <CUTS_TestLoggerFactory_i> auto_clean (servant);

    if (this->factory_map_.bind (test_number, servant) == 0)
    {
      // Release the auto pointer since we stored the object.
      auto_clean.release ();

      // Connect the factory to the database.
      servant->database (CUTS_LOGGING_OPTIONS->database_);

      // Activate the object under it's test-specific POA.
      oid = test_poa->activate_object (servant);
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

  // Extract the test logger factory object from the reference.
  CUTS::TestLoggerFactory_var factory =
    CUTS::TestLoggerFactory::_narrow (obj.in ());

  return factory._retn ();
}
