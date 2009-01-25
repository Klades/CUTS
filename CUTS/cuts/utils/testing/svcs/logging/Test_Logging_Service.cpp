// $Id$

#include "Test_Logging_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Logging_Service.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/logging/server/callbacks/testing/Test_Logging_Callback.h"
#include "cuts/utils/testing/Testing_App.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Test_Logging_Service, _make_CUTS_Test_Logging_Service);

//
// CUTS_Test_Logging_Service
//
CUTS_Test_Logging_Service::CUTS_Test_Logging_Service (void)
{

}

//
// CUTS_Test_Logging_Service
//
CUTS_Test_Logging_Service::~CUTS_Test_Logging_Service (void)
{

}

//
// init
//
int CUTS_Test_Logging_Service::init (int argc, char * argv [])
{
  if (CUTS_TAO_Testing_Service::init (argc, argv) == -1)
    return -1;

  // Instantiate a new server object. Make sure we place it
  // under the ORB in this service.
  CUTS_Test_Logging_Server * server = 0;

  ACE_NEW_THROW_EX (server,
                    CUTS_Test_Logging_Server (this->orb_.in ()),
                    CORBA::NO_MEMORY ());

  this->server_.reset (server);

  // Install the callback object for the server. This will insert log
  // messages into the database for the test.
  CUTS_Test_Logging_Callback * callback = 0;

  ACE_NEW_THROW_EX (callback,
                    CUTS_Test_Logging_Callback (this->test_app ()->test_db ()),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_Test_Logging_Callback> auto_clean (callback);

  if (callback->init () == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to initialize callback\n"),
                       -1);
  }

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - installing main callback object\n"));

  int retval = this->server_->install_callback (callback);

  if (retval == 0)
  {
    auto_clean.release ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to install main callback object; "
                "log messages with not be saved to database\n"));
  }

  // Spawn a new instance of the server.
  CUTS_Test_Database & archive = this->test_app ()->test_db ();
  this->server_->archive (&archive);

  return this->server_->spawn_main (argc, argv);
}

//
// fini
//
int CUTS_Test_Logging_Service::fini (void)
{
  // Shutdown the server. This actually destorys the ORB.
  this->server_->shutdown ();
  return 0;
}
