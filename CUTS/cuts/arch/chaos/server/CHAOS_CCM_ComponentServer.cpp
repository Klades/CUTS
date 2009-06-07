// $Id$

#include "CHAOS_CCM_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_CCM_ComponentServer.inl"
#endif

#include "CHAOS_CCM_ComponentServer_App.h"

//
// CUTS_CHAOS_CCM_ComponentServer
//
CUTS_CHAOS_CCM_ComponentServer::
CUTS_CHAOS_CCM_ComponentServer (CUTS_CHAOS_CCM_ComponentServer_App * app)
: CUTS_CHAOS_CCM_ComponentServer_Base (app)
{

}

//
// activate
//
int CUTS_CHAOS_CCM_ComponentServer::activate (void)
{
  base_type::activate ();
  return CUTS_TCPIP_ComponentServer::activate ();
}

//
// shutdown
//
void CUTS_CHAOS_CCM_ComponentServer::shutdown (void)
{
  // This will shutdown the TCP/IP ORB.
  CUTS_TCPIP_ComponentServer::shutdown ();

  // Pass control to the base class.
  base_type::shutdown ();
}
