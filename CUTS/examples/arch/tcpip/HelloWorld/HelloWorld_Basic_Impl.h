// -*- C++ -*-

#ifndef _HELLOWORLD_BASIC_IMPL_H_
#define _HELLOWORLD_BASIC_IMPL_H_

#include "TCPIP_HelloWorldEC.h"
#include "HelloWorld_impl_export.h"
#include "ace/Task.h"

class HelloWorld_Basic_Impl;

class HelloWorld_Basic_Impl_Task : public ACE_Task_Base
{
public:
  HelloWorld_Basic_Impl_Task (HelloWorld_Basic_Impl * impl);

  virtual ~HelloWorld_Basic_Impl_Task (void);

  int svc (void);

  int handle_timeout (const ACE_Time_Value &, const void *);

  int activate (void);

  int deactivate (void);

private:
  HelloWorld_Basic_Impl * impl_;

  bool is_active_;
};

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

  HelloWorld_Basic_Impl_Task task_;
};

#endif  // !defined _HELLOWORLD_BASIC_IMPL_H_
