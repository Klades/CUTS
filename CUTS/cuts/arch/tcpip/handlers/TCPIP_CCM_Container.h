// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTAINER_H_
#define _CUTS_TCPIP_CCM_CONTAINER_H_

#include "cuts/arch/ccm/CCM_Container_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant.h"
#include "TCPIP_CCM_Container_Strategy.h"

// Forward decl.
class CUTS_TCPIP_CCM_Instance_Handler;

/**
 * @class CUTS_TCPIP_CCM_Container
 */
class CUTS_TCPIP_DEPLOYMENT_HANDLERS_Export CUTS_TCPIP_CCM_Container :
  public CUTS_CCM_Container_T <CUTS_TCPIP_CCM_Container,
                               CUTS_TCPIP_CCM_Instance_Handler,
                               CUTS_TCPIP_CCM_Container_Strategy,
                               CUTS_TCPIP_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef
    CUTS_CCM_Container_T <CUTS_TCPIP_CCM_Container,
                          CUTS_TCPIP_CCM_Instance_Handler,
                          CUTS_TCPIP_CCM_Container_Strategy,
                          CUTS_TCPIP_CCM_Servant> base_type;

  CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_Instance_Handler * server,
                            ::PortableServer::POA_ptr poa);

  virtual ~CUTS_TCPIP_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_H_
