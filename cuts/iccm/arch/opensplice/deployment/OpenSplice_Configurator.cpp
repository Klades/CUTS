// $Id$

#include "OpenSplice_Configurator.h"
#include "OpenSplice_Participant_File.h"

#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant.h"

//
// operator <<=
//
int operator <<= (DDS::EntityFactoryQosPolicy & qos,
                  const iccm::dds::EntityFactoryQosPolicy & policy)
{
  qos.autoenable_created_entities = policy.autoenable_created_entities ();
  return 0;
}

//
// operator <<=
//
int operator <<= (DDS::SchedulingClassQosPolicyKind & qos,
                  const iccm::dds::SchedulingClassQosPolicyKind & policy)
{
  using iccm::dds::SchedulingClassQosPolicyKind;

  switch (policy.integral ())
  {
  case SchedulingClassQosPolicyKind::SCHEDULING_DEFUALT_l:
    qos = DDS::SCHEDULE_DEFAULT;
    break;

  case SchedulingClassQosPolicyKind::SCHEDULING_TIMESHARING_l:
    qos = DDS::SCHEDULE_TIMESHARING;
    break;

  case SchedulingClassQosPolicyKind::SCHEDULING_REALTIME_l:
    qos = DDS::SCHEDULE_REALTIME;
    break;

  default:
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid SchedulingClassQosPolicyKind\n")),
                       1);
  }

  return 0;
}

//
// operator <<=
//
int operator <<= (DDS::SchedulingPriorityQosPolicyKind & qos,
                  const iccm::dds::SchedulingPriorityQosPolicyKind & policy)
{
  using iccm::dds::SchedulingPriorityQosPolicyKind;

  switch (policy.integral ())
  {
  case SchedulingPriorityQosPolicyKind::PRIORITY_ABSOLUTE_l:
    qos = DDS::PRIORITY_ABSOLUTE;
    break;

  case SchedulingPriorityQosPolicyKind::PRIORITY_RELATIVE_l:
    qos = DDS::PRIORITY_RELATIVE;
    break;

  default:
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid SchedulingPriorityQosPolicyKind\n")),
                       1);
  }

  return 0;
}


//
// operator <<=
//
int operator <<= (DDS::SchedulingClassQosPolicy & qos,
                  const iccm::dds::SchedulingClassQosPolicy & policy)
{
  return (qos.kind <<= policy.kind ());
}

//
// operator <<=
//
int operator <<= (DDS::SchedulingPriorityQosPolicy & qos,
                  const iccm::dds::SchedulingPriorityQosPolicy & policy)
{
  return (qos.kind <<= policy.kind ());
}

//
// operator <<=
//
int operator <<= (DDS::SchedulingQosPolicy & qos, const iccm::dds::SchedulingQosPolicy & policy)
{
  int errors = (qos.scheduling_class <<= policy.scheduling_class ());
  errors += (qos.scheduling_priority_kind <<= policy.scheduling_priority_kind ());
  qos.scheduling_priority = static_cast <CORBA::Long> (policy.scheduling_priority ());

  return errors;
}

//
// operator <<=
//
int operator <<= (CUTS_OpenSplice_Servant & s, const iccm::dds::DomainParticipantQos & config)
{
  int errors = 0;

  //// Get the domain participants current QoS settings.
  //DDS::DomainParticipant_var p = s.participant ();
  //DDS::DomainParticipantQos qos;
  //p->get_qos (qos);

  //if (config.entity_factory_p ())
  //  errors += (qos.entity_factory <<= config.entity_factory ());

  //if (config.watchdog_scheduling_p ())
  //  errors += (qos.watchdog_scheduling <<= config.watchdog_scheduling ());

  //if (config.listener_scheduling_p ())
  //  errors += (qos.listener_scheduling <<= config.listener_scheduling ());

  return errors;
}

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
    if (0 == ACE_OS::strcmp (config_values[i]->name (), "ParticipantQoS"))
      config_values[i]->value () >>= config;
  }

  return 0;
}

//
// configure
//
int CUTS_OpenSplice_Configurator::
configure (const char * filename, CUTS_OpenSplice_Servant * servant)
{
  // Load the configuration file.
  CUTS_OpenSplice_Participant_File file;
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
