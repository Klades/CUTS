// $Id$

#include "TCPIP_Remote_Endpoint.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Remote_Endpoint.inl"
#endif

#include "cuts/arch/tcpip/TCPIP_Connector.h"

//
// connect
//
int CUTS_TCPIP_Remote_Endpoint::
connect (const char * addr, const char * uuid, long event)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex, guard, this->lock_, -1);

  if (0 != CUTS_TCPIP_CONNECTOR::instance ()->get_peer (addr, this->handler_))
    return -1;

  this->header_.uuid_.from_string (uuid);
  this->header_.event_id_ = event;
  return 0;
}

//
// disconnect
//
void CUTS_TCPIP_Remote_Endpoint::disconnect (void)
{
  ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->lock_);

  this->handler_ = 0;
  this->header_.uuid_ = ACE_Utils::UUID::NIL_UUID;
  this->header_.event_id_ = -1;
}
