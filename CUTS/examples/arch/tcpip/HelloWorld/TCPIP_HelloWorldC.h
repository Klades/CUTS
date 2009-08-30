// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLD_H_
#define _TCPIP_HELLOWORLD_H_

#include "HelloWorldC.h"
#include "cuts/arch/tcpip/TCPIP_InputCDR.h"
#include "cuts/arch/tcpip/TCPIP_OutputCDR.h"
#include "HelloWorld_stub_export.h"

ACE_CDR::Boolean HELLOWORLD_STUB_Export operator >> (CUTS_TCPIP_InputCDR &, Message &);
ACE_CDR::Boolean HELLOWORLD_STUB_Export operator << (CUTS_TCPIP_OutputCDR &, const Message &);

ACE_CDR::Boolean HELLOWORLD_STUB_Export operator >> (CUTS_TCPIP_InputCDR &, TimeValue &);
ACE_CDR::Boolean HELLOWORLD_STUB_Export operator << (CUTS_TCPIP_OutputCDR &, const TimeValue &);

#endif  // !defined _TCPIP_HELLOWORLD_H_
