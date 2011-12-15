// $Id$

#include "TCPIP_HelloWorldC.h"


ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const ::TimeValue & val)
{
  stream << val.sec;
  stream << val.usec;
  return stream.good_bit ();
}

ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const ::Message & ev)
{
  stream << ev.content ();
  stream << ev.time ();
  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (ACE_InputCDR & stream, ::TimeValue & val)
{
  stream >> val.sec;
  stream >> val.usec;
  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (ACE_InputCDR & stream, ::Message & ev)
{
  ACE_CString _val_300000018;
  stream >> _val_300000018;
  ev.content (_val_300000018.c_str ());

  stream >> ev.time ();
  return stream.good_bit ();
}

