// $Id$

#include "TCPIP_HelloWorldC.h"

/////////////////////////////////////////////////////////////////////////////
// ::TimeValue

ACE_CDR::Boolean operator << (ACE_OutputCDR & stream, ::TimeValue & rhs)
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

/////////////////////////////////////////////////////////////////////////////
// ::Message

ACE_CDR::Boolean operator << (ACE_OutputCDR & stream, ::Message & rhs)
{
  stream << rhs.time ();
  stream << rhs.content ();

  return stream.good_bit ();
}

ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, ::Message & rhs)
{
  // extract the <time> value.
  stream >> rhs.time ();

  // extract the <content> value.
  ACE_CString content;
  stream >> content;
  rhs.content (content.c_str ());

  return stream.good_bit ();
}

