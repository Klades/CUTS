// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Servant
//
CUTS_INLINE
CUTS_TCPIP_CCM_Servant::CUTS_TCPIP_CCM_Servant (const char * name)
: name_ (name)
{

}

//
// ~CUTS_TCPIP_CCM_Servant
//
CUTS_INLINE
CUTS_TCPIP_CCM_Servant::~CUTS_TCPIP_CCM_Servant (void)
{

}

//
// ~CUTS_TCPIP_CCM_Servant
//
CUTS_INLINE
const ACE_CString & CUTS_TCPIP_CCM_Servant::name (void) const
{
  return this->name_;
}
