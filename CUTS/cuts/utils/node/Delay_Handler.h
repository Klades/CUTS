/* -*- C++ -*- */

//=============================================================================
/**
* @file      Delay_Handler.h
*
* $Id$
*
* @author    Pooja Varshneya
*/
//=============================================================================

#ifndef _CUTS_DELAY_HANDLER_H_
#define _CUTS_DELAY_HANDLER_H_

#include "ace/Condition_T.h"
#include "ace/Task.h"
#include "ace/Thread_Mutex.h"
#include "cuts/config.h"

/**
* @class CUTS_Delay_Handler
*
* This class implements the delay functionality. Whenever cutsnode
* deamon needs to be blocked for <delay> seconds, Delay_Handler
* schedules the timer queue and on receiving the timeout event,
* lets the barrier synchronize the delay_handler thread with the main
* thread in Node_Daemon_i class.
*/
class CUTS_Delay_Handler : public ACE_Task_Base
{
public:
  /// Default constructor
  CUTS_Delay_Handler (void);

  /// Destructor
  virtual ~CUTS_Delay_Handler (void);

  /// Schedules the timer.
  int schedule (double delay);

  /// Callback routine for handling timeout.
  virtual int handle_timeout (const ACE_Time_Value & tv, const void * act);

  /// Callback routine for handling process termination.
  virtual int handle_exit (ACE_Process * process);

  /// Service handler routine.
  virtual int svc (void);

  void close (void);

  int wait_for_delay_completion (ACE_Time_Value * abstime = 0);

private:
  /// Mutex for controlling access.
  ACE_Thread_Mutex mutex_;

  /// Condition variable for sychronizing threads.
  ACE_Condition <ACE_Thread_Mutex> is_ready_;

  /// Timer id for the delay task.
  long timer_id_;
};

#if defined (__CUTS_INLINE__)
#include "Delay_Handler.inl"
#endif

#endif  /* !defined _CUTS_DELAY_HANDLER_H_ */

