// $Id$

#include "OpenSplice_Configurator.h"
#include "OpenSplice_Participant_File.h"

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
configure (CUTS_OpenSplice_Servant * servant,
           const ::Components::ConfigValues & config_values)
{
  // First, set the domain for the servant/participant. Get the
  // domain participant factory.
  ::DDS::DomainParticipantFactory_var factory =
    ::DDS::DomainParticipantFactory::get_instance ();

  const char * config = 0;

  for (size_t i = 0; i < config_values.length (); ++ i)
  {
    if (0 == ACE_OS::strcmp (config_values[i]->name (), "DDSParticipantQoS"))
      config_values[i]->value () >>= config;
  }

  DDS::DataReader_ptr ptr;
  DDS::DataReaderQos qos;
  ptr->get_qos (qos);

  ::DDS::DomainParticipant_var participant =
    factory->create_participant (0,
                                 PARTICIPANT_QOS_DEFAULT,
                                 0,
                                 ::DDS::ANY_STATUS);

  // Set the participant for the servant.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - configuring the servant ")
              ACE_TEXT ("with the participant\n")));

  servant->configure (participant.in ());

  if (0 != config)
  {
    // Let's configure the participant's QoS.
    if (0 != this->configure (config, servant))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to configure ")
                  ACE_TEXT ("the participant [config=%s]\n"),
                  config));
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - servant is a NULL pointer\n")));

  return 0;
}

//
// configure_participant
//
int CUTS_OpenSplice_Configurator::
configure (const char * config_file, CUTS_OpenSplice_Servant * servant)
{
  // Load the configuration file.
  CUTS_OpenSplice_Participant_File file;
  iccm::dds::DomainParticipantQos config;

  XSC::XML::XML_Error_Handler error_handler;
  file->setErrorHandler (&error_handler);

  // Read the configuration file into memory.
  if (!file.read (config_file))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read ")
                       ACE_TEXT ("configuration file\n")),
                       -1);

  // Extract its contents.
  file >>= config;

  return 0;
}
