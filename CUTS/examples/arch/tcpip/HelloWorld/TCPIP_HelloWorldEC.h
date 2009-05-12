#ifndef _TCPIP_HELLOWORLDEC_H_
#define _TCPIP_HELLOWORLDEC_H_

#include "cuts/arch/tcpip/TCPIP_Component.h"
#include "cuts/arch/tcpip/TCPIP_Context.h"
#include "TCPIP_HelloWorldC.h"
#include "HelloWorld_exec_export.h"

namespace TCPIP
{
  class HelloWorld_Context;

  typedef CUTS_TCPIP_Var_T <HelloWorld_Context> HelloWorld_Context_var;

  class HELLOWORLD_EXEC_Export HelloWorld_Context :
    public CUTS_TCPIP_Context
  {
  public:
    typedef HelloWorld_Context_var var_type;

    static HelloWorld_Context * _narrow (CUTS_TCPIP_Object * obj);

    HelloWorld_Context (void);

    virtual ~HelloWorld_Context (void);

    virtual void tcpip_handle_message (::Message * ev) = 0;
  };

  class HelloWorld_Exec;

  typedef CUTS_TCPIP_Var_T <HelloWorld_Exec> HelloWorld_Exec_var;

  class HELLOWORLD_EXEC_Export HelloWorld_Exec :
    public CUTS_TCPIP_Component
  {
  public:
    typedef HelloWorld_Exec_var var_type;

    static HelloWorld_Exec * _narrow (CUTS_TCPIP_Object * obj);

    HelloWorld_Exec (void);

    virtual ~HelloWorld_Exec (void);

    virtual void tcpip_handle_message (::Message * ev) = 0;
  };
}

#endif  // !defined _TCPIP_HELLOWORLDEC_H_
