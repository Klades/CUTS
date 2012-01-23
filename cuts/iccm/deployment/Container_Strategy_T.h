// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Container_Strategy_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_CONTAINER_STRATEGY_T_H_
#define _CUTS_ICCM_CONTAINER_STRATEGY_T_H_

#include "Container_Strategy.h"

namespace iCCM
{

/**
 * @class CUTS_CCM_Container_Strategy_T
 */
template <typename CONTAINER>
class Container_Strategy_T : public Container_Strategy
{
public:
  /// Type definition of the servant type.
  typedef CONTAINER server_type;

  /**
   * Initializing constructor
   *
   * @param[in]       container       Host container of strategy.
   */
  CUTS_CCM_Container_Strategy_T (CONTAINER & container);

  /// Destructor.
  virtual ~CUTS_CCM_Container_Strategy_T (void);

protected:
  /// Pointer to the component server hosting the container.
  CONTAINER & container_;
};

}

#if defined (__CUTS_INLINE__)
#include "Container_Strategy_T.inl"
#endif

#include "Container_Strategy_T.cpp"

#endif  // !defined _CUTS_CCM_CONTAINER_STRATEGY_T_H_
