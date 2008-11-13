// $Id$

#include "Types.h"

#if !defined (__CUTS_INLINE__)
#include "Types.inl"
#endif

#include "ace/OS_NS_stdio.h"

//
// value
//
void * CUTS_DB_SQLite_Date_Time::value (void)
{
  if (this->out_of_date_)
  {
    ACE_OS::sprintf (this->buffer_,
                     "%04d-%02d-%02d %02d:%02d:%02d",
                     this->dt_.year (),
                     this->dt_.month (),
                     this->dt_.day (),
                     this->dt_.hour (),
                     this->dt_.minute (),
                     this->dt_.second ());

    this->out_of_date_ = false;
  }

  return this->buffer_;
}
