// $Id$

#include "Testing_App_Task.h"
#include "Testing_App.h"
#include "ace/CORBA_macros.h"
#include "ace/TP_Reactor.h"

//
// CUTS_Testing_App_Task
//
CUTS_Testing_App_Task::CUTS_Testing_App_Task (CUTS_Testing_App & parent)
: parent_ (parent),
  active_ (false)
{
  // Create the thread pool reactor for the task.
  ACE_TP_Reactor * tp_reactor = 0;

  ACE_NEW_THROW_EX (tp_reactor,
                    ACE_TP_Reactor (),
                    ACE_bad_alloc ());
  
  ACE_Auto_Ptr <ACE_TP_Reactor> auto_clean (tp_reactor);

  // Setup the auto clean just in case the next allocation fails.
  ACE_Reactor * reactor = 0;
  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (tp_reactor, 1),
                    ACE_bad_alloc ());

  this->reactor (reactor);
  auto_clean.release ();
}

//
// ~CUTS_Testing_App_Task
//
CUTS_Testing_App_Task::~CUTS_Testing_App_Task (void)
{

}

//
// handle_timeout
//
int CUTS_Testing_App_Task::
handle_timeout (const ACE_Time_Value & tv, const void * act)
{
  this->parent_.shutdown ();
  return 0;
}

//
// svc
//
int CUTS_Testing_App_Task::svc (void)
{
  //this->reactor ()->owner (ACE_OS::thr_self ());

  while (this->active_)
    this->reactor ()->handle_events ();

  return 0;
}

//
// start
//
int CUTS_Testing_App_Task::start (void)
{
  this->active_ = true;
 
  if (this->activate () == -1)
    this->active_ = false;

  return 0;
}

//
// stop
//
int CUTS_Testing_App_Task::stop (void)
{
  if (this->active_)
  {
    // Toggle the active state of the task.
    this->active_ = false;

    // Signal the thread to handle an event and wait for it to exit.
    this->reactor ()->notify ();
    this->wait ();
  }

  return 0;
}

//
// start_test
//
long CUTS_Testing_App_Task::start_test (const ACE_Time_Value & duration)
{
  return 
    this->reactor ()->schedule_timer (this, 
                                      0, 
                                      duration);
}

//
// start_test
//
long CUTS_Testing_App_Task::stop_test (long test_id)
{
  return this->reactor ()->cancel_timer (test_id);
}
