// -*- C++ -*-

//=============================================================================
/**
 * @file          OpenSplice_Component_Instance_Handler.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_COMPONENT_INSTANCE_HANDLER_H_
#define _ICCM_OPENSPLICE_COMPONENT_INSTANCE_HANDLER_H_

#include "cuts/iccm/arch/dds/deployment/DDS_Component_Instance_Handler.h"
#include "OpenSplice_Deployment.h"

#include "OpenSplice_Deployment_Handlers_export.h"

namespace iCCM
{

/**
 * @class OpenSplice_Component_Instance_Handler
 *
 * OpenSplice implementation of the component instance handler.
 */
class OpenSplice_Component_Instance_Handler :
  public DDS_Component_Instance_Handler <OpenSplice_Deployment>
{
public:
  /// Default constructor.
  OpenSplice_Component_Instance_Handler (void);

  /// Destructor.
  virtual ~OpenSplice_Component_Instance_Handler (void);

protected:
  /// Helper method handle the DDSDominQoS property.
  void configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & qos);
};

}

extern "C"
ICCM_OPENSPLICE_DEPLOYMENT_HANDLERS_Export
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_OpenSplice_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Component_Instance_Handler.inl"
#endif

#endif  // !defined _ICCM_OPENSPLICE_COMPONENT_INSTANCE_HANDLER_H_
