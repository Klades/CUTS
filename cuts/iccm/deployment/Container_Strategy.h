// -*- C++ -*-

//=============================================================================
/**
 *  @file         Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_CONTAINER_STRATEGY_H_
#define _CUTS_ICCM_CONTAINER_STRATEGY_H_

#include "ccm/CCM_EnterpriseComponentC.h"
#include "ccm/CCM_StandardConfiguratorC.h"
#include "tao/PortableServer/PS_ForwardC.h"

#include "cuts/config.h"

#include "Deployment_Handlers_export.h"

namespace iCCM
{

/**
 * @class Container_Strategy
 */
class ICCM_DEPLOYENT_HANDLERS_Export Container_Strategy
{
public:
  /// Default constructor.
  Container_Strategy (void);

  /// Destructor.
  virtual ~Container_Strategy (void);

  /**
   * Method for loading an executor.
   *
   * @param[in]       location        Location of the executor
   * @param[in]       entrypt         Entry point for the executor
   */
  virtual ::Components::EnterpriseComponent_ptr
    load_executor (const char * location,
                   const char * entrypt);

  /**
   * Method for loading a servant.
   *
   * @param[in]       name            Name associated with servant
   * @param[in]       location        Location of the executor
   * @param[in]       entrypt         Entry point for the executor
   * @param[in]       port_POA        POA for activating servant ports
   * @param[in]       executor        Executor owned by servant
   */
  virtual ::PortableServer::Servant
    load_servant (const char * name,
                  const char * location,
                  const char * entrypt,
                  ::PortableServer::POA_ptr port_POA,
                  ::Components::EnterpriseComponent_ptr executor);

  /**
   * Notification to activate the servant.
   *
   * @param[in]       servant       Servant to configure.
   */
  virtual void
    install_servant (::PortableServer::Servant servant);

  /**
   * Notification to configurate the servant.
   */
  virtual void
    configure_servant (::PortableServer::Servant servant,
                       const ::Components::ConfigValues & values);

  /**
   * Notification to remove the servant.
   *
   * @param[in]       servant       Servant to remove
   */
  virtual void
    remove_servant (::PortableServer::Servant servant);
};

}

#if defined (__CUTS_INLINE__)
#include "Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_ICCM_CONTAINER_STRATEGY_H_
