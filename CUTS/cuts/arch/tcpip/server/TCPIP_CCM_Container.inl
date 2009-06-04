// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::
CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_ComponentServer * server,
                          const Components::ConfigValues & config,
                          ::PortableServer::POA_ptr poa,
                          ::Components::Deployment::ComponentInstallation_ptr installer)
: base_type (this, config, poa, installer),
  server_ (server)
{

}

//
// ~CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::~CUTS_TCPIP_CCM_Container (void)
{

}

//
// ~CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_ComponentServer *
CUTS_TCPIP_CCM_Container::server (void)
{
  return this->server_;
}
