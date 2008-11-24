// $Id$

#include "Logging_Client_Task.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Client_Task.inl"
#endif

//
// svc
//
int CUTS_Logging_Client_Task::svc (void)
{
  if (!CORBA::is_nil (this->orb_.in ()))
    this->orb_->run ();

  return 0;
}
