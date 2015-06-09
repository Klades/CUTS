// $Id$

#include "TCPIP_HelloWorld_ComponentsC.h"

//
// Output stream operator for ::MessageEvent
//
ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const ::MessageEvent & ev)
{
  stream << ev.content ();
  stream << ev.time ();
  return stream.good_bit ();
}

//
// Input stream operator for ::MessageEvent
//
ACE_CDR::Boolean operator >> (ACE_InputCDR & stream, ::MessageEvent & ev)
{
  ACE_CString _var_300000000;
  stream >> _var_300000000;
  ev.content (_var_300000000.c_str ());

  CORBA::Long _var_300000001;
  stream >> _var_300000001;
  ev.time (_var_300000001);

  return stream.good_bit ();
}

