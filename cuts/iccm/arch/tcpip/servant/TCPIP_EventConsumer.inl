// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// TCPIP_EventConsumer
//
CUTS_INLINE
TCPIP_EventConsumer::TCPIP_EventConsumer (void)
{

}

//
// ~TCPIP_EventConsumer
//
CUTS_INLINE
TCPIP_EventConsumer::~TCPIP_EventConsumer (void)
{

}

//
// push_event
//
CUTS_INLINE
void TCPIP_EventConsumer::push_event (Components::EventBase *)
{
  throw CORBA::NO_IMPLEMENT ();
}

}
