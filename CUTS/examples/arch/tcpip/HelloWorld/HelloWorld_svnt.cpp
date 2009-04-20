// $Id$

#include "HelloWorld_svnt.h"

#if !defined (__CUTS_INLINE__)
#include "HelloWorld_svnt.inl"
#endif

#include "TCPIP_HelloWorldC.h"

namespace CUTS_TCPIP
{
  //
  // HelloWorld_svnt
  //
  HelloWorld_svnt::
  HelloWorld_svnt (TCPIP::HelloWorld_Exec * impl)
    : servant_type (this),
      impl_ (impl)
  {
    // Guard the initializing of the virtual table.
    vtable_type::init_guard_type guard (HelloWorld_svnt::vtable_, 1);

    if (HelloWorld_svnt::vtable_.is_init ())
      return;

    // Initialize the virtual table for the servant.
    HelloWorld_svnt::vtable_[0] = &HelloWorld_svnt::tcpip_handle_message;
  }

  //
  // tcpip_handle_message
  //
  int HelloWorld_svnt::
  tcpip_handle_message (ACE_Message_Block & mb)
  {
    TCPIP::Message_var event;
    ACE_NEW_RETURN (event, TCPIP::Message (), -1);

    // Store the event in a smart pointer for reference counting.

    // Extract the contents of the message.

    // Push the message to the implementation.
    if (this->impl_)
      this->impl_->tcpip_handle_message (event);

    return 0;
  }
}
