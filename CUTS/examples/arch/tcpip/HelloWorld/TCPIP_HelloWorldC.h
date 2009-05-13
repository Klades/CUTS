// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLDC_H_
#define _TCPIP_HELLOWORLDC_H_

#include "HelloWorldC.h"
#include "cuts/arch/tcpip/TCPIP_InputCDR.h"
#include "cuts/arch/tcpip/TCPIP_OutputCDR.h"
#include "TCPIP_HelloWorld_stub_export.h"

// Stream operations
ACE_CDR::Boolean TCPIP_HELLOWORLD_STUB_Export operator << (CUTS_TCPIP_OutputCDR & stream, ::TimeValue & rhs);
ACE_CDR::Boolean TCPIP_HELLOWORLD_STUB_Export operator >> (CUTS_TCPIP_InputCDR & stream, ::TimeValue & rhs);

// Stream operations
ACE_CDR::Boolean TCPIP_HELLOWORLD_STUB_Export operator << (CUTS_TCPIP_OutputCDR & stream, ::Message & rhs);
ACE_CDR::Boolean TCPIP_HELLOWORLD_STUB_Export operator >> (CUTS_TCPIP_InputCDR & stream, ::Message & rhs);

#endif  // !defined _TCPIP_HELLOWORLDC_H_
