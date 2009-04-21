// $Id$

#include "TCPIP_HelloWorldC.h"
#include "ace/CDR_Stream.h"

namespace TCPIP
{
  /////////////////////////////////////////////////////////////////////////////
  // TimeValue

  ACE_CDR::Boolean operator << (ACE_OutputCDR & stream, TimeValue & rhs)
  {
    stream << rhs.sec;
    stream << rhs.usec;

    return stream.good_bit ();
  }

  ACE_CDR::Boolean operator >> (ACE_InputCDR & stream, TimeValue & rhs)
  {
    stream >> rhs.sec;
    stream >> rhs.usec;

    return stream.good_bit ();
  }

  /////////////////////////////////////////////////////////////////////////////
  // Message

  Message::Message (void)
  {

  }

  Message::~Message (void)
  {

  }

  ::TCPIP::TimeValue & Message::time (void)
  {
    return this->time_;
  }

  const ::TCPIP::TimeValue & Message::time (void) const
  {
    return this->time_;
  }

  void Message::time (const ::TCPIP::TimeValue & time)
  {
    this->time_ = time;
  }

  ACE_CString & Message::message (void)
  {
    return this->message_;
  }

  const ACE_CString & Message::message (void) const
  {
    return this->message_;
  }

  void Message::message (const char * message)
  {
    this->message_ = message;
  }

  ACE_CDR::Boolean operator << (ACE_OutputCDR & stream, Message & rhs)
  {
    stream << rhs.time_;
    stream << rhs.message_;

    return stream.good_bit ();
  }

  ACE_CDR::Boolean operator >> (ACE_InputCDR & stream, Message & rhs)
  {
    stream >> rhs.time_;
    stream >> rhs.message_;

    return stream.good_bit ();
  }
}

