// $Id$

#include "RTIDDS_Configurator.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant.h"

//
// CUTS_RTIDDS_Configurator
//
CUTS_RTIDDS_Configurator::CUTS_RTIDDS_Configurator (void)
{

}

//
// ~CUTS_RTIDDS_Configurator
//
CUTS_RTIDDS_Configurator::~CUTS_RTIDDS_Configurator (void)
{

}

//
// configure
//
int CUTS_RTIDDS_Configurator::
configure (CUTS_RTIDDS_Servant * servant,
     const ::Components::ConfigValues & config)
{
  // First, set the domain for the servant/participant.
  // Get the domain participant factory.
  ::DDSDomainParticipantFactory * factory =
    ::DDSDomainParticipantFactory::get_instance ();

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
              ACE_TEXT ("%T (%t) - %M - creating a participant in domain %s\n"),
              dds_domain));

  // The domain on RTI-DDS is an unique integer. Since the DDSDomainQoS
  // is a string value, we are going to hash it. This should give us a
  // unique id for the domain.
  DDS_DomainId_t domain = dds_domain != 0 ? ACE::hash_pjw (dds_domain) : 0;

  ::DDSDomainParticipant * participant =
      factory->create_participant (domain,
                                   DDS_PARTICIPANT_QOS_DEFAULT,
                                   0,
                                   DDS_STATUS_MASK_NONE);

  // Set the participant for the servant.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring the servant ")
              ACE_TEXT ("with the participant\n")));

  if (0 != servant)
    servant->configure (participant);
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - servant is a NULL pointer\n")));


  // Configure the QoS for the participant.

  return 0;
}
