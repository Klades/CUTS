// -*- C++ -*-
// $Id$

#include "TCPIP_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Container_Strategy.inl"
#endif

#include "TCPIP_Container.h"
#include "TCPIP_Component_Instance_Handler.h"
#include "cuts/iccm/arch/tcpip/servant/TCPIP_Servant.h"

namespace iCCM
{

//
// install_servant
//
void TCPIP_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an TCPIP_Servant
  // by using 'dynamic_cast <TCPIP_Servant *> (servant)'.
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - installing servant...\n")));

  // Register the TCP/IP servent with the object manager.
  TCPIP_Servant * tcpip_servant =
    dynamic_cast <TCPIP_Servant *> (servant);

  if (0 != tcpip_servant)
    this->container_.inst_handler ()->the_ORB ().the_OM ().activate_object (tcpip_servant);
}

//
// configure_servant
//
void TCPIP_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  // NOTE: The servant can be casted to an TCPIP_Servant
  // by using 'dynamic_cast <TCPIP_Servant *> (servant)'.
  // Also, the ConfigValues passed into this method are the same
  // configuration values attached to a component instance.
}

//
// remove_servant
//
void TCPIP_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an TCPIP_Servant
  // by using 'dynamic_cast <TCPIP_Servant *> (servant)'.
  TCPIP_Servant * tcpip_servant =
    dynamic_cast <TCPIP_Servant *> (servant);

  if (0 == tcpip_servant)
    return;

  const ACE_Utils::UUID & uuid = tcpip_servant->the_UUID ();
  this->container_.inst_handler ()->the_ORB ().the_OM ().deactivate_object (uuid);
}

}
