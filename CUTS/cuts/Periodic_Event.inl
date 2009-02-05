// -*- C++ -*-
// $Id$

//
// CUTS_Periodic_Event
//
CUTS_INLINE
CUTS_Periodic_Event::CUTS_Periodic_Event (void)
: type_ (PE_UNDEFINED),
  timer_ (-1),
  hertz_ (0.0)
{

}

//
// ~CUTS_Periodic_Event
//
CUTS_INLINE
CUTS_Periodic_Event::~CUTS_Periodic_Event (void)
{

}

//
// hertz
//
CUTS_INLINE
double CUTS_Periodic_Event::hertz (void) const
{
  return this->hertz_;
}
