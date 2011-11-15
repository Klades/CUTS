// $Id$

#include "ORB_Server_Task.h"

#if !defined (__CUTS_INLINE__)
#include "ORB_Server_Task.inl"
#endif

//
// svc
//
int CUTS_ORB_Server_Task::svc (void)
{
  CUTS_TRACE ("CUTS_ORB_Server_Task::svc (void)");

  try
  {
    this->orb_->run ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
