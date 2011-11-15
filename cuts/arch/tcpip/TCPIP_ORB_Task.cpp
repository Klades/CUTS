// -*- C++ -*-

#include "TCPIP_ORB_Task.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_ORB_Task.inl"
#endif

#include "TCPIP_ORB.h"

//
// svc
//
int CUTS_TCPIP_ORB_Task::svc (void)
{
  try
  {
    this->orb_.run ();
    return 0;
  }
  catch (...)
  {

  }

  return -1;
}
