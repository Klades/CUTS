// $Id$

#include "RTIDDS_Configurator.h"
#include "RTIDDS_Participant_File.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant.h"

//
// operator <<=
//
int operator <<= (DDS_EntityFactoryQosPolicy & qos,
                  const iccm::dds::EntityFactoryQosPolicy & policy)
{
  qos.autoenable_created_entities = policy.autoenable_created_entities ();
  return 0;
}

//
// operator <<=
//
int operator <<= (CUTS_RTIDDS_Servant & s, const iccm::dds::DomainParticipantQos & config)
{
  int errors = 0;

  // Get the domain participants current QoS settings.
  DDSDomainParticipant * p = s.participant ();

  DDS_DomainParticipantQos qos;
  p->get_qos (qos);

  if (config.entity_factory_p ())
    errors += (qos.entity_factory <<= config.entity_factory ());

  return errors;
}


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
     const ::Components::ConfigValues & config_values)
{
  // First, set the domain for the servant/participant.
  // Get the domain participant factory.
  ::DDSDomainParticipantFactory * factory =
    ::DDSDomainParticipantFactory::get_instance ();

  const char * config = 0;

  for (size_t i = 0; i < config_values.length (); ++ i)
  {
    if (0 == ACE_OS::strcmp (config_values[i]->name (), "ParticipantQoS"))
      config_values[i]->value () >>= config;
  }

  ::DDSDomainParticipant * participant =
      factory->create_participant (0,
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


  if (0 != config)
  {
    // Let's configure the participant's QoS.
    if (0 != this->configure (config, servant))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to configure ")
                  ACE_TEXT ("the participant [config=%s]\n"),
                  config));
  }

  return 0;
}

//
// configure
//
int CUTS_RTIDDS_Configurator::
configure (const char * filename, CUTS_RTIDDS_Servant * servant)
{
  // Load the configuration file.
  CUTS_RTIDDS_Participant_File file;
  iccm::dds::DomainParticipantQos config;

  XSC::XML::XML_Error_Handler error_handler;
  file->setErrorHandler (&error_handler);

  // Read the configuration file into memory.
  if (!file.read (filename))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read ")
                       ACE_TEXT ("configuration file\n")),
                       -1);

  // Extract its contents.
  file >>= config;

  // Configure the servant's QoS. The return value is the number
  // of errors that occurred during the configuration process.
  int errors = (*servant <<= config);

  if (0 != errors)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - there were %d error(s)")
                       ACE_TEXT ("while configuring the servant\n"),
                       errors),
                       -1);

  return errors;
}
