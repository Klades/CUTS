// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"

// Forward decl.
class CUTS_TCPIP_CCM_Container;

/**
 * @class CUTS_TCPIP_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for TCP/IP.
 */
class CUTS_TCPIP_CCM_Container_Strategy :
  public CUTS_CCM_Container_Strategy_T <CUTS_TCPIP_CCM_Container>
{
public:
  typedef CUTS_CCM_Container_Strategy_T <CUTS_TCPIP_CCM_Container> base_type;

  /**
   * Initializing constructor
   *
   * @param[in]     container       Container hosting the strategy
   */
  CUTS_TCPIP_CCM_Container_Strategy (CUTS_TCPIP_CCM_Container & container);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_Container_Strategy (void);

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
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_STRATEGY_H_
