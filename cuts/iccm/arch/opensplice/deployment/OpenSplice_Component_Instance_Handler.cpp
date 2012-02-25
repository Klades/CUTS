// $Id$

#include "OpenSplice_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Component_Instance_Handler.inl"
#endif

#include "ccpp_dds_dcps.h"

//
// operator <<=
//
void operator <<= (::DDS::EntityFactoryQosPolicy & qos, const iccm::EntityFactoryQosPolicy & policy)
{
  qos.autoenable_created_entities = policy.autoenable_created_entities ();
}

//
// operator <<=
//
void operator <<= (::DDS::DomainParticipantFactoryQos & qos, const iccm::DomainParticipantFactoryQos & policy)
{
  if (policy.entity_factory_p ())
    qos.entity_factory <<= policy.entity_factory ();
}

namespace iCCM
{

//
// configure_DDSDomainQoS
//
void OpenSplice_Component_Instance_Handler::
configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & value)
{
  // Get the current QoS values, update them, and set them.
  ::DDS::DomainParticipantFactory_var dpf = ::DDS::DomainParticipantFactory::get_instance ();
  ::DDS::DomainParticipantFactoryQos qos;

  dpf->get_qos (qos);
  qos <<= value;
  dpf->set_qos (qos);
}

}

//
// create_CUTS_OpenSplice_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_OpenSplice_Component_Instance_Handler (void)
{
  return new iCCM::OpenSplice_Component_Instance_Handler ();
}


