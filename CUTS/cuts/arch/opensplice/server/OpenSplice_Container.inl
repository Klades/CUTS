// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_CCM_Container
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Container::
CUTS_OpenSplice_CCM_Container (CUTS_OpenSplice_CCM_ComponentServer * server,
			       const Components::ConfigValues & config,
			       ::PortableServer::POA_ptr poa,
			       ::Components::Deployment::ComponentInstallation_ptr installer)
  : base_type (server, config, poa, installer)
{

}

//
// ~CUTS_OpenSplice_CCM_Container
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Container::~CUTS_OpenSplice_CCM_Container (void)
{

}
