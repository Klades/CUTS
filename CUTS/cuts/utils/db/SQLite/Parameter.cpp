// $Id$

#include "Parameter.h"

#if !defined (__CUTS_INLINE__)
#include "Parameter.inl"
#endif

#include "Query.h"
#include "Exception.h"
#include "cuts/utils/db/DB_Types_Impl.h"
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
void CUTS_DB_SQLite_Parameter::bind (CUTS_DB_Date_Time_Impl * dt)
{
  std::ostringstream ostr;
  ostr << dt->year () << "-" << dt->month () << "-" << dt->day ()
       << " "
       << dt->hour () << ":" << dt->minute () << ":" << dt->second ();

  this->bind (const_cast <char *> (ostr.str ().c_str ()),
              ostr.str ().length ());
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
