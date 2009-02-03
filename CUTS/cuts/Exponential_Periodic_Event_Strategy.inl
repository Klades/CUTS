// -*- C++ -*-
// $Id$

#include "ace/OS_NS_time.h"

//
// CUTS_Exponential_Periodic_Event_Strategy
//
CUTS_INLINE
CUTS_Exponential_Periodic_Event_Strategy::
CUTS_Exponential_Periodic_Event_Strategy (double hertz)
: exp_ (hertz),
  inter_arrivals_ (rng_, exp_)
{
  this->rng_.seed (ACE_OS::time ());
}

//
// ~CUTS_Exponential_Periodic_Event_Strategy
//
CUTS_INLINE
CUTS_Exponential_Periodic_Event_Strategy::
~CUTS_Exponential_Periodic_Event_Strategy (void)
{

}

//
// reset
//
CUTS_INLINE
void CUTS_Exponential_Periodic_Event_Strategy::reset (void)
{
  this->exp_.reset ();
}
