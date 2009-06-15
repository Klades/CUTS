// $Id$

#include "OpenSplice_Configurator.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant.h"

//
// CUTS_OpenSplice_Configurator
//
CUTS_OpenSplice_Configurator::CUTS_OpenSplice_Configurator (void)
{

}

//
// ~CUTS_OpenSplice_Configurator
//
CUTS_OpenSplice_Configurator::~CUTS_OpenSplice_Configurator (void)
{

}

//
// configure
//
int CUTS_OpenSplice_Configurator::
configure (CUTS_OpenSplice_CCM_Servant * servant,
	   const ::Components::ConfigValues & config)
{
  // First, set the domain for the servant/participant.
  // Get the domain participant factory.
  ::DDS::DomainParticipantFactory_var factory =
    ::DDS::DomainParticipantFactory::get_instance ();

  const char * dds_domain = 0;
  const char * dds_participant = 0;

  for (size_t i = 0; i < config.length (); ++ i)
    {
      if (0 == ACE_OS::strcmp (config[i]->name (), "DDSDomainQoS"))
	config[i]->value () >>= dds_domain;
      else if (0 == ACE_OS::strcmp (config[i]->name (), "DDSParticipantQoS"))
	config[i]->value () >>= dds_participant;
    }

  ACE_DEBUG ((LM_DEBUG,
	      "%T (%t) - %M - creating a participant in domain %s\n",
	      dds_domain));

  ::DDS::DomainParticipant_var participant =
      factory->create_participant (dds_domain,
                                   PARTICIPANT_QOS_DEFAULT,
                                   0,
                                   ::DDS::ANY_STATUS);

  // Set the participant for the servant.
  servant->configure (participant.in ());
  
  // Configure the QoS for the participant.

  return 0;
}
