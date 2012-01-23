// -*- C++ -*-

//=============================================================================
/**
 *  @file         Publisher_Table.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_PUBLISHER_TABLE_H_
#define _CUTS_ICCM_PUBLISHER_TABLE_H_

#include "ccm/CCM_EventsC.h"

#include "cuts/config.h"
#include "Servant_export.h"

namespace iCCM
{

/**
 * @class Subscriber_Table
 *
 * The interface for a CCM publisher table. The publisher table must manage
 * a set of subscribers.
 */
class ICCM_SERVANT_Export Publisher_Table
{
public:
  /// Destructor.
  virtual ~Publisher_Table (void) = 0;

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

}

#if defined (__CUTS_INLINE__)
#include "Publisher_Table.inl"
#endif

#endif  // !defined _SUBSCRIBER_TABLE_H_
