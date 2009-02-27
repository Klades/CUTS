// $Id$

#include "Parameter.h"

#if !defined (__CUTS_INLINE__)
#include "Parameter.inl"
#endif

#include "Exception.h"
#include "Query.h"
#include "Types.h"
#include "sqlite3.h"
#include <sstream>

//
// null
//
void CUTS_DB_SQLite_Parameter::null (void)
{
  int retval = ::sqlite3_bind_null (this->owner_->owner ().stmt_,
                                    this->index_);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (this->owner_->owner ().parent_);
}

//
// bind
//
void CUTS_DB_SQLite_Parameter::bind (const char * buffer, size_t bufsize)
{
  int retval = ::sqlite3_bind_text (this->owner_->owner ().stmt_,
                                    this->index_,
                                    buffer,
                                    bufsize,
                                    SQLITE_TRANSIENT);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (this->owner_->owner ().parent_);
}

//
// bind
//
void CUTS_DB_SQLite_Parameter::bind (char * buffer, size_t bufsize)
{
  int retval = ::sqlite3_bind_text (this->owner_->owner ().stmt_,
                                    this->index_,
                                    buffer,
                                    bufsize,
                                    SQLITE_TRANSIENT);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (this->owner_->owner ().parent_);
}

//
// bind
//
void CUTS_DB_SQLite_Parameter::bind (CUTS_DB_Date_Time & dt)
{
  char * value = reinterpret_cast <char *> (dt.value ());
  this->bind (value, 20);

  CUTS_DB_Parameter::bind (dt);
}

void CUTS_DB_SQLite_Parameter::length (long len)
{

}

long CUTS_DB_SQLite_Parameter::length (void)
{
  return 0;
}

//
// reset
//
void CUTS_DB_SQLite_Parameter::
reset (const CUTS_DB_SQLite_Parameter_List * owner, int index)
{
  this->owner_ = owner;
  this->index_ = index;
}

//
// bind_int
//
void CUTS_DB_SQLite_Parameter::bind_int (int val)
{
  int retval = ::sqlite3_bind_int (this->owner_->owner ().stmt_,
                                   this->index_,
                                   val);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (this->owner_->owner ().parent_);
}

//
// bind_double
//
void CUTS_DB_SQLite_Parameter::bind_double (double val)
{
  int retval = ::sqlite3_bind_double (this->owner_->owner ().stmt_,
                                      this->index_,
                                      val);

  if (retval != SQLITE_OK)
    throw CUTS_DB_SQLite_Exception (this->owner_->owner ().parent_);
}

