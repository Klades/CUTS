// $Id$

#include "TCPIP_HelloWorldC.h"

ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, ::TimeValue & rhs)
{
  stream << rhs.sec;
  stream << rhs.usec;

  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, ::TimeValue & rhs)
{
  stream >> rhs.sec;
  stream >> rhs.usec;

  return stream.good_bit ();
}

ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, ::Message & rhs)
{
  stream << rhs.time ();
  stream << rhs.content ();

  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, ::Message & rhs)
{
  stream >> rhs.time ();

  ACE_CString content;
  stream >> content;
  rhs.content (content.c_str ());

  return stream.good_bit ();
}

