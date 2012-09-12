// $Id$

#include "TCPIP_Connector.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Connector.inl"
#endif

//
// ~CUTS_TCPIP_Connector
//
CUTS_INLINE
CUTS_TCPIP_Connector::~CUTS_TCPIP_Connector (void)
{
  peer_table_type::ITERATOR iter (this->peer_table_);

  for (; !iter.done (); ++ iter)
    delete iter->item ();
}

//
// get_peer
//
int CUTS_TCPIP_Connector::
get_peer (const peer_addr_type & addr,
          CUTS_TCPIP_Connector_Svc_Handler * & handler)
{
  if (0 == this->peer_table_.find (addr, handler))
    return 0;

  // Perform double-lock checking to ensure only one connection
  // attempt is made to the peer.
  ACE_GUARD_RETURN (ACE_RW_Thread_Mutex,
                    guard,
                    this->connect_lock_,
                    -1);

  if (0 == this->peer_table_.find (addr, handler))
    return 0;

  // Ok, so we can go ahead and establish connection with peer.
  CUTS_TCPIP_Connector_Svc_Handler * temp = 0;

  if (0 != this->connect (temp, addr))
    return -1;

  // Store the service handler in the peer table.
  ACE_Auto_Ptr <CUTS_TCPIP_Connector_Svc_Handler> auto_clean (temp);
  int retval = this->peer_table_.bind (addr, temp);

  if (0 == retval)
    handler = auto_clean.release ();

  return retval;
}
