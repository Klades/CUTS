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

#ifndef _CUTS_OPENSPLICE_CCM_INSTANCE_HANDLER_H_
#define _CUTS_OPENSPLICE_CCM_INSTANCE_HANDLER_H_

#include "cuts/arch/ccm/CCM_Component_Instance_Handler_T.h"
#include "OpenSplice_Container.h"
#include "OpenSplice_Deployment_Handlers_export.h"

/**
 * @class CUTS_OpenSplice_CCM_Instance_Handler
 */
class CUTS_OpenSplice_CCM_Instance_Handler :
  public CUTS_CCM_Component_Instance_Handler_T <CUTS_OpenSplice_CCM_Instance_Handler,
                                                CUTS_OpenSplice_CCM_Container>
{
public:
  typedef CUTS_CCM_Component_Instance_Handler_T <CUTS_OpenSplice_CCM_Instance_Handler,
                                                 CUTS_OpenSplice_CCM_Container>
                                                 base_type;
  /// Default constructor.
  CUTS_OpenSplice_CCM_Instance_Handler (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Instance_Handler (void);
};

extern "C"
::DAnCE::InstanceDeploymentHandler_ptr CUTS_OSPL_DEPLOYMENT_HANDLERS_Export
create_CUTS_OpenSplice_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Instance_Handler.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_
