// -*- C++ -*-

//=============================================================================
/**
 *  @file RTIDDS_Component_Instance_Handler.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_RTIDDS_COMPONENT_INSTANCE_HANDLER_H_
#define _ICCM_RTIDDS_COMPONENT_INSTANCE_HANDLER_H_

#include "cuts/iccm/arch/dds/deployment/DDS_Component_Instance_Handler.h"
#include "RTIDDS_Deployment.h"

#include "RTIDDS_Deployment_Handlers_export.h"

namespace iCCM
{

/**
 * @class RTIDDS_Component_Instance_Handler
 *
 * RTIDDS implementation of the deployment handlers for component
 * instances.
 */
class ICCM_RTIDDS_DEPLOYMENT_HANDLERS_Export RTIDDS_Component_Instance_Handler :
  public DDS_Component_Instance_Handler <RTIDDS_Deployment>
{
public:
  /// Default constructor.
  RTIDDS_Component_Instance_Handler (void);

  /// Destructor.
  virtual ~RTIDDS_Component_Instance_Handler (void);

protected:
  /// Helper method handle the DDSDominQoS property.
  void configure_DDSDomainQoS (const iccm::DomainParticipantFactoryQos & qos);
};

}

extern "C"
ICCM_RTIDDS_DEPLOYMENT_HANDLERS_Export
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_RTIDDS_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Component_Instance_Handler.inl"
#endif

#endif  // !defined _ICCM_RTIDDS_COMPONENT_INSTANCE_HANDLER_H_