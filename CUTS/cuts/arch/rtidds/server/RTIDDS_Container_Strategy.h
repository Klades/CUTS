// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_CCM_Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_RTIDDS_CCM_CONTAINER_STRATEGY_H_
#define _CUTS_RTIDDS_CCM_CONTAINER_STRATEGY_H_

#include "cuts/arch/ccm/CCM_Container_Strategy_T.h"
#include "RTIDDS_Configurator.h"

// Forward decl.
class CUTS_RTIDDS_CCM_Container;

/**
 * @class CUTS_RTIDDS_CCM_Container_Strategy
 *
 * Implementation of the CCM container startegy for RTIDDS.
 */
class CUTS_RTIDDS_COMPONENTSERVER_Export CUTS_RTIDDS_CCM_Container_Strategy :
  public CUTS_CCM_Container_Strategy_T <CUTS_RTIDDS_CCM_Container>
{
public:
  typedef CUTS_CCM_Container_Strategy_T <CUTS_RTIDDS_CCM_Container> base_type;

  CUTS_RTIDDS_CCM_Container_Strategy (CUTS_RTIDDS_CCM_Container & container);

  virtual ~CUTS_RTIDDS_CCM_Container_Strategy (void);

  virtual void configure_servant (::PortableServer::Servant servant,
				  const ::Components::ConfigValues & config);

private:
  CUTS_RTIDDS_Configurator configurator_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Container_Strategy.inl"
#endif

#endif  // !defined _CUTS_RTIDDS_CCM_CONTAINER_STRATEGY_H_
