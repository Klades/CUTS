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

#include "Testing_Base_export.h"
#include "ace/Task.h"

// Forward decl.
class CUTS_Testing_App;

/**
 * @class CUTS_Testing_App_Task
 *
 * Event handler for the CUTS_Testing_App class.
 */
class CUTS_TESTING_BASE_Export CUTS_Testing_App_Task : protected ACE_Task_Base
{
public:
  CUTS_Testing_App_Task (CUTS_Testing_App & parent);

  virtual ~CUTS_Testing_App_Task (void);

  /**
   * Start the task. This will allow the task to respond to events of 
   * interest, such as timeout events for executing tests.
   */
  int start (void);

  /**
   * Stop the application task. It will not longer be able to respond
   * to events of interest.
   */
  int stop (void);

  /**
   * @name Test Management
   *
   * Methods related to the management of a test run.
   */

  // @{

  /**
   * Start a new test.
   */
  long start_test (const ACE_Time_Value & duration);

  long stop_test (long test_id);
  // @}

protected:
  /// Handle the timeout event.
  virtual int handle_timeout (const ACE_Time_Value & tv, const void * act = 0);

  /// The service thread for the task.
  virtual int svc (void);

private:
  /// The parent of the event handler.
  CUTS_Testing_App & parent_;

  /// The active state of the task.
  bool active_;
};

#endif  // !defined _CUTS_TEST_EVENT_HANDLER_H_
