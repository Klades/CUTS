// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_RTIDDS_PUBLISHER_T_H_
#define _ICCM_RTIDDS_PUBLISHER_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_Publisher_T.h"
#include "RTIDDS.h"

namespace iCCM
{

/**
 * @class RTIDDS_Publisher_T
 *
 * Template version of the RTIDDS publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class RTIDDS_Publisher_T :
  public DDS_Publisher_T <RTIDDS, EVENT>
{
public:
  /// Default constructor.
  RTIDDS_Publisher_T (void);

  /// Destructor.
  virtual ~RTIDDS_Publisher_T (void);
};

}

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher_T.inl"
#endif

#include "RTIDDS_Publisher_T.cpp"

#endif  // !defined _ICCM_RTIDDS_PUBLISHER_T_H_
