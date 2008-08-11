// -*- C++ -*-

//=============================================================================
/**
 * @file          Test_Logger_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_I_H_
#define _CUTS_TEST_LOGGER_I_H_

#include "cuts/utils/logging/loggingC.h"
#include "cuts/utils/testing/testingC.h"

/**
 * @class CUTS_Test_Logger_i
 *
 * Implementation of the CUTS test logger. This is designed to prevent
 * class that use the CUTS_Test_Logger class from needed to import
 * the CORBA related libraries.
 */
class CUTS_Test_Logger_i
{
public:
  /// Default constructor.
  CUTS_Test_Logger_i (void);

  /// Destructor.
  ~CUTS_Test_Logger_i (void);

  /**
   * Log the specified message.
   *
   * @param[in]       tv            Time value of the message
   * @param[in]       severity      Message severity
   * @param[in]       msg           Pointer to the message
   * @param[in]       msg_length    Length of the message.
   */
  void log (const ACE_Time_Value & tv,
            long severity,
            const char * msg,
            size_t msg_length);

  /**
   * Configure the implementation. This will connect to the logging
   * client on the localhost running on \a port.
   *
   * @param[in]       port          Port number of the client.
   */
  void configure (short port);

  /**
   * Connect to the test manager.
   *
   * @param[in]       name          Name of the test manager.
   */
  void connect (const ACE_CString & name);

  /// Reconnect to the test manager. This will also update the test
  /// number for the logger.
  void connect (void);

private:
  bool connect_i (const ACE_CString & name);

  /// Name of the test manager.
  ACE_CString test_name_;

  /// The test number for the logger.
  long test_number_;

  /// ORB for the logging client.
  CORBA::ORB_var orb_;

  /// The logger client for the hosting machine.
  CUTS::TestLoggerClient_var log_client_;

  /// Factory for creating/destroying the logger.
  CUTS::TestLoggerFactory_var log_factory_;

  /// The actual CUTS logger.
  CUTS::TestLogger_var logger_;

  /// The test manager for this logger.
  CUTS::TestManager_var test_manager_;
};

#endif  // !defined _CUTS_TEST_LOGGER_I_H_
