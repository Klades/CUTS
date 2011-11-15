// -*- C++ -*-

//=============================================================================
/**
 * @file          Constant_Periodic_Event_Strategy.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CONSTANT_PERIODIC_EVENT_STRATEGY_H_
#define _CUTS_CONSTANT_PERIODIC_EVENT_STRATEGY_H_

#include "Periodic_Event_Strategy.h"

/**
 * @class CUTS_Constant_Periodic_Event_Strategy
 *
 * Strategy for generating periodic events with constant arrival
 * rates.
 */
class CUTS_Export CUTS_Constant_Periodic_Event_Strategy :
  public CUTS_Periodic_Event_Strategy
{
public:
  /// Default constructor.
  CUTS_Constant_Periodic_Event_Strategy (double hertz);

  /// Destructor.
  virtual ~CUTS_Constant_Periodic_Event_Strategy (void);

  // Calculate the next arrival time.
  void next_arrival (ACE_Time_Value & curr_time);

  // Reset the generator.
  void reset (void);

private:
  ACE_Time_Value constant_;
};

#if defined (__CUTS_INLINE__)
#include "Constant_Periodic_Event_Strategy.inl"
#endif

#endif
