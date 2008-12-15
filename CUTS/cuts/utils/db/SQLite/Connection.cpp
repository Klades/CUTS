// $Id$

#include "Connection.h"
#include "Exception.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/CORBA_macros.h"
#include "sqlite3.h"

//
// CUTS_DB_SQLite_Connection
//
CUTS_DB_SQLite_Connection::CUTS_DB_SQLite_Connection (void)
: conn_ (0)
{

}

//
// ~CUTS_DB_SQLite_Connection
//
CUTS_DB_SQLite_Connection::~CUTS_DB_SQLite_Connection (void)
{
  this->disconnect ();
}

//
// connect
//
void CUTS_DB_SQLite_Connection::connect (const ACE_CString & connstr)
{
  long flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;

  this->connect (connstr, flags, 0);
}

//
// connect
//
void CUTS_DB_SQLite_Connection::
connect (const ACE_CString & connstr, long flags, const char * vfs)
{
  int retval = ::sqlite3_open_v2 (connstr.c_str (),
                                  &this->conn_,
                                  flags,
                                  vfs);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (*this);

  CUTS_DB_Connection::connect (connstr);
}

//
// disconnect
//
void CUTS_DB_SQLite_Connection::disconnect (void)
{
  if (this->conn_ != 0)
  {
    ::sqlite3_close (this->conn_);
    this->conn_ = 0;
  }
}

//
// create_query
//
CUTS_DB_SQLite_Query * CUTS_DB_SQLite_Connection::create_query (void)
{
  CUTS_DB_SQLite_Query * query = 0;

  ACE_NEW_THROW_EX (query,
                    CUTS_DB_SQLite_Query (*this),
                    ACE_bad_alloc ());

  return query;
}

//
// has_table
//
bool CUTS_DB_SQLite_Connection::has_table (const ACE_CString & tablename)
{
  // Instantiate a new query for the database.
  CUTS_DB_SQLite_Query * query = this->create_query ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Query>
    auto1 (query, &CUTS_DB_SQLite_Query::destroy);

  // Prepare the SQL statement.
  const char * __sql_stmt__ = "SELECT * FROM sqlite_master WHERE tbl_name = ?";
  query->prepare (__sql_stmt__);

  query->parameters ()[0].bind (tablename.c_str (), tablename.length ());

  // Execute the query and get the result
  CUTS_DB_SQLite_Record * record = query->execute ();

  CUTS_Auto_Functor_T <CUTS_DB_SQLite_Record>
    auto2 (record, &CUTS_DB_SQLite_Record::destroy);

  return !record->done ();
}
