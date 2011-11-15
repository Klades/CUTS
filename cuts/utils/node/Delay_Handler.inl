// -*- C++ -*-
// $Id$

//
// wait_for_delay_completion
//
CUTS_INLINE
int CUTS_Delay_Handler::
wait_for_delay_completion (ACE_Time_Value * abstime)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->mutex_, -1);
  return this->is_ready_.wait (abstime);
}
