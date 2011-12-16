// $Id$

#include "Periodic_Event.h"

#if !defined (__CUTS_INLINE__)
#include "Periodic_Event.inl"
#endif

#include "Exponential_Periodic_Event_Strategy.h"
#include "Constant_Periodic_Event_Strategy.h"
#include "ace/OS_Memory.h"
#include "ace/Trace.h"

//
// configure
//
int CUTS_Periodic_Event::configure (Strategy_Type type, double hertz)
{
  CUTS_Periodic_Event_Strategy * strategy = 0;

  switch (type)
  {
  case PE_UNDEFINED:
    // ingore this case...
    break;

  case PE_EXPONENTIAL:
    ACE_NEW_RETURN (strategy,
                    CUTS_Exponential_Periodic_Event_Strategy (hertz),
                    -1);
    break;

  case PE_CONSTANT:
    ACE_NEW_RETURN (strategy,
                    CUTS_Constant_Periodic_Event_Strategy (hertz),
                    -1);
    break;
  }

  this->strategy_.reset (strategy);
  this->type_ = type;
  return 0;
}

//
// schedule_timeout
//
int CUTS_Periodic_Event::schedule_timeout (const ACE_Time_Value & curr_time)
{
  if (this->strategy_.get () == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - periodic event strategy ")
                       ACE_TEXT ("is not defined\n")),
                       -1);

  // Get the next arrival based on the current time.
  ACE_Time_Value next_arrival (curr_time);
  this->strategy_->next_arrival (next_arrival);

  // Schedule the arrival of the next event.
  this->timer_ = this->timer_queue_.schedule (this, 0, next_arrival);
  return this->timer_ != -1 ? 0 : -1;
}

//
// cancel_timeout
//
void CUTS_Periodic_Event::cancel_timeout (void)
{
  if (this->timer_ == -1)
    return;

  this->timer_queue_.cancel (this->timer_);
  this->timer_ = -1;
}

//
// activate
//
int CUTS_Periodic_Event::activate (void)
{
  // Activate the timer queue, then schedule the first timeout.
  int retval = this->timer_queue_.activate ();

  if (retval != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate timer queue\n")),
                       -1);

  return this->schedule_timeout (ACE_OS::gettimeofday ());
}

//
// deactivate
//
int CUTS_Periodic_Event::deactivate (void)
{
  // Cancel the current timeout.
  this->cancel_timeout ();

  // Deactivate the timer queue and wait for its thread(s) to return.
  this->timer_queue_.deactivate ();
  this->timer_queue_.wait ();

  return 0;
}

//
// handle_timeout
//
int CUTS_Periodic_Event::
handle_timeout (const ACE_Time_Value & curr_time, const void *)
{
  // First, schedule the next timeout event.
  this->schedule_timeout (curr_time);

  // Now, let's handle the timeout event.
  this->handle_timeout_i ();
  return 0;
}
