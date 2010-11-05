// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLD_H_
#define _TCPIP_HELLOWORLD_H_

#include "HelloWorldC.h"
#include "cuts/arch/tcpip/TCPIP_InputCDR.h"
#include "cuts/arch/tcpip/TCPIP_OutputCDR.h"


#include "HelloWorld_stub_export.h"

//============================================================================
// stream operators for ::Message
//============================================================================

HELLOWORLD_STUB_Export ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR &, ::Message &);
HELLOWORLD_STUB_Export ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR &, const ::Message &);

//============================================================================
// stream operators for ::TimeValue
//============================================================================

HELLOWORLD_STUB_Export ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR &, ::TimeValue &);
HELLOWORLD_STUB_Export ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR &, const ::TimeValue &);

#endif  // !defined _TCPIP_HELLOWORLD_H_
