// -*- C++ -*-

//=============================================================================
/**
 *  @file         $File$
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_OPENSPLICE_DEPLOYMENT_CONTAINER_H_
#define _CUTS_ICCM_OPENSPLICE_DEPLOYMENT_CONTAINER_H_

#include "cuts/iccm/deployment/Container_T.h"
#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Servant.h"

#include "OpenSplice_Container_Strategy.h"

namespace iCCM
{

// Forward decl.
class OpenSplice_Component_Instance_Handler;

/**
 * @class OpenSplice_Container
 */
class ICCM_OPENSPLICE_DEPLOYMENT_HANDLERS_Export OpenSplice_Container :
  public Container_T <OpenSplice_Container,
                      OpenSplice_Component_Instance_Handler,
                      OpenSplice_Container_Strategy,
                      OpenSplice_Servant>
{
public:
  /// Type definition of the base type.
  typedef
    Container_T <OpenSplice_Container,
                 OpenSplice_Component_Instance_Handler,
                 OpenSplice_Container_Strategy,
                 OpenSplice_Servant> base_type;

  /**
   * Initializing constructor.
   *
   * @param[in]           handler         Pointer to the parent handler
   * @param[in]           the_POA         POA to pass to base class
   */
  OpenSplice_Container (OpenSplice_Component_Instance_Handler * handler,
                        ::PortableServer::POA_ptr the_POA);

  /// Destructor.
  virtual ~OpenSplice_Container (void);

private:
  OpenSplice_Container (void);
  OpenSplice_Container (const OpenSplice_Container &);
  const OpenSplice_Container & operator = (const OpenSplice_Container &);
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Container.inl"
#endif

#endif  // !defined _CUTS_OPENSPLICE_CCM_CONTAINER_H_
