#ifndef _TCPIP_HELLOWORLDEC_H_
#define _TCPIP_HELLOWORLDEC_H_

#include "cuts/arch/tcpip/TCPIP_Object_T.h"
#include "cuts/arch/tcpip/TCPIP_Var_T.h"
#include "TCPIP_HelloWorldC.h"
#include "HelloWorld_exec_export.h"

namespace TCPIP
{
  class HelloWorld_Exec;

  typedef CUTS_TCPIP_Var_T <HelloWorld_Exec> HelloWorld_Exec_var;

  class HELLOWORLD_EXEC_Export HelloWorld_Exec :
    public CUTS_TCPIP_MT_Object
  {
  public:
    typedef HelloWorld_Exec_var var_type;

    HelloWorld_Exec (void);

    virtual ~HelloWorld_Exec (void);

    virtual void tcpip_handle_message (TCPIP::Message * ev) = 0;
  };
}

#endif  // !defined _TCPIP_HELLOWORLDEC_H_
