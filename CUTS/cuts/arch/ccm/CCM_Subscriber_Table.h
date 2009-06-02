// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Subscriber_Table_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_SUBSCRIBER_TABLE_H_
#define _CUTS_CCM_SUBSCRIBER_TABLE_H_

#include "ccm/CCM_EventsC.h"
#include "CCM_export.h"

/**
 * @class CUTS_TCPIP_CCM_Subscriber_Table
 */
class CUTS_CCM_Export CUTS_CCM_Subscriber_Table
{
public:
  CUTS_CCM_Subscriber_Table (void);

  virtual ~CUTS_CCM_Subscriber_Table (void) = 0;

  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr) = 0;

  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie *) = 0;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Subscriber_Table.inl"
#endif

#endif  // !defined _CUTS_CCM_SUBSCRIBER_TABLE_H_
