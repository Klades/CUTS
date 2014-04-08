// -*- C++ -*-

//=============================================================================
/**
 *  @file         CoreDX_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_COREDX_PUBLISHER_T_H_
#define _ICCM_COREDX_PUBLISHER_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_Publisher_T.h"
#include "CoreDX.h"

namespace iCCM
{

/**
 * @class CoreDX_Publisher_T
 *
 * Template version of the CoreDX publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class CoreDX_Publisher_T :
  public DDS_Publisher_T <CoreDX, EVENT>
{
public:
  /// Default constructor.
  CoreDX_Publisher_T (void);

  /// Destructor.
  virtual ~CoreDX_Publisher_T (void);

protected:
  /// INSERT CODE HERE
};

}

#if defined (__CUTS_INLINE__)
#include "CoreDX_Publisher_T.inl"
#endif

#include "CoreDX_Publisher_T.cpp"

#endif  // !defined _ICCM_COREDX_PUBLISHER_T_H_
