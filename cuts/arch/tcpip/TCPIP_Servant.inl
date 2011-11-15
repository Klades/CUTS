// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Servant
//
CUTS_INLINE
CUTS_TCPIP_Servant::CUTS_TCPIP_Servant (void)
: orb_ (0)
{

}

//
// ~CUTS_TCPIP_Servant
//
CUTS_INLINE
CUTS_TCPIP_Servant::~CUTS_TCPIP_Servant (void)
{

}

//
// the_UUID
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_TCPIP_Servant::the_UUID (void) const
{
  return this->uuid_;
}

//
// the_ORB
//
CUTS_INLINE
const CUTS_TCPIP_ORB * CUTS_TCPIP_Servant::the_ORB (void) const
{
  return this->orb_;
}
