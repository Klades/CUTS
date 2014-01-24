// $Id$

#include "Application_Task.h"

#if !defined (__CUTS_INLINE__)
#include "Application_Task.inl"
#endif

#include "ace/Reactor.h"
#include "ace/CORBA_macros.h"

CUTS_Application_Task::CUTS_Application_Task (void)
: nthreads_ (1),
  active_ (false)
{

}

int CUTS_Application_Task::activate (void)
{
  int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
  int retval = ACE_Task_Base::activate (flags, this->nthreads_);

  if (retval == 0)
    this->active_ = true;
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate application task\n")));

  return retval;
}

//
// deactivate
//
int CUTS_Application_Task::deactivate (void)
{
  if (!this->active_)
    return 0;

  // Toggle the active flag.
  this->active_ = false;
  this->wait ();
  return 0;
}
