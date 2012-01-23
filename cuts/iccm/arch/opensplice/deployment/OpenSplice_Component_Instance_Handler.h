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

#include "cuts/iccm/deployment/Component_Instance_Handler_T.h"
#include "OpenSplice_Container.h"

namespace iCCM
{

/**
 * @class OpenSplice_Component_Instance_Handler
 */
class OpenSplice_Component_Instance_Handler :
  public Component_Instance_Handler_T <OpenSplice_Component_Instance_Handler,
                                       OpenSplice_Container>
{
public:
  /// Type definition of the base type.
  typedef Component_Instance_Handler_T <OpenSplice_Component_Instance_Handler,
                                        OpenSplice_Container>
                                        base_type;

  /// Default constructor.
  OpenSplice_Component_Instance_Handler (void);

  /// Destructor.
  virtual ~OpenSplice_Component_Instance_Handler (void);

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

}

extern "C"
ICCM_OPENSPLICE_DEPLOYMENT_HANDLERS_Export
::DAnCE::InstanceDeploymentHandler_ptr
create_iCCM_OpenSplice_Component_Instance_Handler (void);

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Component_Instance_Handler.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_INSTANCE_HANDLER_H_
