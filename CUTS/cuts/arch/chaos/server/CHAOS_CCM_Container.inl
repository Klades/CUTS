// -*- C++ -*-
// $Id$

//
// CUTS_CHAOS_CCM_Container
//
CUTS_INLINE
CUTS_CHAOS_CCM_Container::
CUTS_CHAOS_CCM_Container (
  CUTS_CHAOS_CCM_ComponentServer * server,
	const Components::ConfigValues & config,
	::PortableServer::POA_ptr poa,
	::Components::Deployment::ComponentInstallation_ptr installer)
  : CUTS_CHAOS_CCM_Container_Base (server, config, poa, installer)
{

}

//
// ~CUTS_CHAOS_CCM_Container
//
CUTS_INLINE
CUTS_CHAOS_CCM_Container::~CUTS_CHAOS_CCM_Container (void)
{

}
