// $Id$

//
// CUTS_TCPIP_Connector
//
CUTS_INLINE
CUTS_TCPIP_Connector::CUTS_TCPIP_Connector (void)
{

}

//
// get_peer
//
CUTS_INLINE
int CUTS_TCPIP_Connector::
get_peer (const char * addr, CUTS_TCPIP_Connector_Svc_Handler * & handler)
{
  peer_addr_type peer_addr (addr);
  return this->get_peer (peer_addr, handler);
}

