// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_CCM_Container
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Container::
CUTS_RTIDDS_CCM_Container (CUTS_RTIDDS_CCM_ComponentServer * server,
			       const Components::ConfigValues & config,
			       ::PortableServer::POA_ptr poa,
			       ::Components::Deployment::ComponentInstallation_ptr installer)
  : base_type (server, config, poa, installer)
{

}

//
// ~CUTS_RTIDDS_CCM_Container
//
CUTS_INLINE
CUTS_RTIDDS_CCM_Container::~CUTS_RTIDDS_CCM_Container (void)
{

}
