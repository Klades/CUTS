// -*- C++ -*-
// $Id$

//
// CUTS_Periodic_Event_Strategy
//
CUTS_INLINE
CUTS_Periodic_Event_Strategy::CUTS_Periodic_Event_Strategy (void)
{

}

//
// ~CUTS_Periodic_Event_Strategy
//
CUTS_INLINE
CUTS_Periodic_Event_Strategy::~CUTS_Periodic_Event_Strategy (void)
{

}

//
// convert
//
CUTS_INLINE
void CUTS_Periodic_Event_Strategy::convert (double secs, ACE_Time_Value & tv)
{
  tv.set (secs);
  //// Break the number into integer/fraction part.
  //double ipart = 0.0;
  //double fpart = modf (secs, &ipart);

  //// Determine the number of usecs in the seconds.
  //fpart *= ACE_ONE_SECOND_IN_USECS;
  //tv.set (
  //ACE_Time_Value delta (static_cast <time_t> (ipart),
  //                      static_cast <suseconds_t> (fpart));

  //// Increment the current time by its delta.
  //curr_time += delta;
  //return 0;
}
