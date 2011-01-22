// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Publisher_Table.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_PUBLISHER_TABLE_H_
#define _CUTS_CCM_PUBLISHER_TABLE_H_

#include "ccm/CCM_EventsC.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_Subscriber_Table
 *
 * The interface for a CCM publisher table. The publisher table must manage
 * a set of subscribers.
 */
class CUTS_CCM_Export CUTS_CCM_Publisher_Table
{
public:
  /// Destructor.
  virtual ~CUTS_CCM_Publisher_Table (void) = 0;

  /**
   * Subscribe a consumer to this publisher.
   *
   * @param[in]         consumer        Target consumer
   * @return            Subscription cookie
   */
  virtual ::Components::Cookie * subscribe (::Components::EventConsumerBase_ptr consumer) = 0;

  /**
   * Unsubscribe a consumer. The consumer to be unsubscribed is identifed
   * be the cookie parameter. If there cookie cannot be found, then an
   * exception is thrown.
   *
   * @param[in]         c               Subscription cookie
   * @return            The once connected consumer
   */
  virtual ::Components::EventConsumerBase_ptr unsubscribe (::Components::Cookie * c) = 0;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Publisher_Table.inl"
#endif

#endif  // !defined _CUTS_CCM_SUBSCRIBER_TABLE_H_
