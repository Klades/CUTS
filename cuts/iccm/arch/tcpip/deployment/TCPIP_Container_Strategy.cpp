// -*- C++ -*-
// $Id$

#include "TCPIP_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Container_Strategy.inl"
#endif

#include "TCPIP_Container.h"
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
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - installing servant...\n")));
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
}

}
