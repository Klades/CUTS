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

#ifndef _CUTS_ICCM_OPENSPLICE_DEPLOYMENT_CONTAINER_STRATEGY_H_
#define _CUTS_ICCM_OPENSPLICE_DEPLOYMENT_CONTAINER_STRATEGY_H_

#include "cuts/iccm/deployment/Container_Strategy_T.h"

#include "OpenSplice_Deployment_Handlers_export.h"

namespace iCCM
{

// Forward decl.
class OpenSplice_Container;

/**
 * @class OpenSplice_Container_Strategy
 *
 * Implementation of the CCM container startegy for OpenSplice.
 */
class ICCM_OPENSPLICE_DEPLOYMENT_HANDLERS_Export OpenSplice_Container_Strategy :
  public Container_Strategy_T <OpenSplice_Container>
{
public:
  /// Type definition of the base type.
  typedef Container_Strategy_T <OpenSplice_Container> base_type;

  /// Initializing constructor.
  OpenSplice_Container_Strategy (OpenSplice_Container & container);

  /// Destructor.
  virtual ~OpenSplice_Container_Strategy (void);

  virtual void
    configure_servant (
    ::PortableServer::Servant servant,
    const ::Components::ConfigValues & config);
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_ICCM_OPENSPLICE_DEPLOYMENT_CONTAINER_STRATEGY_H_
