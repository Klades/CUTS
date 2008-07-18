// -*- C++ -*-

#ifndef _CUTS_TEST_LOGGER_I_H_
#define _CUTS_TEST_LOGGER_I_H_

#include "cuts/config.h"
#include "loggingS.h"
#include "ace/Task_Ex_T.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Refcountable_T.h"

// Forward decl.
class CUTS_TestLoggerFactory_i;

/**
 * @struct CUTS_Log_Message
 *
 * Data structure used by the CUTS_Test_Log_Message_Handler to buffer log
 * messages before sending them to the server. This data structure has been
 * designed to work with the ACE_Locked_Free_List to amortize memory
 * allocations for a test.
 */
class CUTS_Log_Message
{
public:
  /// Default constructor.
  CUTS_Log_Message (void);

  /// Timestamp of the log message.
  long timestamp_;

  /// Severity of the log message.
  long severity_;

  /// The textual content of the log message.
  ACE_Array <char> text_;

  // @{ @name ACE_Free_List methods

  /**
   * Set the next element on the free list.
   */
  void set_next (CUTS_Log_Message * next);

  /**
   * Get the next element on the free list.
   */
  CUTS_Log_Message * get_next (void);

private:
  /// Next element in the free list.
  CUTS_Log_Message * next_;
  // @}
};

/**
 * @class CUTS_TestLogger_i
 *
 * Default implemenation of the CUTS::TestLogger interace.
 */
class CUTS_TestLogger_i :
  public POA_CUTS::TestLogger,
  public ACE_Task_Ex <ACE_MT_SYNCH, CUTS_Log_Message>
{
public:
  CUTS_TestLogger_i (CUTS_TestLoggerFactory_i & parent);

  virtual ~CUTS_TestLogger_i (void);

  virtual void log (CORBA::LongLong timestamp,
                    CORBA::Long severity,
                    const CUTS::MessageText & message);

  virtual void batch_log (const CUTS::LogMessages & msgs);

  /// Destroy the logger.
  virtual void destroy (void);

  int start (const ACE_Time_Value & timeout);

  int stop (void);

protected:
  /// Service handler routine for the task.
  virtual int svc (void);

  /// Handle the timeout event.
  virtual int handle_timeout (const ACE_Time_Value & current_time,
                              const void * act);

  /// Handle the input event.
  virtual int handle_input (ACE_HANDLE fd);

  /// Handle the exception event.
  virtual int handle_exception (ACE_HANDLE fd);

private:
  /// Parent of the test logger.
  CUTS_TestLoggerFactory_i & parent_;

  /**
   * Helper method to handle a new log message.
   *
   * @param[in]     message       New log message.
   */
  int handle_message (CUTS_Log_Message * message);

  /**
   * Insert the messages into the database. This will take the current
   * size of the queue, and dump that many messages into the database.
   * Any messages that come along while the messages are being dumped
   * into the database will be processed next time.
   */
  int insert_messages_into_database (void);

  /// Test number assigned to the message handler.
  long test_number_;

  /// The name of the host running this handler.
  const char * hostname_;

  /// Active state of the task.
  bool is_active_;

  /// Id of the timer for insert events into the database.
  long timer_id_;

  /// Low water mark for the message queue.
  size_t lwm_msg_queue_;

  /// High water mark for the message queue.
  size_t hwm_msg_queue_;

  /// Free list of log messages owned by handler.
  ACE_Locked_Free_List <CUTS_Log_Message, ACE_RW_Thread_Mutex> msg_free_list_;
};

#if defined (__CUTS_INLINE__)
#include "TestLogger_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_I_H_
