// $Id$

#include "HelloWorld_svnt.h"

#if !defined (__CUTS_INLINE__)
#include "HelloWorld_svnt.inl"
#endif

namespace CUTS_TCPIP
{
  //
  // HelloWorld_svnt
  //
  HelloWorld_svnt::HelloWorld_svnt (void)
    : servant_type (this, 1)
  {
    this->vtable_[0] = &HelloWorld_svnt::tcpip_handle_message;
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_svnt::
  tcpip_handle_message (ACE_Message_Block & ev)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - I received a message!!\n"));

    return 0;
  }
}
