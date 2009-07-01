// $Id $

#include "Delay_Handler.h"

//
// CUTS_Delay_Handler
//
CUTS_Delay_Handler::
CUTS_Delay_Handler (ACE_Barrier * delay_end_barrier)
: timer_queue_ (),
  delay_end_barrier_ (delay_end_barrier),
  active_ (false)
{
}

//
// ~CUTS_Delay_Handler
//
CUTS_Delay_Handler::~CUTS_Delay_Handler (void)
{
  if (this->active_)
  {
    this->timer_queue_.deactivate ();
  }
}

//
// schedule
//
long CUTS_Delay_Handler::schedule (double delay)
{
  // If the object is activated, schedule the delay.

  if (this->active_)
  {
    ACE_Time_Value timeout;
    timeout.set (delay);

    ACE_Time_Value cur_time = ACE_OS::gettimeofday ();

    return this->timer_queue_.schedule (this, 0, cur_time + timeout);
  }

  return -1;
}

//
// handle_exit
//
int CUTS_Delay_Handler::handle_exit (ACE_Process * process)
{
  ACE_UNUSED_ARG (process);
  return this->delay_end_barrier_->wait ();
}

//
// handle_timeout
//
int CUTS_Delay_Handler::
handle_timeout (const ACE_Time_Value & tv, const void * act)
{
  ACE_UNUSED_ARG (tv);
  ACE_UNUSED_ARG (act);

  return this->delay_end_barrier_->wait ();
}

//
// activate
//
int CUTS_Delay_Handler::activate (void)
{
  ACE_Task_Base::activate ();

  int retval = timer_queue_.activate ();
  this->active_ = retval != -1;
  return retval;
}

//
// deactivate
//
void CUTS_Delay_Handler::deactivate (void)
{
  timer_queue_.deactivate ();
  this->close ();
  this->active_ = false;
}
