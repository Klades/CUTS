// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// TCPIP_Servant
//
CUTS_INLINE
TCPIP_Servant::TCPIP_Servant (const char * name)
: Servant (name),
  orb_ (0)
{

}

//
// ~TCPIP_Servant
//
CUTS_INLINE
TCPIP_Servant::~TCPIP_Servant (void)
{

}

//
// the_UUID
//
CUTS_INLINE
const ACE_Utils::UUID & TCPIP_Servant::the_UUID (void) const
{
  return this->uuid_;
}

//
// the_ORB
//
CUTS_INLINE
const TCPIP_ORB * TCPIP_Servant::the_ORB (void) const
{
  return this->orb_;
}

//
// handle_event
//
CUTS_INLINE
int TCPIP_Servant::handle_event (ACE_UINT32 id, ACE_InputCDR & input)
{
  throw CORBA::NO_IMPLEMENT ();
}

}
