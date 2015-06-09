// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLD_COMPONENTSC_H_
#define _TCPIP_HELLOWORLD_COMPONENTSC_H_

#include "HelloWorld_ComponentsC.h"
#include "cuts/iccm/arch/tcpip/stub/TCPIP_OutputCDR.h"
#include "cuts/iccm/arch/tcpip/servant/TCPIP_Event.h"

#include "HelloWorld_Components_stub_export.h"

//
// Output Operators
//
HELLOWORLD_COMPONENTS_STUB_Export ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR &, const ::MessageEvent &);

//
// Input Operators
//
HELLOWORLD_COMPONENTS_STUB_Export ACE_CDR::Boolean operator >> (ACE_InputCDR &, ::MessageEvent &);

/**
 * @struct iCCM::TCPIP_Event_Traits < ::MessageEvent >
 *
 * Trait information for MessageEventEvent event type.
 */
namespace iCCM 
{
  template < >
  struct TCPIP_Event_Traits < ::MessageEvent >
  {
    typedef ::OBV_MessageEvent tcpip_event_type;
  };
}

#endif  // !defined _TCPIP_HELLOWORLD_COMPONENTSC_H_