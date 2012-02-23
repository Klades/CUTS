// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Publisher_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_OPENSPLICE_CCM_PUBLISHER_T_H_
#define _CUTS_OPENSPLICE_CCM_PUBLISHER_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_Publisher_T.h"
#include "OpenSplice.h"

namespace iCCM
{

/**
 * @class OpenSplice_Publisher_T
 *
 * Template version of the OpenSplice publisher object that is bound to
 * an specific event type.
 */
template <typename EVENT>
class OpenSplice_Publisher_T :
  public DDS_Publisher_T <OpenSplice, EVENT>
{
public:
  /// Default constructor.
  OpenSplice_Publisher_T (void);

  /// Destructor.
  virtual ~OpenSplice_Publisher_T (void);
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_T.inl"
#endif

#include "OpenSplice_Publisher_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SUBSCRIBER_T_H_

