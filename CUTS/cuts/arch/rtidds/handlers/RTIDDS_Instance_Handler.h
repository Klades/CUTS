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
#include "RTIDDS_Container.h"
#include "RTIDDS_Deployment_Handlers_export.h"

/**
 * @class CUTS_RTIDDS_CCM_Instance_Handler
 */
class CUTS_RTIDDS_CCM_Instance_Handler :
  public CUTS_CCM_Component_Instance_Handler_T <CUTS_RTIDDS_CCM_Instance_Handler,
                                                CUTS_RTIDDS_CCM_Container>
{
public:
  typedef CUTS_CCM_Component_Instance_Handler_T <CUTS_RTIDDS_CCM_Instance_Handler,
                                                 CUTS_RTIDDS_CCM_Container>
                                                 base_type;
  /// Default constructor.
  CUTS_RTIDDS_CCM_Instance_Handler (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Instance_Handler (void);

  /**
   * Configure the deployment properties for this locality manager. The
   * only deployment property supported at this moment is DDSDomainQoS.
   * This property points to an XML file that sets the DomainQoS for the
   * DDS participants managed by this handler.
   *
   * @param[in]         props         Configuration properties
   */
  virtual void configure (const Deployment::Properties & props);

private:
  /// Helper method handle the DDSDominQoS property.
  void configure_DDSDomainQoS (const Deployment::Property & prop);
};

extern "C"
::DAnCE::InstanceDeploymentHandler_ptr CUTS_RTIDDS_DEPLOYMENT_HANDLERS_Export
create_CUTS_RTIDDS_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Instance_Handler.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_
