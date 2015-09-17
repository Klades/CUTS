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
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Opening connection to ")
              ACE_TEXT ("Qpid Broker [%s:%d]\n"),
              this->host_.c_str (),
              this->port_));
  this->connection_.open (this->host_, this->port_);
}

//
// passivate
//
void QpidPB_Publisher_Table::passivate (void)
{
  this->connection_.close ();
  iCCM::Publisher_Table::passivate ();
}

}
