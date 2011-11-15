// -*- C++ -*-
// $Id$

//
// CUTS_CCM_EventConsumer
//
CUTS_INLINE
CUTS_CCM_EventConsumer::
CUTS_CCM_EventConsumer (void)
{

}

//
// ~CUTS_CCM_EventConsumer
//
CUTS_INLINE
CUTS_CCM_EventConsumer::~CUTS_CCM_EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void CUTS_CCM_EventConsumer::push_event (Components::EventBase *)
{
  throw CORBA::NO_IMPLEMENT ();
}
