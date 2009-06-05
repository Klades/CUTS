// $Id$

#include "TCPIP_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

#include "TCPIP_CCM_ComponentServer_App.h"

//
// CUTS_TCPIP_CCM_EventConsumer
//
CUTS_TCPIP_CCM_ComponentServer::
CUTS_TCPIP_CCM_ComponentServer (CUTS_TCPIP_CCM_ComponentServer_App * app)
: base_type (app)
{

}

//
// shutdown
//
void CUTS_TCPIP_CCM_ComponentServer::shutdown (void)
{
  // This will shutdown the TCP/IP ORB.
  CUTS_TCPIP_ComponentServer::shutdown ();

  // Pass control to the base class.
  base_type::shutdown ();
}
