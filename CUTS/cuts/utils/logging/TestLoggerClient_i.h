// -*- C++ -*-

//=============================================================================
/**
 * @file          TestLoggerClient_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_CLIENT_I_H_
#define _CUTS_TEST_LOGGER_CLIENT_I_H_

#include "loggingS.h"
#include "cuts/utils/ODBC/ODBC_Connection.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/RW_Thread_Mutex.h"

// Forward decl.
class CUTS_Test_Log_Message_Handler;

/**
 * @class CUTS_TestLoggerClient_i
 *
 * Implementation of the CUTS::TestLoggerClient interface.
 */
class CUTS_TestLoggerClient_i :
  public POA_CUTS::TestLoggerClient
{
public:
  /// Default constructor.
  CUTS_TestLoggerClient_i (void);

  /// Destructor.
  virtual ~CUTS_TestLoggerClient_i (void);

  /**
   * Log the specified message. The client will cache the message until
   * it is ready to send it to the logger server.
   */
  virtual void log (const CUTS::LogMessage & message);

  /**
   * Register the test with the logger.
   *
   * @param[in]       test          The test number
   */
  virtual void register_test (CORBA::Long new_test, CORBA::Long old_test);

  /**
   * Unregister the test with the logger.
   *
   * @param[in]       test          The test number
   */
  virtual void unregister_test (CORBA::Long test);

  /**
   * Set the address of the database server.
   */
  void database_server_address (const ACE_CString & addr);

  /**
   * Set the timeout interval for flushing the message queue.
   */
  void timeout_interval (const ACE_Time_Value & tv);

private:
  void unregister_test_i (long test);

  /// Type definition of the handler map for the tests.
  typedef 
    ACE_Hash_Map_Manager <long,
                          CUTS_Test_Log_Message_Handler *,
                          ACE_RW_Thread_Mutex> map_type;

  /// Mapping the handler by the test number.
  map_type handler_map_;

  /// The database connection for the client.
  ODBC_Connection conn_;

  /// The hostname of the logging client.
  ACE_Auto_String_Free hostname_;

  /// Server address of the database.
  ACE_CString server_addr_;

  /// Timeout interval for flushing the message queue.
  ACE_Time_Value timeout_;
};

#endif  // !defined _CUTS_TEST_LOGGER_CLIENT_I_H_
