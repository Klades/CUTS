// $Id$

#include "TCPIP_HelloWorldC.h"

namespace TCPIP
{
  Message::Message (void)
  {

  }

  Message::~Message (void)
  {

  }

  TimeValue & Message::time (void)
  {
    return this->time_;
  }

  const TimeValue & Message::time (void) const
  {
    return this->time_;
  }

  void Message::time (const TimeValue & time)
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
}
