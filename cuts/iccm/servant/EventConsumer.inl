// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// EventConsumer
//
CUTS_INLINE
EventConsumer::EventConsumer (void)
{

}

//
// ~EventConsumer
//
CUTS_INLINE
EventConsumer::~EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void EventConsumer::push_event (Components::EventBase *)
{
  throw CORBA::NO_IMPLEMENT ();
}

}
