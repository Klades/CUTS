// $Id:

#include "ButtonImpl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace ButtonImpl
{

//
// Button
//
Button::Button (void)
{
/*  this->periodic_EventCreator_.init (this, &Button::periodic_EventCreator);
  this->periodic_EventCreator_.configure (CUTS_Periodic_Event::PE_CONSTANT, 1);
  this->register_object (&this->periodic_EventCreator_);
*/
}

//
// ~Button
//
Button::~Button (void)
{

}

//
// push_Click
//
void Button::push_Click (::Notify * ev)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("Got notify on Click\n")));

  ::Notify_var __event_100000008__ (this->ctx_->new_SingleClick_event ());
  this->ctx_->push_SingleClick (__event_100000008__.in ());

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("pushing SingleClick\n")));

  ACE_UNUSED_ARG (ev);
}

//
// periodic_EventCreator
//
void Button::periodic_EventCreator (void)
{
  ::Notify_var __event_100000008__ (this->ctx_->new_SingleClick_event ());

  this->ctx_->push_SingleClick (__event_100000008__.in ());
}

}

//
// create_Button_Impl
//
::Components::EnterpriseComponent_ptr
create_Button_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (retval,
                  ::ButtonImpl::Button (),
                  ::Components::EnterpriseComponent::_nil ());

  return retval;
}
