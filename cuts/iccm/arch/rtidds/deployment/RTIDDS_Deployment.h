// -*- C++ -*-

//=============================================================================
/**
 * @file          RTIDDS_Deployment.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_DEPLOYMENT_H_
#define _ICCM_OPENSPLICE_DEPLOYMENT_H_

#include "cuts/iccm/arch/dds/deployment/DDS_Container_Strategy.h"
#include "cuts/iccm/arch/dds/deployment/DDS_Container.h"
#include "cuts/iccm/arch/rtidds/servant/RTIDDS_Servant.h"

namespace iCCM
{
// Forward decl.
class RTIDDS_Deployment;

// Forward decl.
class RTIDDS_Component_Instance_Handler;

// Type definition.
typedef DDS_Container_Strategy <RTIDDS_Deployment> RTIDDS_Container_Strategy;

// Type definition.
typedef DDS_Container <RTIDDS_Deployment> RTIDDS_Container;

/**
 * @class RTIDDS_Deployment
 *
 * Trait class for the RTIDDS deployment handlers.
 */
class RTIDDS_Deployment
{
public:
  typedef RTIDDS_Container container_type;
  typedef RTIDDS_Container_Strategy container_strategy_type;
  typedef RTIDDS_Component_Instance_Handler component_instance_handler_type;
  typedef RTIDDS_Servant servant_type;
};

}

#endif  // !defined _ICCM_OPENSPLICE_DEPLOYMENT_H_
