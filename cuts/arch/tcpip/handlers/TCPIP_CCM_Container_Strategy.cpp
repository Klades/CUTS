// $Id$

#include "TCPIP_CCM_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container_Strategy.inl"
#endif

#include "TCPIP_CCM_Container.h"
#include "TCPIP_CCM_Instance_Handler.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant.h"

//
// configure_servant
//
void CUTS_TCPIP_CCM_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  // Register the TCP/IP servent with the object manager.
  CUTS_TCPIP_CCM_Servant * tcpip_servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (servant);

  if (0 != tcpip_servant)
    this->container_.inst_handler ()->the_ORB ().the_OM ().activate_object (tcpip_servant);
}

//
// remove_servant
//
void CUTS_TCPIP_CCM_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  CUTS_TCPIP_CCM_Servant * tcpip_servant =
    dynamic_cast <CUTS_TCPIP_CCM_Servant *> (servant);

  if (0 == tcpip_servant)
    return;

  const ACE_Utils::UUID & uuid = tcpip_servant->the_UUID ();
  this->container_.inst_handler ()->the_ORB ().the_OM ().deactivate_object (uuid);
}
