// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Log_Message_Handler.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOG_MESSAGE_HANDLER_H_
#define _CUTS_TEST_LOG_MESSAGE_HANDLER_H_

#include "cuts/config.h"
#include "ace/Task_Ex_T.h"
#include "ace/Refcountable_T.h"
#include "ace/Free_List.h"

/**
 * @struct CUTS_Log_Message
 *
 * Data structure used by the CUTS_Test_Log_Message_Handler to buffer
 * log messages before sending them to the server. This data structure
 * has been designed to work with the ACE_Locked_Free_List to amortize
 * memory allocations for a test.
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

// Forward decl.
class CUTS_DB_Connection;

/**
 * @class CUTS_Test_Log_Message_Handler
 *
 * Self contained handler for a specific test. The test that the handler 
 * manages is determined at construction time. 
 */
class CUTS_Test_Log_Message_Handler :
  protected ACE_Task_Ex <ACE_MT_SYNCH, CUTS_Log_Message>,
  public ACE_Refcountable_T <ACE_RW_Thread_Mutex>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]           conn            Existing database connection
   * @param[in]           test_number     Test number handler manages
   */
  CUTS_Test_Log_Message_Handler (CUTS_DB_Connection & conn,
                                 long test_number,
                                 const char * hostname,
                                 size_t lwm_msg_queue = 25,
                                 size_t hwm_msg_queue = 50);

  /// Destructor.
  virtual ~CUTS_Test_Log_Message_Handler (void);

  /**
   * Start the log message handler. The start () method takes a \a timeout
   * value that specifies how often the handler should insert queued 
   * messages into the database if the queue does not reach a certain size.
   *
   * @param[in]           timeout         Desired timeout value
   */
  int start (const ACE_Time_Value & timeout);

  /// Stop the log message handler.
  int stop (void);

  /**
   * Handle a new log message. This will insert the message onto the 
   * queue. 
   */
  int handle_message (CUTS_Log_Message * msg);

  /**
   * Create a new log message.
   */
  CUTS_Log_Message * new_message (void);

private:
  /// Service handler routine for the task.
  virtual int svc (void);

  /// Handle the timeout event.
  virtual int handle_timeout (const ACE_Time_Value & current_time,  
                              const void * act);

  /// Handle the input event.
  virtual int handle_input (ACE_HANDLE fd);

  /// Handle the exception event.
  virtual int handle_exception (ACE_HANDLE fd);

  /**
   * Insert the messages into the database. This will take the current 
   * size of the queue, and dump that many messages into the database.
   * Any messages that come along while the messages are being dumped
   * into the database will be processed next time.
   */
  int insert_messages_into_database (void);

  /// The database connection for the handler.
  CUTS_DB_Connection & conn_;

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
#include "Test_Log_Message_Handler.inl"
#endif

#endif  // !defined _CUTS_TEST_LOG_MESSAGE_HANDLER_H_
