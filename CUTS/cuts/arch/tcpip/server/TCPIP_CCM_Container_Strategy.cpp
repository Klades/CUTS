// $Id$

#include "TCPIP_CCM_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container_Strategy.inl"
#endif

#include "TCPIP_CCM_Container.h"
#include "TCPIP_CCM_ComponentServer.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant.h"
#include "ace/OS_NS_unistd.h"

//
// configure_servant
//
void CUTS_TCPIP_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  // Register the TCP/IP servent with the object manager.
  CUTS_TCPIP_CCM_Servant * tcpip_servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (servant);

  if (0 != tcpip_servant)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating the servant\n"));

    this->container_.server ()->the_ORB ().the_OM ().activate_object (tcpip_servant);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - the TCP/IP servant is now active\n"));
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%T) - %M - %s is not a TCP/IP servant\n"),
                tcpip_servant->name ().c_str ()));

    // should we throw an exception here??
  }
}

