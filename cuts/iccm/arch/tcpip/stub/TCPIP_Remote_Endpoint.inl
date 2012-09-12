// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Remote_Endpoint
//
CUTS_INLINE
CUTS_TCPIP_Remote_Endpoint::CUTS_TCPIP_Remote_Endpoint (void)
: handler_ (0)
{

}

//
// ~CUTS_TCPIP_Remote_Endpoint
//
CUTS_INLINE
CUTS_TCPIP_Remote_Endpoint::~CUTS_TCPIP_Remote_Endpoint (void)
{

}

//
// is_connected
//
CUTS_INLINE
bool CUTS_TCPIP_Remote_Endpoint::is_connected (void) const
{
  return 0 != this->handler_;
}
