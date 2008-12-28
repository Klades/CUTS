// $Id$

#if !defined (__CUTS_INLINE__)
# include "cuts/Trigger_T.inl"
#endif

#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_time.h"
#include "ace/Time_Value.h"

//
// ~CUTS_Periodic_Trigger_T
//
template <typename COMPONENT>
CUTS_Periodic_Trigger_T <COMPONENT>::~CUTS_Periodic_Trigger_T (void)
{

}

//
// activate
//
template <typename COMPONENT>
int CUTS_Periodic_Trigger_T <COMPONENT>::activate (void)
{
  // Activate the timer queue.
  int retval = this->timer_queue_.activate ();

  if (retval == 0)
  {
    // Schedule a timeout interval.
    this->schedule_timeout (this->timeout_);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to activate periodic task\n"));
  }

  return retval;
}

//
// deactivate
//
template <typename COMPONENT>
int CUTS_Periodic_Trigger_T <COMPONENT>::deactivate (void)
{
  this->timer_queue_.deactivate ();
  this->cancel_timeout ();

  return 0;
}

//
// handle_timeout
//
template <typename COMPONENT>
int CUTS_Periodic_Trigger_T <COMPONENT>::
handle_timeout (const ACE_Time_Value & , const void *)
{
  // Calculate the score for this <timeout_> event.
  double score = (double) ACE_OS::rand () / (double) RAND_MAX;

  // invoke the method if the score is within the <probability_>
  if (this->component_ != 0 && this->method_ != 0)
  {
    if (score <= this->probability_)
      (this->component_->*this->method_) ();
  }
  else
  {
    if (this->component_ == 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (Periodic_Trigger): target "
                  "component is not set; ignoring event\n"));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (Periodic_Trigger): target method "
                  "is not set; ignoring event\n"));
    }
  }

  return 0;
}

//
// schedule_timeout
//
template <typename COMPONENT>
void CUTS_Periodic_Trigger_T <COMPONENT>::schedule_timeout (long msec)
{
  if (this->timer_ == -1)
  {
    ACE_Time_Value interval;
    interval.msec (msec);

    ACE_Time_Value abstime =
      this->timer_queue_.timer_queue ()->gettimeofday () + interval;

    this->timer_ = this->timer_queue_.schedule (this, 0, abstime, interval);

    if (this->timer_ == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "[%M] -%T - failed to schedule timer\n"));
    }
  }
  else
  {
    ACE_ERROR ((LM_NOTICE,
                "[%M] -%T - timer has already been scheduled\n"));
  }
}
