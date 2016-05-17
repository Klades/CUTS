// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// TAO_EventConsumer
//
CUTS_INLINE
TAO_EventConsumer::TAO_EventConsumer (void)
{

}

//
// ~TAO_EventConsumer
//
CUTS_INLINE
TAO_EventConsumer::~TAO_EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void TAO_EventConsumer::push_event (Components::EventBase * ev)
{
  ::iCCM::EventConsumer::push_event (ev);
}

}
