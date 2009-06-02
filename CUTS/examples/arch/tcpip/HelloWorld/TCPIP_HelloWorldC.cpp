// $Id$

#include "TCPIP_HelloWorldC.h"


ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const TimeValue & val)
{
  stream << val.sec;
  stream << val.usec;
  return stream.good_bit ();
}

ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const Message & ev)
{
  stream << ev.time ();
  stream << ev.content ();
  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, TimeValue & val)
{
  stream >> val.sec;
  stream >> val.usec;
  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, Message & ev)
{
  stream >> ev.time ();

  // extracting member content
  ACE_CString _300000016;
  stream >> _300000016;
  ev.content (_300000016.c_str ());
  return stream.good_bit ();
}

