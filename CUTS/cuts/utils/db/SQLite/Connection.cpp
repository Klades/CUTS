// $Id$

#include "Connection.h"
#include "Exception.h"
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
