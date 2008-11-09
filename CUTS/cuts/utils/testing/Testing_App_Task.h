// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Event_Handler.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_EVENT_HANDLER_H_
#define _CUTS_TEST_EVENT_HANDLER_H_

#include "cuts/config.h"
#include "ace/Task.h"

/**
 * @class CUTS_Testing_App_Task
 *
 * Event handler for the CUTS_Testing_App class.
 */
class CUTS_Testing_App_Task : protected ACE_Task_Base
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       parent        Parent testing application
   */
  CUTS_Testing_App_Task (void);

  /// Destructor
  virtual ~CUTS_Testing_App_Task (void);

  /**
   * @name Test Management
   *
   * Methods related to the management of a test run.
   */

  // @{

  /**
   * Start a new test.
   */
  int run_test (const ACE_Time_Value & duration);

  int stop_test (void);
  // @}

protected:
  /// Handle the timeout event.
  virtual int handle_timeout (const ACE_Time_Value & tv, const void * act = 0);

  /// The service thread for the task.
  virtual int svc (void);

private:
  /// The active state of the task.
  bool active_;

  /// Id of the timer for the task.
  long timer_id_;
};

#endif  // !defined _CUTS_TEST_EVENT_HANDLER_H_
