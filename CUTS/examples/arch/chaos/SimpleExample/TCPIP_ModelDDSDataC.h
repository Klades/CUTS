// -*- C++ -*-

#ifndef _TCPIP_MODELDDSDATA_H_
#define _TCPIP_MODELDDSDATA_H_

#include "ModelDDSDataC.h"
#include "cuts/arch/tcpip/TCPIP_InputCDR.h"
#include "cuts/arch/tcpip/TCPIP_OutputCDR.h"
#include "ModelDDSData_stub_export.h"

namespace Outer
{
  ACE_CDR::Boolean MODELDDSDATA_STUB_Export operator >> (CUTS_TCPIP_InputCDR &, TestData_DDS &);
  ACE_CDR::Boolean MODELDDSDATA_STUB_Export operator << (CUTS_TCPIP_OutputCDR &, const TestData_DDS &);

  namespace Inner
  {
    ACE_CDR::Boolean MODELDDSDATA_STUB_Export operator >> (CUTS_TCPIP_InputCDR &, Data_DDS &);
    ACE_CDR::Boolean MODELDDSDATA_STUB_Export operator << (CUTS_TCPIP_OutputCDR &, const Data_DDS &);
  }
}

#endif  // !defined _TCPIP_MODELDDSDATA_H_
