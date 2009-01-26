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

  // Initialize the logging server's database archive.
  CUTS_Test_Database & archive = this->test_app ()->test_db ();
  this->server_->archive (&archive);

  // Spawn a new instance of the server.
  return this->server_->spawn_main (argc, argv);
}

//
// fini
//
int CUTS_Test_Logging_Service::fini (void)
{
  // Shutdown the server. This actually destorys the ORB.
  // this->server_->shutdown ();
  return 0;
}
