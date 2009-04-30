// -*- C++ -*-

#ifndef _HELLOWORLD_BASIC_IMPL_H_
#define _HELLOWORLD_BASIC_IMPL_H_

#include "TCPIP_HelloWorldEC.h"
#include "HelloWorld_impl_export.h"

class HELLOWORLD_IMPL_Export HelloWorld_Basic_Impl :
  public TCPIP::HelloWorld_Exec
{
public:
  HelloWorld_Basic_Impl (void);

  virtual ~HelloWorld_Basic_Impl (void);

  virtual void tcpip_handle_message (TCPIP::Message * ev);

  virtual void set_session_context (CUTS_TCPIP_Context * ctx);

  virtual void configuration_complete (void);

  virtual void ccm_activate (void);

  virtual void ccm_passivate (void);

  virtual void ccm_remove (void);

private:
  /// The context for the component.
  TCPIP::HelloWorld_Context_var ctx_;
};

#endif  // !defined _HELLOWORLD_BASIC_IMPL_H_
