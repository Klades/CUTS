// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::
CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_ComponentServer * parent,
                          const Components::ConfigValues & config,
                          ::PortableServer::POA_ptr poa,
                          ::Components::Deployment::ComponentInstallation_ptr installer)
: base_type (parent, config, poa, installer)
{

}

//
// ~CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::~CUTS_TCPIP_CCM_Container (void)
{

}
