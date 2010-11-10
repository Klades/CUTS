// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_CCM_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_CONTAINER_H_
#define _CUTS_OPENSPLICE_CCM_CONTAINER_H_

#include "cuts/arch/ccm/CCM_Container_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant.h"
#include "OpenSplice_Container_Strategy.h"

// Forward decl.
class CUTS_OpenSplice_CCM_Instance_Handler;

/**
 * @class CUTS_OpenSplice_CCM_Container
 */
class CUTS_OSPL_DEPLOYMENT_HANDLERS_Export CUTS_OpenSplice_CCM_Container :
  public CUTS_CCM_Container_T <CUTS_OpenSplice_CCM_Container,
                               CUTS_OpenSplice_CCM_Instance_Handler,
                               CUTS_OpenSplice_CCM_Container_Strategy,
                               CUTS_OpenSplice_CCM_Servant>
{
public:
  /// Type definition of the base type.
  typedef
    CUTS_CCM_Container_T <CUTS_OpenSplice_CCM_Container,
                          CUTS_OpenSplice_CCM_Instance_Handler,
                          CUTS_OpenSplice_CCM_Container_Strategy,
                          CUTS_OpenSplice_CCM_Servant> base_type;

  CUTS_OpenSplice_CCM_Container (CUTS_OpenSplice_CCM_Instance_Handler * server,
                                 ::PortableServer::POA_ptr poa);

  /// Destructor.
  virtual ~CUTS_OpenSplice_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Container.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_CONTAINER_H_
