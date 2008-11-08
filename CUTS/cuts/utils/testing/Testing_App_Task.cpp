// $Id$

#include "Test_export.h"
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

  this->parent_.shutdown ();
  return 0;
}

//
// svc
//
int CUTS_Testing_App_Task::svc (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::svc (void)");

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - running application task's thread\n"));

  this->reactor ()->owner (ACE_OS::thr_self ());

  while (this->active_)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - waiting for the next event\n"));

    this->reactor ()->handle_events ();
  }

  return 0;
}

//
// start
//
int CUTS_Testing_App_Task::start (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::start (void)");

  this->active_ = true;

  if (this->activate () == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to activate testing application task\n"));

    this->active_ = false;
  }
  return 0;
}

//
// stop
//
int CUTS_Testing_App_Task::stop (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::stop (void)");

  if (this->active_)
  {
    // Toggle the active state of the task.
    this->active_ = false;

    // Signal the thread to handle an event and wait for it to exit.
    this->reactor ()->notify (this);
    this->wait ();
  }

  return 0;
}

//
// start_test
//
long CUTS_Testing_App_Task::start_test (const ACE_Time_Value & duration)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::start_test (const ACE_Time_Value &)");

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
  CUTS_TEST_TRACE ("CUTS_Testing_App_Task::stop_test (long)");

  return this->reactor ()->cancel_timer (test_id);
}
