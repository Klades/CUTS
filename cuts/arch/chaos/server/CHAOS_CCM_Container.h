// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_CONTAINER_H_
#define _CUTS_CHAOS_CCM_CONTAINER_H_

#include "cuts/arch/ccm/CCM_Container_T.h"
#include "../ccm/CHAOS_CCM_Servant.h"
#include "CHAOS_CCM_Container_Strategy.h"

// Forward decl.
class CUTS_CHAOS_CCM_ComponentServer;

/// Type definition of the base type.
typedef
  CUTS_CCM_Container_T <
    CUTS_CHAOS_CCM_Container,
    CUTS_CHAOS_CCM_ComponentServer,
    CUTS_CHAOS_CCM_Container_Strategy,
    CUTS_CHAOS_CCM_Servant > CUTS_CHAOS_CCM_Container_Base;

/**
 * @class CUTS_CHAOS_CCM_Container
 */
class CUTS_CHAOS_CCM_COMPONENTSERVER_Export CUTS_CHAOS_CCM_Container :
  public CUTS_CHAOS_CCM_Container_Base
{
public:
  /// Initializing constructor.
  CUTS_CHAOS_CCM_Container (
    CUTS_CHAOS_CCM_ComponentServer * server,
    const Components::ConfigValues & config,
    ::PortableServer::POA_ptr poa,
    ::Components::Deployment::ComponentInstallation_ptr installer);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_Container (void);
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_Container.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_CONTAINER_H_

