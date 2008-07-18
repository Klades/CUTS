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

// Forward decl.
class CUTS_DB_Connection;

/**
 * @class CUTS_Test_Log_Message_Handler
 *
 * Self contained handler for a specific test. The test that the handler
 * manages is determined at construction time.
 */
class CUTS_Test_Log_Message_Handler :
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


private:
};

#if defined (__CUTS_INLINE__)
#include "Test_Log_Message_Handler.inl"
#endif

#endif  // !defined _CUTS_TEST_LOG_MESSAGE_HANDLER_H_
