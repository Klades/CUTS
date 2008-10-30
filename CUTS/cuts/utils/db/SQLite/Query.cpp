// $Id$

#include "Query.h"
#include "Connection.h"
#include "ace/CORBA_macros.h"

//
// CUTS_DB_SQLite_Query
//
CUTS_DB_SQLite_Query::
CUTS_DB_SQLite_Query (CUTS_DB_SQLite_Connection & parent)
: parent_ (parent),
  stmt_ (0),
  needs_reseting_ (false)
{

}

//
// ~CUTS_DB_SQLite_Query
//
CUTS_DB_SQLite_Query::~CUTS_DB_SQLite_Query (void)
{
  if (this->stmt_ != 0)
    this->finalize ();
}

//
// prepare
//
void CUTS_DB_SQLite_Query::prepare (const char * query)
{
  size_t len = ACE_OS::strlen (query);
  this->prepare (query, len);
}

//
// prepare
//
void CUTS_DB_SQLite_Query::prepare (const char * query, size_t len)
{
  if (this->stmt_ != 0)
    this->finalize ();

  const char * tail = 0;

  int retval = ::sqlite3_prepare_v2 (this->parent_.conn_,
                                     query,
                                     len,
                                     &this->stmt_,
                                     &tail);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (retval);
}

//
// destroy
//
void CUTS_DB_SQLite_Query::destroy (void)
{
  delete this;
}

//
// execute_no_record
//
void CUTS_DB_SQLite_Query::execute_no_record (const char * query)
{
  this->prepare (query);
  this->execute_no_record ();
}

//
// execute_no_record
//
void CUTS_DB_SQLite_Query::execute_no_record (void)
{
  if (this->stmt_ == 0)
    throw CUTS_DB_SQLite_Exception (SQLITE_ERROR);

  if (this->needs_reseting_)
    this->reset ();

  // Execute the SQL statement.
  int retval = ::sqlite3_step (this->stmt_);
  this->needs_reseting_ = true;

  if (retval != SQLITE_DONE)
    throw CUTS_DB_SQLite_Exception (retval);
}

//
// execute
//
CUTS_DB_SQLite_Record * CUTS_DB_SQLite_Query::execute (const char * query)
{
  this->prepare (query);
  return this->execute ();
}

//
// execute
//
CUTS_DB_SQLite_Record * CUTS_DB_SQLite_Query::execute (void)
{
  if (this->stmt_ == 0)
    throw CUTS_DB_SQLite_Exception (SQLITE_ERROR);

  if (this->needs_reseting_)
    this->reset ();

  CUTS_DB_SQLite_Record * record = 0;

  ACE_NEW_THROW_EX (record,
                    CUTS_DB_SQLite_Record (*this),
                    ACE_bad_alloc ());

  this->needs_reseting_ = true;
  return record;
}

//
// cancel
//
void CUTS_DB_SQLite_Query::cancel (void)
{
  // no-op
}

//
// last_insert_id
//
long CUTS_DB_SQLite_Query::last_insert_id (void)
{
  return static_cast <long> (::sqlite3_last_insert_rowid (this->parent_.conn_));
}

//
// parameter
//
CUTS_DB_Parameter * CUTS_DB_SQLite_Query::parameter (size_t index)
{
  return 0;
}

//
// parameter_count
//
size_t CUTS_DB_SQLite_Query::parameter_count (void) const
{
  return 0;
}

//
// finalize
//
void CUTS_DB_SQLite_Query::finalize (void)
{
  // Release the statements resources.
  ::sqlite3_finalize (this->stmt_);

  // Reset the variables.
  this->stmt_ = 0;
  this->needs_reseting_ = false;
}

//
// reset
//
void CUTS_DB_SQLite_Query::reset (void)
{
  ::sqlite3_reset (this->stmt_);
  this->needs_reseting_ = false;
}
