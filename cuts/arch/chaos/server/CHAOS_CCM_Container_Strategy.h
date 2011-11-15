// -*- C++ -*-

#ifndef _CUTS_CHAOS_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_CHAOS_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"
#include "cuts/arch/opensplice/server/OpenSplice_Configurator.h"
#include "CHAOS_CCM_ComponentServer_export.h"

// Forward decl.
class CUTS_CHAOS_CCM_Container;

/// Type defintion of CUTS_CHAOS_CCM_Container_Strategy base type.
typedef
  CUTS_CCM_Container_Strategy_T <
    CUTS_CHAOS_CCM_Container>
    CUTS_CHAOS_CCM_Container_Strategy_Base;

/**
 * @class CUTS_CHAOS_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for CHAOS.
 */
class CUTS_CHAOS_CCM_COMPONENTSERVER_Export CUTS_CHAOS_CCM_Container_Strategy :
  public CUTS_CHAOS_CCM_Container_Strategy_Base
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]     container       Container hosting the strategy
   */
  CUTS_CHAOS_CCM_Container_Strategy (CUTS_CHAOS_CCM_Container & container);

  /// Destructor.
  virtual ~CUTS_CHAOS_CCM_Container_Strategy (void);

  /**
   * Callback for configuring the servant. Implementing this method
   * is optional. It primarily is used to configure the servant using
   * domain-specific information specific to the target architecture.
   *
   * @param[in]     servant         Servant to configure
   * @param[in]     config          Configuration for the servant.
   */
  virtual void
    configure_servant (::PortableServer::Servant servant,
                       const ::Components::ConfigValues & config);

  virtual void
    remove_servant (::PortableServer::Servant servant);

 private:
  /// Configurator for OpenSplice, and possibly DDS.
  CUTS_OpenSplice_Configurator ospl_configurator_;
};

#if defined (__CUTS_INLINE__)
#include "CHAOS_CCM_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_CHAOS_CCM_CONTAINER_STRATEGY_H_
