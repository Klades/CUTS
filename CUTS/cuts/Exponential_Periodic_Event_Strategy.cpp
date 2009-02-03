// $Id$

#include "Exponential_Periodic_Event_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Exponential_Periodic_Event_Strategy.inl"
#endif

#include "ace/OS_NS_math.h"

//
// next_arrival
//
void CUTS_Exponential_Periodic_Event_Strategy::
next_arrival (ACE_Time_Value & curr_time)
{
  // Get the next interarrvial time.
  double inter_arrival = this->inter_arrivals_ ();

  // Convert the time to a ACE_Time_Value.
  ACE_Time_Value delta;
  this->convert (inter_arrival, delta);

  // Increment the current time by its delta.
  curr_time += delta;
}
