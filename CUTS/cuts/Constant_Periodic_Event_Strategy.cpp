// $Id$

#include "Constant_Periodic_Event_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Constant_Periodic_Event_Strategy.inl"
#endif

//
// ~CUTS_Constant_Periodic_Event_Strategy
//
CUTS_Constant_Periodic_Event_Strategy::
CUTS_Constant_Periodic_Event_Strategy (double hertz)
{
 double inter_arrivals = 1000.0 / hertz;
 this->convert (inter_arrivals, this->constant_);
}
