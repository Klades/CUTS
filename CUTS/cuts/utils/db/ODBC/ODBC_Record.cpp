// $Id$

#include "ODBC_Record.h"

#if !defined (__CUTS_INLINE__)
#include "ODBC_Record.inl"
#endif

#include "ODBC_Query.h"
#include "ace/Date_Time.h"

//
// ODBC_Record
//
ODBC_Record::ODBC_Record (const ODBC_Query & query)
: query_ (query),
  index_ (0),
  count_ (0),
  columns_ (0)
{
  SQLINTEGER count;

  SQL_VERIFY (::SQLRowCount (this->query_.stmt_, &count),
              ODBC_Stmt_Exception (this->query_.stmt_));

  this->count_ = static_cast <size_t> (count);

  SQLSMALLINT cols = 0;

  SQL_VERIFY (::SQLNumResultCols (this->query_.stmt_, &cols),
              ODBC_Stmt_Exception (this->query_.stmt_));

  this->columns_ = static_cast <size_t> (cols);
}

//
// ~ODBC_Record
//
ODBC_Record::~ODBC_Record (void)
{

}

//
// advance
//
void ODBC_Record::advance (void)
{
  if (this->index_ < this->count_)
  {
    SQL_VERIFY (::SQLFetch (this->query_.stmt_),
                ODBC_Stmt_Exception (this->query_.stmt_));

    ++ this->index_;
  }
}

//
// count
//
size_t ODBC_Record::count (void) const
{
  return this->count_;
}

//
// get_data
//
void ODBC_Record::
get_data (size_t column, ACE_Date_Time & datetime)
{
  SQL_TIMESTAMP_STRUCT timestamp;

  this->get_data_i (static_cast <SQLUSMALLINT> (column),
                    SQL_C_TYPE_TIMESTAMP,
                    &timestamp,
                    sizeof (SQL_TIMESTAMP_STRUCT),
                    0);

  // Convert the <SQL_TIMESTAMP_STRUCT> to a <ACE_Time_Value>.
  datetime.month (timestamp.month);
  datetime.day (timestamp.day);
  datetime.year (timestamp.year);
  datetime.hour (timestamp.hour);
  datetime.minute (timestamp.minute);
  datetime.second (timestamp.second);
  datetime.microsec (timestamp.fraction);
}

//
// get_data_i
//
void ODBC_Record::get_data_i (SQLUSMALLINT column,
                              SQLSMALLINT target_type,
                              SQLPOINTER target,
                              SQLINTEGER bufsize,
                              SQLINTEGER * result)
{
  SQL_VERIFY (::SQLGetData (this->query_.stmt_,
                            column,
                            target_type,
                            target,
                            bufsize,
                            result),
              ODBC_Stmt_Exception (this->query_.stmt_));
}

//
// columns
//
size_t ODBC_Record::columns (void) const
{
  return this->columns_;
}

//
// done
//
bool ODBC_Record::done (void) const
{
  return this->index_ >= this->count_;
}
