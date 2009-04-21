// -*- C++ -*-

#ifndef _HELLOWORLD_BASIC_IMPL_H_
#define _HELLOWORLD_BASIC_IMPL_H_

#include "TCPIP_HelloWorldEC.h"
#include "HelloWorld_impl_export.h"

class HELLOWORLD_IMPL_Export HelloWorld_Basic_Impl :
  public ::TCPIP::HelloWorld_Exec
{
public:
  HelloWorld_Basic_Impl (void);

  virtual ~HelloWorld_Basic_Impl (void);

  virtual void tcpip_handle_message (TCPIP::Message * ev);
};

#endif  // !defined _HELLOWORLD_BASIC_IMPL_H_
