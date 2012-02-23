// -*- C++ -*-

//=============================================================================
/**
 * @file          OpenSplice_Deployment.h
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
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Servant.h"

namespace iCCM
{
// Forward decl.
class OpenSplice_Deployment;

// Forward decl.
class OpenSplice_Component_Instance_Handler;

// Type definition.
typedef DDS_Container_Strategy <OpenSplice_Deployment> OpenSplice_Container_Strategy;

// Type definition.
typedef DDS_Container <OpenSplice_Deployment> OpenSplice_Container;

/**
 * @class OpenSplice_Deployment
 *
 * Trait class for the OpenSplice deployment handlers.
 */
class OpenSplice_Deployment
{
public:
  typedef OpenSplice_Container container_type;
  typedef OpenSplice_Container_Strategy container_strategy_type;
  typedef OpenSplice_Component_Instance_Handler component_instance_handler_type;
  typedef OpenSplice_Servant servant_type;
};

}

#endif  // !defined _ICCM_OPENSPLICE_DEPLOYMENT_H_
