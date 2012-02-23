// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Container_Strategy.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_CONTAINER_STRATEGY_H_
#define _ICCM_DDS_CONTAINER_STRATEGY_H_

#include "cuts/iccm/deployment/Container_Strategy_T.h"

namespace iCCM
{

/**
 * @class DDS_Container_Strategy
 *
 * Implementation of the CCM container startegy for DDS.
 */
template <typename T>
class DDS_Container_Strategy :
  public Container_Strategy_T <typename T::container_type>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         container         Reference to container
   */
  DDS_Container_Strategy (typename T::container_type & container);

  /// Destructor.
  virtual ~DDS_Container_Strategy (void);

  /**
   * Configure the servant. The configuration values are the attribute
   * values for the component instance and its implementation.
   */
  virtual void
    configure_servant (
    ::PortableServer::Servant servant,
    const ::Components::ConfigValues & config);
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Container_Strategy.inl"
#endif

#include "DDS_Container_Strategy.cpp"

#endif  // !defined _ICCM_DDS_DEPLOYMENT_CONTAINER_STRATEGY_H_
