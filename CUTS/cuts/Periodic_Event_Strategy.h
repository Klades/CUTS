// -*- C++ -*-

//=============================================================================
/**
 * @file        Periodic_Event_Strategy.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PERIODIC_EVENT_STRATEGY_H_
#define _CUTS_PERIODIC_EVENT_STRATEGY_H_

#include "CUTS_export.h"
#include "ace/Time_Value.h"

/**
 * @class CUTS_Periodic_Event_Strategy
 *
 * Base class strategy for the periodic event strategies. The strategy
 * is responsible for calculating the inter-arrival rates for events
 * that enter the (open) system.
 */
class CUTS_Export CUTS_Periodic_Event_Strategy
{
public:
  /// Destructor.
  virtual ~CUTS_Periodic_Event_Strategy (void);

  /**
   * Calculate the next arrival given the current time. The strategy
   * should update \a curr_time with the absolute time of the next
   * event. This can be accomplished by adding the inter-arrival time
   * for the next event to \a curr_time.
   *
   * @param[in]           curr_time         Current time
   * @retval              0                 Success
   * @retval              -1                Failure
   */
  virtual void next_arrival (ACE_Time_Value & curr_time) = 0;

  /// Reset the strategy.
  virtual void reset (void) = 0;

protected:
  void convert (double secs, ACE_Time_Value & tv);

  /// Default constructor.
  CUTS_Periodic_Event_Strategy (void);
};

#if defined (__CUTS_INLINE__)
#include "Periodic_Event_Strategy.inl"
#endif

#endif  // !defined _CUTS_PERIODIC_EVENT_STRATEGY_H_
