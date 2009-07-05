// $Id$

#include "Delay_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "Delay_Handler.inl"
#endif

#include "ace/Reactor.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Delay_Handler
//
CUTS_Delay_Handler::CUTS_Delay_Handler (void)
: is_ready_ (mutex_)
{
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    ACE_bad_alloc ());

  this->reactor (reactor);
}

//
// ~CUTS_Delay_Handler
//
CUTS_Delay_Handler::~CUTS_Delay_Handler (void)
{
  // Close the handler.
  this->close ();

  // Delete the reactor.
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  delete reactor;
}

//
// close
//
void CUTS_Delay_Handler::close (void)
{
  // Make sure the reactors event loop is done.
  if (!this->reactor ()->reactor_event_loop_done ())
    this->reactor ()->end_reactor_event_loop ();

  // Wait for all threads to exit.
  this->wait ();
}

//
// schedule
//
int CUTS_Delay_Handler::schedule (double d)
{
  // Schedule the delay with the reactor.
  ACE_Time_Value delay;
  delay.set (d);

  return this->schedule (delay);
}

//
// schedule
//
int CUTS_Delay_Handler::schedule (const ACE_Time_Value & delay)
{
  this->timer_id_ = this->reactor ()->schedule_timer (this, 0, delay);
  return -1 != this->timer_id_ ? 0 : -1;
}

//
// handle_exit
//
int CUTS_Delay_Handler::handle_exit (ACE_Process *)
{
  ACE_ERROR ((LM_WARNING,
              ACE_TEXT ("%T (%t) - %M - process finished before delay\n")));

  // First, cancel the timer.
  this->reactor ()->cancel_timer (this->timer_id_);
  this->timer_id_ = -1;

  // Notify all threads waiting for timeout to complete.
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->mutex_, -1);
  this->is_ready_.broadcast ();

  return 0;
}

//
// handle_timeout
//
int CUTS_Delay_Handler::
handle_timeout (const ACE_Time_Value & , const void * )
{
  // Reset the timer id.
  this->timer_id_ = -1;

  // Notify all threads waiting for timeout to complete.
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->mutex_, -1);
  this->is_ready_.broadcast ();

  return 0;
}

//
// svc
//
int CUTS_Delay_Handler::svc (void)
{
  // Set the owner of the reactor.
  this->reactor ()->owner (ACE_OS::thr_self ());

  if (-1 == this->reactor ()->run_reactor_event_loop ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to run reactor event loop\n")),
                       -1);

  return 0;
}
