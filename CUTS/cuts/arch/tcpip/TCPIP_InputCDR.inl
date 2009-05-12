// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_InputCDR
//
CUTS_INLINE
CUTS_TCPIP_InputCDR::
CUTS_TCPIP_InputCDR (const ACE_Message_Block * data, int byte_order)
: ACE_InputCDR (data, byte_order)
{

}

//
// CUTS_TCPIP_InputCDR
//
CUTS_INLINE
CUTS_TCPIP_InputCDR::
CUTS_TCPIP_InputCDR (const char * buf, size_t bufsiz)
: ACE_InputCDR (buf, bufsiz)
{

}

//
// ~CUTS_TCPIP_InputCDR
//
CUTS_INLINE
CUTS_TCPIP_InputCDR::~CUTS_TCPIP_InputCDR (void)
{

}
