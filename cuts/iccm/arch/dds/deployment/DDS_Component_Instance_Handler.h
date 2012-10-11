// -*- C++ -*-

//=============================================================================
/**
 * @file          DDS_Component_Instance_Handler.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_COMPONENT_INSTANCE_HANDLER_H_
#define _ICCM_DDS_COMPONENT_INSTANCE_HANDLER_H_

#include "cuts/iccm/deployment/Component_Instance_Handler_T.h"

namespace iccm
{
// Forward decl.
class DomainParticipantFactoryQos;
}

namespace iCCM
{

/**
 * @class DDS_Component_Instance_Handler
 */
template <typename T>
class DDS_Component_Instance_Handler :
  public Component_Instance_Handler_T <typename T::component_instance_handler_type,
                                       ::DAnCE::InstanceDeploymentHandler,
                                       typename T::container_type>
{
public:
  /// Default constructor.
  DDS_Component_Instance_Handler (void);

  /// Destructor.
  virtual ~DDS_Component_Instance_Handler (void);

  /**
   * Configure the deployment properties for this locality manager. The
   * only deployment property supported at this moment is DDSDomainQoS.
   * This property points to an XML file that sets the DomainQoS for the
   * DDS participants managed by this handler.
   *
   * @param[in]         props         Configuration properties
   */
  virtual void configure (const Deployment::Properties & props);

protected:
  /// Helper method handle the DDSDominQoS property.
  virtual void configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & qos) = 0;

private:
  /// Load the domain Qos from the Xml.
  bool load_DDSDomainQoS (const ::Deployment::Property & prop,
                          iccm::DomainParticipantFactoryQos & qos);
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Component_Instance_Handler.inl"
#endif

#include "DDS_Component_Instance_Handler.cpp"

#endif  // !defined _ICCM_DDS_COMPONENT_INSTANCE_HANDLER_H_
