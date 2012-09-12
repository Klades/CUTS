// $Id$

#include "TCPIP_Acceptor.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Acceptor.inl"
#endif

//
// make_svc_handler
//
int CUTS_TCPIP_Acceptor::
make_svc_handler (CUTS_TCPIP_Event_Handler *& handler)
{
  if (handler == 0)
    ACE_NEW_RETURN (handler,
                    CUTS_TCPIP_Event_Handler (&this->obj_mgr_),
                    -1);

  handler->reactor (this->reactor ());
  return 0;
}
