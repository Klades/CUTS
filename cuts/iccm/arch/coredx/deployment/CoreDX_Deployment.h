#ifndef _ICCM_COREDX_DEPLOYMENT_H_
#define _ICCM_COREDX_DEPLOYMENT_H_

#include "cuts/iccm/arch/coredx/servant/CoreDX_Servant.h"

namespace iCCM
{

// Forward decl.
class CoreDX_Component_Instance_Handler;
class CoreDX_Container_Strategy;
class CoreDX_Container;

/**
 * @class CoreDX_Deployment
 *
 * Trait class for the CoreDX deployment handlers.
 */
class CoreDX_Deployment
{
public:
  typedef CoreDX_Container container_type;
  typedef CoreDX_Container_Strategy container_strategy_type;
  typedef CoreDX_Component_Instance_Handler component_instance_handler_type;
  typedef CoreDX_Servant servant_type;
};

}
#endif
