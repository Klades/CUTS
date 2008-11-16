// -*- C++ -*-

//=============================================================================
/**
 * @file        TestLogger_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_I_H_
#define _CUTS_TEST_LOGGER_I_H_

#include "clientS.h"
#include "cuts/Log_T.h"
#include "ace/Task.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Refcountable_T.h"
#include "ace/OS_NS_netdb.h"

// Forward decl.
class CUTS_TestLoggerFactory_i;

/**
 * @class CUTS_TestLogger_i
 *
 * Default implemenation of the CUTS::TestLogger interface.
 */
class CUTS_TestLogger_i :
  public virtual POA_CUTS::TestLogger,
  public ACE_Task_Base
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]         logid             ID of the logger
   * @param[in]         parent            Parent factory object
   * @param[in]         msg_queue_size    Size of the message queue
   */
  CUTS_TestLogger_i (long logid,
                     CUTS_TestLoggerFactory_i & parent,
                     size_t msg_queue_size = 25);

  /// Destructor.
  virtual ~CUTS_TestLogger_i (void);

  virtual void log (const CUTS::TimeValue & tv,
                    CORBA::Long severity,
                    const CUTS::MessageText & message);

  virtual void batch_log (const CUTS::LogMessages & msgs);

  /**
   * Start the logger. It will flush the message queue at the defined
   * interval.
   *
   * @param[in]       timeout       Timeout value.
   */
  int start (const ACE_Time_Value & timeout);

  /// Stop the logger.
  int stop (void);

protected:
  /// Service handler routine for the task.
  virtual int svc (void);

  /// Handle the timeout event.
  virtual int handle_timeout (const ACE_Time_Value & current_time,
                              const void * act);

  /// Handle the input event.
  virtual int handle_input (ACE_HANDLE fd);

  virtual int handle_exception (ACE_HANDLE fd);

private:
  void copy_message (CUTS::LogMessage & dst, const CUTS::LogMessage & src);

  /// Send messages to the logging server.
  void send_messages (void);

  /// Id of the logger assigned by the parent.
  long logid_;

  /// Parent of the test logger.
  CUTS_TestLoggerFactory_i & parent_;

  /// Active state of the task.
  bool is_active_;

  /// Timeout value for the logger.
  ACE_Time_Value timeout_;

  /// Id of the timer for insert events into the database.
  long timer_id_;

  /// Mutex for swapping the message queues.
  ACE_RW_Thread_Mutex swap_mutex_;

  /// Type definition of the message log.
  typedef CUTS_Log_T <CUTS::LogMessage, ACE_RW_Thread_Mutex> msg_log_type;

  /// Maximum size of the message queue.
  size_t msg_queue_size_;

  /// Double buffer for the log messages.
  msg_log_type msg_logs_[2];

  /// Pointer to the active message log.
  msg_log_type * active_log_;

  /// Pointer to the inactive message log.
  msg_log_type * inactive_log_;

  /// Log message packet that is sent to the server.
  CUTS::LogMessagePacket packet_;
};

#if defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_I_H_
