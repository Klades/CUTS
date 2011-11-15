// -*- C++ -*-

//=============================================================================
/**
 * @file          Exponential_Periodic_Event_Strategy.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_EXPONENTIAL_PERIODIC_EVENT_STRATEGY_H_
#define _CUTS_EXPONENTIAL_PERIODIC_EVENT_STRATEGY_H_

#include "Periodic_Event_Strategy.h"
#include "boost/random.hpp"

/**
 * @class CUTS_Exponential_Periodic_Event_Strategy
 *
 * Strategy for generating periodic events with exponential
 * arrival rates.
 */
class CUTS_Export CUTS_Exponential_Periodic_Event_Strategy :
  public CUTS_Periodic_Event_Strategy
{
public:
  typedef boost::mt19937 generator_type;

  /// Default constructor.
  CUTS_Exponential_Periodic_Event_Strategy (double hertz);

  /// Destructor.
  virtual ~CUTS_Exponential_Periodic_Event_Strategy (void);

  // Calculate the next arrival time.
  void next_arrival (ACE_Time_Value & curr_time);

  // Reset the generator.
  void reset (void);

private:
  generator_type rng_;

  boost::exponential_distribution <> exp_;

  boost::variate_generator <generator_type &,
                            boost::exponential_distribution <> >
                            inter_arrivals_;
};

#if defined (__CUTS_INLINE__)
#include "Exponential_Periodic_Event_Strategy.inl"
#endif

#endif
