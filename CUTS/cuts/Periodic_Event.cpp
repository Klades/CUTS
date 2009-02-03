// $Id$

#include "Periodic_Event.h"

#if !defined (__CUTS_INLINE__)
#include "Periodic_Event.inl"
#endif

#include "Exponential_Periodic_Event_Strategy.h"
#include "Constant_Periodic_Event_Strategy.h"
#include "ace/OS_Memory.h"

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
  return 0;
}

//
// schedule_timeout
//
int CUTS_Periodic_Event::schedule_timeout (const ACE_Time_Value & curr_time)
{
  // Do we really next to cancel the current timeout??
  if (this->timer_ != -1)
    this->cancel_timeout ();


  if (this->strategy_.get () != 0)
  {
    // Get the next arrival based on the current time.
    ACE_Time_Value next_arrival (curr_time);
    this->strategy_->next_arrival (next_arrival);

    // Schedule the arrival of the next event.
    this->timer_ = this->timer_queue_.schedule (this, 0, next_arrival);

    if (this->timer_ == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to schedule next timeout\n"),
                         -1);
  }
  else
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - periodic strategy not set\n"),
                       -1);

  return 0;
}

//
// cancel_timeout
//
void CUTS_Periodic_Event::cancel_timeout (void)
{
  if (this->timer_ != -1)
  {
    this->timer_queue_.cancel (this->timer_);
    this->timer_ = -1;
  }
}

//
// activate
//
int CUTS_Periodic_Event::activate (void)
{
  // Activate the timer queue.
  int retval = this->timer_queue_.activate ();

  if (retval == 0)
    this->schedule_timeout (ACE_OS::gettimeofday ());
  else
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to activate periodic task\n"));

  return retval;
}

//
// deactivate
//
int CUTS_Periodic_Event::deactivate (void)
{
  this->timer_queue_.deactivate ();
  this->cancel_timeout ();

  return 0;
}

//
// handle_timeout
//
int CUTS_Periodic_Event::
handle_timeout (const ACE_Time_Value & timeout, const void *)
{
  // First, schedule the next timeout event. This should be
  // on the order of microseconds.
  ACE_Time_Value next_arrival (timeout);

  this->schedule_timeout (timeout);
  this->handle_timeout_i ();
  return 0;
}
