// $Id$

#include "Test_Logging_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Logging_Service.inl"
#endif

#include "Test_Logging_Callback.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/testing/Testing_App.h"
#include "cuts/utils/db/DB_Query.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Test_Logging_Service, _make_CUTS_Test_Logging_Service);

static const char * __CREATE_CUTS_LOGGING_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_logging"
"("
"lid INTEGER PRIMARY KEY AUTOINCREMENT,"
"timeofday DATETIME,"
"severity INTEGER,"
"hostname VARCHAR,"
"message TEXT"
")";

static const char * __CREATE_INDEX_CUTS_LOGGING_MESSAGE__ =
"CREATE INDEX IF NOT EXISTS cuts_logging_message ON cuts_logging (message)";

#define INIT_STMT_COUNT 2

static const char * __INIT_STMTS__[INIT_STMT_COUNT] =
{
  __CREATE_CUTS_LOGGING_TABLE__,
  __CREATE_INDEX_CUTS_LOGGING_MESSAGE__
};

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
                    ACE_bad_alloc ());

  this->server_.reset (server);

  // Install the callback object for the server. This will insert log
  // messages into the database for the test.
  CUTS_Test_Logging_Callback * callback = 0;

  ACE_NEW_THROW_EX (callback,
                    CUTS_Test_Logging_Callback (this->test_app ()->test_db ()),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Test_Logging_Callback> auto_clean (callback);

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

  try
  {
    // Try to create the logging table in the database.
    CUTS_DB_Query * query = this->test_app ()->test_db ()->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - initializing CUTS logging data table(s)\n"));

    for (size_t i = 0; i < INIT_STMT_COUNT; ++ i)
      query->execute_no_record (__INIT_STMTS__[i]);
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  // Spawn a new instance of the server. ;-)
  this->server_->uuid (this->test_app ()->options ().uuid_);
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
