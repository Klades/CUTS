// $Id$

#include "ODBC_Parameter_List.h"

#if !defined (__CUTS_INLINE__)
#include "ODBC_Parameter_List.inl"
#endif

#include "ODBC_Query.h"
#include "ace/Log_Msg.h"
#include "ace/CORBA_macros.h"


//
// ODBC_Parameter_List
//
ODBC_Parameter_List::ODBC_Parameter_List (const ODBC_Query & query)
: query_ (query)
{

}

//
// ~ODBC_Parameter_List
//
ODBC_Parameter_List::~ODBC_Parameter_List (void)
{

}

//
// reset
//
void ODBC_Parameter_List::reset (void)
{
  // Get the number of parameters in the prepared statement.
  SQLSMALLINT pcount;
  SQL_VERIFY (::SQLNumParams (this->query_.stmt_, &pcount),
              ODBC_Stmt_Exception (this->query_.stmt_));

  // If this is the first prepared statement on this handle
  // then we need to allocate a new parameter list.
  this->params_.size (pcount);

  for (int i = 0; i < pcount; ++ i)
  {
    this->params_[i].query_ = &this->query_;
    this->params_[i].index_ = i;
  }
}
