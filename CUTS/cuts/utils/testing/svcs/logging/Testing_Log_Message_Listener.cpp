// $Id$

#include "Testing_Log_Message_Listener.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Log_Message_Listener.inl"
#endif

#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/testing/Testing_App.h"
#include "cuts/UUID.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Testing_Log_Message_Listener, _make_CUTS_Testing_Log_Message_Listener);

//
// init
//
int CUTS_Testing_Log_Message_Listener::init (int argc, char * argv [])
{
  try
  {
    // Initialize the testing service.
    if (CUTS_TAO_Testing_Service::init (argc, argv) == -1)
      return -1;

    // Resolve the RootPOA.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA\n")),
                         -1);

    ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (root_poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - reference is not a PortableServer::POA")),
                         -1);

    // Activate the POA manager.
    ::PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
    mgr->activate ();

    // Initialiaze the servant.
    this->servant_->init (&this->test_app ()->test_db ());
    this->servant_.activate (root_poa.in ());

    // Activate the ORB's task.
    this->orb_task_.reset (this->orb_.in ());
    this->orb_task_.activate ();

    // Resolve the LoggingServer initial reference.
    obj = this->orb_->resolve_initial_references ("LoggingServer");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve LoggerServer ")
                         ACE_TEXT ("initial reference\n")),
                         -1);

    // Extract the logging server from the generic reference.
    this->logging_server_ = ::CUTS::LoggingServer::_narrow (obj.in ());

    if (::CORBA::is_nil (this->logging_server_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - reference is not a CUTS::LoggingServer")),
                         -1);

    // Get the UUID of the current test.
    CUTS_Test_Profile profile;
    this->test_app ()->test_db ().get_test_profile (profile);

    ::CUTS::UUID test_uuid;
    test_uuid <<= profile.uuid_;

    // Register the listener with the logging server.
    obj = this->servant_.get_reference ();
    ::CUTS::LoggingServerListener_var listener = ::CUTS::LoggingServerListener::_narrow (obj.in ());
    this->cookie_ = this->logging_server_->register_listener (test_uuid, listener);

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// fini
//
int CUTS_Testing_Log_Message_Listener::fini (void)
{
  try
  {
    // Get the UUID of the current test.
    CUTS_Test_Profile profile;
    this->test_app ()->test_db ().get_test_profile (profile);

    ::CUTS::UUID test_uuid;
    test_uuid <<= profile.uuid_;

    // Unregister the listener with the logging server.
    this->logging_server_->unregister_listener (test_uuid, this->cookie_.in ());

    // Deactivate the servant, then shutdown the ORB.
    this->servant_.deactivate ();
    this->orb_->shutdown ();

    // Pass control to the base class.
    CUTS_TAO_Testing_Service::fini ();

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}
