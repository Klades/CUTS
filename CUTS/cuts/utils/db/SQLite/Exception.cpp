// $Id$

#include "Exception.h"

//
// error_msgs_
//
const char * CUTS_DB_SQLite_Exception::error_msgs_[27] =
{
  "Successful result",
  "SQL error or missing database",
  "Internal logic error in SQLite",
  "Access permission denied",
  "Callback routine requested an abort",
  "The database file is locked",
  "A table in the database is locked",
  "A malloc () failed",
  "Attempt to write a readonly database",
  "Operation terminated by sqlite3_interrupt ()",
  "Some kind of disk I/O error occurred",
  "The database disk image is malformed",
  "NOT USED. Table or record not found",
  "Insertion failed because database is full",
  "Unable to open the database file",
  "NOT USED. Database lock protocol error",
  "Database is empty",
  "The database schema changed",
  "String or BLOB exceeds size limit",
  "Abort due to constraint violation",
  "Data type mismatch",
  "Library used incorrectly",
  "Uses OS features not supported on host",
  "Authorization denied",
  "Auxiliary database format error",
  "2nd parameter to sqlite3_bind out of range",
  "File opened that is not a database file"
};

//
// CUTS_DB_SQLite_Exception
//
CUTS_DB_SQLite_Exception::CUTS_DB_SQLite_Exception (void)
{

}

//
// CUTS_DB_SQLite_Exception
//
CUTS_DB_SQLite_Exception::CUTS_DB_SQLite_Exception (long err_code)
: CUTS_DB_Exception (err_code, "", "")
{
  if (err_code >= 0 && err_code <= 26)
    this->message_ = CUTS_DB_SQLite_Exception::error_msgs_[err_code];
  else
    this->message_ = "unknown error code";
}

//
// ~CUTS_DB_SQLite_Exception
//
CUTS_DB_SQLite_Exception::~CUTS_DB_SQLite_Exception (void)
{

}
