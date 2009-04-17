// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Servant
//
CUTS_INLINE
CUTS_TCPIP_Servant::CUTS_TCPIP_Servant (void)
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
