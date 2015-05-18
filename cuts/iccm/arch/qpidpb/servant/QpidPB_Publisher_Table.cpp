// $IdQpidPB_Publisher_Table.cpp 3086 2011-01-22 05:53:51Z hillj $

#include "QpidPB_Publisher_Table.h"

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_Table.inl"
#endif

namespace iCCM
{

//
// activate
//
void QpidPB_Publisher_Table::activate (void)
{
  this->connection_.open (this->host_, this->port_);
}

//
// passivate
//
void QpidPB_Publisher_Table::passivate (void)
{
  this->connection_.close ();
}

}
