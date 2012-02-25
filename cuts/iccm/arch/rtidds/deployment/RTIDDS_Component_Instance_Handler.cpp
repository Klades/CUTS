// $Id$

#include "RTIDDS_Component_Instance_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Component_Instance_Handler.inl"
#endif

////
//// operator <<=
////
//void operator <<= (::DDS::EntityFactoryQosPolicy & qos, const iccm::EntityFactoryQosPolicy & policy)
//{
//  qos.autoenable_created_entities = policy.autoenable_created_entities ();
//}
//
////
//// operator <<=
////
//void operator <<= (::DDS::DomainParticipantFactoryQos & qos, const iccm::DomainParticipantFactoryQos & policy)
//{
//  if (policy.entity_factory_p ())
//    qos.entity_factory <<= policy.entity_factory ();
//}

namespace iCCM
{

//
// configure_DDSDomainQoS
//
void RTIDDS_Component_Instance_Handler::
configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & value)
{
  // Get the current QoS values, update them, and set them.
  ::DDSDomainParticipantFactory * dpf = ::DDSDomainParticipantFactory::get_instance ();
  ::DDS_DomainParticipantFactoryQos qos;

  dpf->get_qos (qos);
  //qos <<= value;
  dpf->set_qos (qos);
}

}

//
// create_RTIDDS_Component_Instance_Handler
//
extern "C"
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_RTIDDS_Component_Instance_Handler (void)
{
  iCCM::RTIDDS_Component_Instance_Handler * handler = 0;
  ACE_NEW_RETURN (handler,
                  iCCM::RTIDDS_Component_Instance_Handler (),
                  handler);

  return handler;
}

