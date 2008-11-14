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
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - running the server's main event loop (thr_id: %t)\n"));

  this->orb_->run ();
  return 0;
}
