//  $Id$

#include "ClickTask.h"
#include "ButtonImpl.h"

#include "ace/Reactor.h"

//
// ClickTask
//
ClickTask::ClickTask (::ButtonImpl::Button * button)
: button_ (button),
  is_active_ (false),
  timer_id_ (-1),
  timeout_count_ (0)
{
  ACE_Reactor * reactor = 0;

  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    ACE_bad_alloc ());

  this->reactor (reactor);
}

//
// ~ClickTask
//
ClickTask::~ClickTask (void)
{
  std::auto_ptr <ACE_Reactor> auto_clean (this->reactor ());
  this->reactor (0);
}

//
// activate
//
int ClickTask::activate (const ACE_Time_Value & interval)
{
  if (this->is_active_)
    return this->timer_id_;

  // Activate the task
  if (0 != ACE_Task_Base::activate ())
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate ")
                ACE_TEXT ("ClickTask\n")));

  // Schedule the timer for the heartbeat.
  this->timer_id_ =
    this->reactor ()->schedule_timer (this,
                                      0,
                                      ACE_Time_Value::zero,
                                      interval);

  if (this->timer_id_ == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to schedule timer for ")
                ACE_TEXT ("ClickTask\n")));

  this->is_active_ = true;

  return this->timer_id_;
}

//
// deactivate
//
int ClickTask::deactivate (void)
{
  if (!this->is_active_)
    return 0;

  // Toggle the active flag.
  this->is_active_ = false;

  // Wakeup the thread and wait for it to exit.
  this->reactor ()->notify (this);
  this->wait ();

  if (this->timer_id_ != -1)
  {
    // Finally, cancel the timer.
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;
  }

  // Reset the timeout count
  this->timeout_count_ = 0;

  return 0;
}

//
// svc
//
int ClickTask::svc (void)
{
  try
  {
    // Set the reactor's owner.
    this->reactor ()->owner (ACE_OS::thr_self ());

    // Keep processing events while we are active.
    while (this->is_active_)
      this->reactor ()->handle_events ();

    return 0;
  }
  catch (...)
  {
    return -1;
  }
}

//
// handle_timeout
//
int ClickTask::
handle_timeout (const ACE_Time_Value & , const void * )
{
  // handle_timeout is called when the task is activated, we want to skip
  // the first call since we do not want the ButtonImpl to respond immediately
  if (0 == this->button_ || 0 == this->timeout_count_)
  {
    ++ this->timeout_count_;
    return 0;
  }

  // Signal the Button to decide what click event to send
  this->button_->decide_action ();

  return 0;
}
