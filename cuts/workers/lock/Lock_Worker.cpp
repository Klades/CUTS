// $Id:

#include "Lock_Worker.h"

#if !defined (__CUTS_INLINE__)
#include "Lock_Worker.inl"
#endif

#include "ace/Guard_T.h"

void CUTS_Lock_Worker::wait (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);
  this->cond_.wait ();
}

void CUTS_Lock_Worker::signal (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->mutex_);
  this->cond_.signal ();
}

void CUTS_Lock_Worker::acquire (void)
{
  this->mutex_.acquire ();
}

void CUTS_Lock_Worker::release (void)
{
  this->mutex_.release ();
}
CUTS_WORKER_FACTORY_EXPORT_IMPL (CUTS_Lock_Worker);
