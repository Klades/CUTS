// -*- C++ -*-
// $Id$

//
// CUTS_Component
//
CUTS_INLINE
CUTS_Component::CUTS_Component (void)
{

}

//
// input_events
//
CUTS_INLINE
const CUTS_Component::input_event_map_type &
CUTS_Component::input_events (void) const
{
  return this->input_events_;
}

//
// start
//
CUTS_INLINE
const CUTS_Component::start_type & CUTS_Component::start (void) const
{
  return this->start_;
}
