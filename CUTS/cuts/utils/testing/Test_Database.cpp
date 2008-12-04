// $Id$

#include "Test_Database.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Database.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/SQLite/Query.h"
#include "cuts/utils/db/SQLite/Types.h"
#include "ace/CORBA_macros.h"
#include "ace/UUID.h"
#include "ace/Env_Value_T.h"
#include <sstream>

static const char * __CREATE_CUTS_TEST_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_test"
"("
"uuid CHAR(36) PRIMARY KEY,"
"name VARCHAR,"
"UNIQUE (uuid)"
")";

static const char * __CREATE_CUTS_TEST_SCHED_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_test_interval"
"("
"tsid INTEGER PRIMARY KEY AUTOINCREMENT, "
"start_time DATETIME, "
"stop_time DATETIME"
")";

#define CREATE_TABLES_COUNT 2

static const char * __CREATE_TABLES__[CREATE_TABLES_COUNT] =
{
  __CREATE_CUTS_TEST_TABLE__,
  __CREATE_CUTS_TEST_SCHED_TABLE__
};

//
// CUTS_Test_Database
//
CUTS_Test_Database::CUTS_Test_Database (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::CUTS_Test_Database (void)");

  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream ostr;
  ostr << CUTS_ROOT << "/etc/tests";

  this->outdir_ = ostr.str ().c_str ();

  // Finish the initialization.
  this->init ();
}

//
// ~CUTS_Test_Database
//
CUTS_Test_Database::~CUTS_Test_Database (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::~CUTS_Test_Database (void)");
}

//
// init
//
void CUTS_Test_Database::init (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::init (void)");

  CUTS_DB_SQLite_Connection * conn = 0;

  ACE_NEW_THROW_EX (conn,
                    CUTS_DB_SQLite_Connection (),
                    ACE_bad_alloc ());

  this->conn_.reset (conn);
}

//
// create
//
bool CUTS_Test_Database::create (const ACE_Utils::UUID & uuid)
{
  bool retval = this->open (uuid);

  if (retval)
  {
    // Instantiate a new query for the database.
    CUTS_DB_SQLite_Query * query = this->conn_->create_query ();

    CUTS_Auto_Functor_T <
      CUTS_DB_SQLite_Query>
      auto_release (query, &CUTS_DB_SQLite_Query::destroy);

    // Create the default tables in the database.
    for (size_t i = 0; i < CREATE_TABLES_COUNT; ++ i)
      query->execute_no_record (__CREATE_TABLES__[i]);
  }

  return retval;
}

//
// open
//
bool CUTS_Test_Database::open (const ACE_Utils::UUID & uuid)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::open (const ACE_Utils::UUID &)");

  // Construct the location of the database.
  ACE_Utils::UUID temp (uuid);

  std::ostringstream ostr;
  ostr << this->outdir_ << ACE_TEXT ("/")
       << temp.to_string ()->c_str () << ACE_TEXT (".cdb");

  // Connect to the database.
  this->conn_->connect (ostr.str ().c_str ());
  return this->conn_->is_connected ();
}

//
// start_new_test
//
void CUTS_Test_Database::start_new_test (const ACE_Time_Value & tv)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::start_new_test (void)");

  // Instantiate a new query for the database.
  CUTS_DB_SQLite_Query * query = this->conn_->create_query ();

  CUTS_Auto_Functor_T <
    CUTS_DB_SQLite_Query>
    auto_release (query, &CUTS_DB_SQLite_Query::destroy);

  const char * __sql_stmt__ =
    "INSERT INTO cuts_test_interval (start_time) VALUES (?)";

  query->prepare (__sql_stmt__);

  ACE_Date_Time temp (tv);
  CUTS_DB_SQLite_Date_Time dt (temp);

  query->parameters ()[0].bind (dt);
  query->execute_no_record ();

  // Save the id of the active test run.
  this->active_id_ = query->last_insert_id ();
}

//
// start_new_test
//
void CUTS_Test_Database::stop_current_test (const ACE_Time_Value & tv)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::stop_current_test (void)");

  // Instantiate a new query for the database.
  CUTS_DB_SQLite_Query * query = this->conn_->create_query ();

  CUTS_Auto_Functor_T <
    CUTS_DB_SQLite_Query>
    auto_release (query, &CUTS_DB_SQLite_Query::destroy);

  const char * __sql_stmt__ =
    "UPDATE cuts_test_interval SET stop_time = ? WHERE tsid = ?";

  query->prepare (__sql_stmt__);

  ACE_Date_Time temp (tv);
  CUTS_DB_SQLite_Date_Time dt;
  (temp);

  query->parameters ()[0].bind (dt);
  query->parameters ()[1].bind (this->active_id_);

  query->execute_no_record ();
}
