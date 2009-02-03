// -*- C++ -*-
// $Id$

//
// ~CUTS_Constant_Periodic_Event_Strategy
//
CUTS_INLINE
CUTS_Constant_Periodic_Event_Strategy::
~CUTS_Constant_Periodic_Event_Strategy (void)
{

}

//
// next_arrival
//
CUTS_INLINE
void CUTS_Constant_Periodic_Event_Strategy::
next_arrival (ACE_Time_Value & curr_time)
{
  curr_time += this->constant_;
}

//
// reset
//
CUTS_INLINE
void CUTS_Constant_Periodic_Event_Strategy::reset (void)
{

}
