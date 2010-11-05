// -*- C++ -*-

//=============================================================================
/**
 * @file          TCPIP_CCM_Instance_Handler.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_
#define _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_

#include "cuts/arch/ccm/CCM_Component_Instance_Handler_T.h"
#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "cuts/arch/tcpip/TCPIP_ORB_Task.h"
#include "TCPIP_CCM_Container.h"
#include "TCPIP_Deployment_Handlers_export.h"

/**
 * @class CUTS_TCPIP_CCM_Instance_Handler
 */
class CUTS_TCPIP_CCM_Instance_Handler :
  public CUTS_CCM_Component_Instance_Handler_T <CUTS_TCPIP_CCM_Instance_Handler,
                                                CUTS_TCPIP_CCM_Container>
{
public:
  typedef CUTS_CCM_Component_Instance_Handler_T <CUTS_TCPIP_CCM_Instance_Handler,
                                                 CUTS_TCPIP_CCM_Container>
                                                 base_type;
  /// Default constructor.
  CUTS_TCPIP_CCM_Instance_Handler (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Instance_Handler (void);

  virtual void configure (const Deployment::Properties & config);

  virtual void close (void);

  CUTS_TCPIP_ORB & the_ORB (void);

private:
  /// The ORB for the component server.
  CUTS_TCPIP_ORB tcpip_orb_;

  /// The active object for this handler.
  CUTS_TCPIP_ORB_Task orb_task_;
};

extern "C"
::DAnCE::InstanceDeploymentHandler_ptr CUTS_TCPIP_DEPLOYMENT_HANDLERS_Export
create_CUTS_TCPIP_Component_Instance_Handler (void);


#endif  // !defined _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_
