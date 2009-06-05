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
  : base_type (server, config, poa, installer),
    factory_ (::DDS::DomainParticipantFactory::get_instance ())
{

}

//
// ~CUTS_OpenSplice_CCM_Container
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Container::~CUTS_OpenSplice_CCM_Container (void)
{

}

//
// get_participant_factory
//
CUTS_INLINE
::DDS::DomainParticipantFactory_ptr
CUTS_OpenSplice_CCM_Container::get_participant_factory (void)
{
  return ::DDS::DomainParticipantFactoryInterface::_duplicate (this->factory_.in ());
}
