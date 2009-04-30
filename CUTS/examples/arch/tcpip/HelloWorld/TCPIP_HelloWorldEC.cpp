// $Id$

#include "TCPIP_HelloWorldEC.h"

namespace TCPIP
{
  HelloWorld_Context::HelloWorld_Context (void)
  {

  }

  HelloWorld_Context::~HelloWorld_Context (void)
  {

  }

  HelloWorld_Context * HelloWorld_Context::_narrow (CUTS_TCPIP_Object * obj)
  {
    HelloWorld_Context * ptr = dynamic_cast <HelloWorld_Context *> (obj);

    if (0 != ptr)
      ptr->incr_refcount ();

    return ptr;
  }

  HelloWorld_Exec::HelloWorld_Exec (void)
  {

  }

  HelloWorld_Exec::~HelloWorld_Exec (void)
  {

  }

  HelloWorld_Exec * HelloWorld_Exec::_narrow (CUTS_TCPIP_Object * obj)
  {
    HelloWorld_Exec * ptr = dynamic_cast <HelloWorld_Exec *> (obj);

    if (0 != ptr)
      ptr->incr_refcount ();

    return ptr;
  }
}
