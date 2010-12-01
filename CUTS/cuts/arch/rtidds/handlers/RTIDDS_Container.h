// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_CCM_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_CONTAINER_H_
#define _CUTS_OPENSPLICE_CCM_CONTAINER_H_

#include "cuts/arch/ccm/CCM_Container_T.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant.h"
#include "RTIDDS_Container_Strategy.h"

// Forward decl.
class CUTS_RTIDDS_CCM_Instance_Handler;

/**
 * @class CUTS_RTIDDS_CCM_Container
 */
class CUTS_RTIDDS_DEPLOYMENT_HANDLERS_Export CUTS_RTIDDS_CCM_Container :
  public CUTS_CCM_Container_T <CUTS_RTIDDS_CCM_Container,
                               CUTS_RTIDDS_CCM_Instance_Handler,
                               CUTS_RTIDDS_CCM_Container_Strategy,
                               CUTS_RTIDDS_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef
    CUTS_CCM_Container_T <CUTS_RTIDDS_CCM_Container,
                          CUTS_RTIDDS_CCM_Instance_Handler,
                          CUTS_RTIDDS_CCM_Container_Strategy,
                          CUTS_RTIDDS_CCM_Servant> base_type;

  CUTS_RTIDDS_CCM_Container (CUTS_RTIDDS_CCM_Instance_Handler * server,
                                 ::PortableServer::POA_ptr poa);

  /// Destructor.
  virtual ~CUTS_RTIDDS_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Container.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_CONTAINER_H_
