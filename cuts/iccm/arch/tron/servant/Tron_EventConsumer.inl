// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Tron_EventConsumer
//
CUTS_INLINE
Tron_EventConsumer::Tron_EventConsumer (void)
{

}

//
// ~Tron_EventConsumer
//
CUTS_INLINE
Tron_EventConsumer::~Tron_EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void Tron_EventConsumer::push_event (Tron_Event * ev)
{
  throw CORBA::NO_IMPLEMENT ();
}

}
