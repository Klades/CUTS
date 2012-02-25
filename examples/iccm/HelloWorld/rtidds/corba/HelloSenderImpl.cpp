// This file was generated by:
// $Id$

#include "HelloSenderImpl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace HelloSenderImpl
{
  //
  // HelloSender
  //
  HelloSender::HelloSender (void)
  {
    this->periodic_EventCreator_.init (this, &HelloSender::periodic_EventCreator);
    this->periodic_EventCreator_.configure (CUTS_Periodic_Event::PE_CONSTANT, 1);
    this->register_object (&this->periodic_EventCreator_);
  }

  //
  // ~HelloSender
  //
  HelloSender::~HelloSender (void)
  {
  }

  //
  // PeriodicEvent: EventCreator
  //
  void HelloSender::periodic_EventCreator (void)
  {
    ::MessageEvent_var __event_100000008__ (this->ctx_->new_greeting_event ());
    __event_100000008__->content (this->message_.c_str ());

    this->ctx_->push_greeting (__event_100000008__.in ());
  }

  //
  // attribute setter: message
  //
  void HelloSender::message (const char * message)
  {
    this->message_ = message;
  }

  //
  // attribute getter: message
  //
  char * HelloSender::message (void)
  {
    ::CORBA::String_var s =
      ::CORBA::string_dup (this->message_.c_str ());
    return s._retn ();
  }
}

//
// create_HelloSender_Impl
//
::Components::EnterpriseComponent_ptr
create_HelloSender_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval,
                  ::HelloSenderImpl::HelloSender (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}


// end of auto-generated file

