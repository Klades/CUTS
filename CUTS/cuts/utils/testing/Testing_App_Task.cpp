// $Id$

#include "Test_export.h"
#include "Testing_App_Task.h"
#include "Testing_App.h"
#include "ace/CORBA_macros.h"
#include "ace/TP_Reactor.h"

//
// CUTS_Testing_App_Task
//
CUTS_Testing_App_Task::CUTS_Testing_App_Task (void)
: active_ (false),
  timer_id_ (-1)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::CUTS_Testing_App_Task (CUTS_Testing_App &)");

  // Create the reactor for the task.
  ACE_Reactor * reactor = 0;

  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    ACE_bad_alloc ());

  this->reactor (reactor);
}

//
// ~CUTS_Testing_App_Task
//
CUTS_Testing_App_Task::~CUTS_Testing_App_Task (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::~CUTS_Testing_App_Task (void)");

  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  delete reactor;
}

//
// handle_timeout
//
int CUTS_Testing_App_Task::
handle_timeout (const ACE_Time_Value & tv, const void * act)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::handle_timeout (const ACE_Time_Value &, const void *)");

  // Toggle the active flag for the task.
  this->active_ = false;
  return 0;
}

//
// svc
//
int CUTS_Testing_App_Task::svc (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::svc (void)");

  // Set the reactor's owner to this thread.
  this->reactor ()->owner (ACE_OS::thr_self ());

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - running testing application's event loop\n"));

  while (this->active_)
    this->reactor ()->handle_events ();

  return 0;
}

//
// start_test
//
int CUTS_Testing_App_Task::run_test (const ACE_Time_Value & duration)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::start_test (const ACE_Time_Value &)");

  if (!this->active_)
  {
    // Set the active flag for the task.
    this->active_ = true;

    if (this->activate () == -1)
    {
      // Reset the active flag for the task
      this->active_ = false;

      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to activate testing "
                         "applcation task\n"),
                         -1);
    }
  }

  // Schedule the timer for the test.
  this->timer_id_ =
    this->reactor ()->schedule_timer (this,
                                      0,
                                      duration);

  // Wait for the test to end. This means waiting for the spawned
  // thread to return.
  return this->wait ();
}

//
// stop_test
//
int CUTS_Testing_App_Task::stop_test (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::stop_test (long)");

  if (this->timer_id_ != -1)
  {
    // Cancel the timer for the task.
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;
  }

  // Toggle the active flag for the task.
  if (this->active_)
    this->active_ = false;

  // Notify the task, which will end the event loop.
  this->reactor ()->notify (this);
  this->wait ();

  return 0;
}
