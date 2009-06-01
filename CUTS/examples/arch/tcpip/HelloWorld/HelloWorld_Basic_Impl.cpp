// $Id$

#include "HelloWorld_Basic_Impl.h"

//
// HelloWorld_Basic_Impl
//
HelloWorld_Basic_Impl::HelloWorld_Basic_Impl (void)
: eventCount_ (0),
  isActive_ (true)
{
}

//
// ~HelloWorld_Basic_Impl
//
HelloWorld_Basic_Impl::~HelloWorld_Basic_Impl (void)
{
}

//
// push_handle_message
//
void HelloWorld_Basic_Impl::push_handle_message (::Message * ev)
{
  ACE_UNUSED_ARG (ev);
}

//
// message
//
void HelloWorld_Basic_Impl::message (const char * message)
{
  this->message_ = message;
}

//
// message
//
char * HelloWorld_Basic_Impl::message (void)
{
  ::CORBA::String_var s =
    ::CORBA::string_dup (this->message_.c_str ());
  return s._retn ();
}

//
// readonly_message
//
char * HelloWorld_Basic_Impl::readonly_message (void)
{
  ::CORBA::String_var s =
    ::CORBA::string_dup (this->readonly_message_.c_str ());
  return s._retn ();
}

//
// ccm_activate
//
void HelloWorld_Basic_Impl::ccm_activate (void)
{
}

