// $Id:

#include "ButtonImpl.h"
#include "cuts/arch/ccm/CCM_Events_T.h"

namespace ButtonImpl
{

//
// Button
//
Button::Button (void)
: click_count_ (0),
  task_ (this)
{
  // initalize task_timeout_
  timespec_t timeout;
  timeout.tv_nsec = 20 * 10000 * 1000; // hard coded for 20 * reporter timeunit (10000us)
  this->task_timeout_.set (timeout);

  // activate the task
  this->task_.activate ();
}

//
// ~Button
//
Button::~Button (void)
{
  this->task_.deactivate ();
}

//
// push_Click
//
void Button::push_Click (::Notify * ev)
{
  // Activate the task if this is the first click received
  if (0 == this->click_count_)
    this->task_.reschedule (this->task_timeout_);

  // Increment the click count
  ++ this->click_count_;

  // If click_count is 2, then a double click must be sent immediately
  if (2 == this->click_count_)
    this->decide_action ();

  ACE_UNUSED_ARG (ev);
}

//
// decide_action
//
void Button::decide_action (void)
{
  this->task_.cancel_timer ();

  if (0 == this->click_count_)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - decide_action called with no clicks received\n")));
  }
  else if (1 == this->click_count_)
  {
    ::Notify_var __event_100000008__ (this->ctx_->new_SingleClick_event ());
    this->ctx_->push_SingleClick (__event_100000008__.in ());
  }
  else if (1 < this->click_count_)
  {
    ::Notify_var __event_100000008__ (this->ctx_->new_DoubleClick_event ());
    this->ctx_->push_DoubleClick (__event_100000008__.in ());
  }

  this->click_count_ = 0;
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
