// $Id$

#include "BarrierCallback_i.h"

#if !defined (__CUTS_INLINE__)
#include "BarrierCallback_i.inl"
#endif

#include "ace/Guard_T.h"

//
// signal
//
void CUTS_Barrier_Callback_i::signal (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);

  this->retval_ = 0;
  this->is_ready_.signal ();
}

//
// abort
//
void CUTS_Barrier_Callback_i::abort (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);

  this->retval_ = -1;
  this->is_ready_.signal ();
}

//
// wait
//
int CUTS_Barrier_Callback_i::wait (void)
{
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->mutex_, -1);

  // Wait for the condition to become true.
  this->is_ready_.wait ();
  return this->retval_;
}
