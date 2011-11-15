// $Id$

#include "Test_Database.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Database.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "ace/CORBA_macros.h"
#include "ace/Date_Time.h"
#include "ace/UUID.h"
#include "adbc/SQLite/Types.h"
#include <sstream>

static const char * __CREATE_CUTS_TEST_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_test"
"("
"tid INTEGER PRIMARY KEY DEFAULT 1,"
"uuid CHAR(36),"
"name VARCHAR"
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
// init
//
void CUTS_Test_Database::init (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::init (void)");

  ADBC::SQLite::Connection * conn = 0;

  ACE_NEW_THROW_EX (conn,
                    ADBC::SQLite::Connection (),
                    ACE_bad_alloc ());

  this->conn_.reset (conn);
}

//
// create
//
bool CUTS_Test_Database::
create (const ACE_CString & location, ACE_Utils::UUID & uuid)
{
  long flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  bool retval = this->open_i (location, flags);

  if (retval)
  {
    // Instantiate a new query for the database.
    ADBC::SQLite::Query * query = this->conn_->create_query ();

    CUTS_Auto_Functor_T <ADBC::SQLite::Query>
      auto_release (query, &ADBC::SQLite::Query::destroy);

    // Create the default tables in the database.
    for (size_t i = 0; i < CREATE_TABLES_COUNT; ++ i)
      query->execute_no_record (__CREATE_TABLES__[i]);

    ACE_Utils::UUID curr_uuid;

    if (CUTS_Test_Database::get_test_uuid_i (*query, curr_uuid) == 0)
    {
      uuid = curr_uuid;
    }
    else
    {
      // Store the UUID in the database.
      const char * __sql_stmt__ =
        "INSERT INTO cuts_test (uuid) VALUES (?)";

      // Prepare the SQL statement.
      query->prepare (__sql_stmt__);

      const ACE_CString * uuidstr = uuid.to_string ();
      query->parameters ()[0].bind (uuidstr->c_str (), uuidstr->length ());

      // Execute the SQL statement.
      query->execute_no_record ();
    }
  }

  return retval;
}

//
// open
//
bool CUTS_Test_Database::open (const ACE_CString & location)
{
  return this->open_i (location, SQLITE_OPEN_READWRITE);
}

//
// open_i
//
bool CUTS_Test_Database::open_i (const ACE_CString & location, long flags)
{
  this->conn_->connect (location, flags);
  return this->conn_->is_connected ();
}

//
// start_new_test
//
void CUTS_Test_Database::start_new_test (const ACE_Time_Value & tv)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::start_new_test (void)");

  // Instantiate a new query for the database.
  ADBC::SQLite::Query * query = this->conn_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_release (query, &ADBC::SQLite::Query::destroy);

  const char * __sql_stmt__ =
    "INSERT INTO cuts_test_interval (start_time) VALUES (?)";

  query->prepare (__sql_stmt__);

  ACE_Date_Time temp (tv);
  ADBC::SQLite::Date_Time dt (temp);

  query->parameters ()[0].bind (&dt);
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
  ADBC::SQLite::Query * query = this->conn_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_release (query, &ADBC::SQLite::Query::destroy);

  const char * __sql_stmt__ =
    "UPDATE cuts_test_interval SET stop_time = ? WHERE tsid = ?";

  query->prepare (__sql_stmt__);

  ACE_Date_Time temp (tv);
  ADBC::SQLite::Date_Time dt;
  (temp);

  query->parameters ()[0].bind (&dt);
  query->parameters ()[1].bind (&this->active_id_);

  query->execute_no_record ();
}

//
// set_test_uuid
//
int CUTS_Test_Database::set_test_uuid (const ACE_Utils::UUID & uuid)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::set_test_uuid (const ACE_Utils::UUID &)");

  ADBC::SQLite::Query * query = this->conn_->create_query ();

  if (query == 0)
    return -1;

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_release (query, &ADBC::SQLite::Query::destroy);

  // Prepare the SQL statement.
  const char * __sql_stmt__ =
    "UPDATE cuts_test SET uuid = ? WHERE tid = 1";

  query->prepare (__sql_stmt__);

  const ACE_CString * struuid = uuid.to_string ();
  query->parameters ()[0].bind (struuid->c_str (), struuid->length ());

  // Write the UUID to the database.
  query->execute_no_record ();
  return 0;
}

//
// get_test_uuid_i
//
int CUTS_Test_Database::
get_test_uuid_i (ADBC::SQLite::Query & query, ACE_Utils::UUID & uuid)
{
  // Prepare the SQL statement.
  const char * __sql_stmt__ = "SELECT * FROM cuts_test WHERE tid = 1";
  query.prepare (__sql_stmt__);

  // Execute the SQL statement.
  ADBC::SQLite::Record & record = query.execute ();

  // Make sure there is at least one record.
  if (record.done ())
    return -1;

  char buffer[37];
  record.get_data (1, buffer, sizeof (buffer));

  // Convert the string into a UUID.
  uuid.from_string (buffer);
  return 0;
}

//
// get_test_profile
//
int CUTS_Test_Database::
get_test_profile (CUTS_Test_Profile & profile)
{
  // Instantiate a new query for the database.
  ADBC::SQLite::Query * query = this->conn_->create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query>
    auto_release (query, &ADBC::SQLite::Query::destroy);

  // Prepare the SQL statement.
  const char * __sql_stmt__ = "SELECT * FROM cuts_test WHERE tid = 1";
  query->prepare (__sql_stmt__);

  // Execute the SQL statement.
  ADBC::SQLite::Record & record = query->execute ();

  // Make sure there is at least one record.
  if (record.done ())
    return -1;

  char uuid[37];
  char name[256];

  record.get_data (1, uuid, sizeof (uuid));
  record.get_data (2, name, sizeof (name));

  // Save the data in the profile.
  profile.uuid_.from_string (uuid);
  profile.name_ = name;
  return 0;
}
