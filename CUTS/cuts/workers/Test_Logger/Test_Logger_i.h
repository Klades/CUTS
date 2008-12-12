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

#include "cuts/utils/logging/client/clientC.h"
#include "cuts/utils/testing/svcs/server/testingC.h"

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
  bool log (const ACE_Time_Value & tv,
            long severity,
            const char * msg,
            size_t msg_length);

  /**
   * Configure the implementation. This will connect to the logging
   * client on the localhost running on \a port.
   *
   * @param[in]       port          Port number of the client.
   */
  bool configure (short port);

  /**
   * Connect to the test manager.
   *
   * @param[in]       name          Name of the test manager.
   */
  bool connect_using_location (const ACE_CString & location);

  /**
   * Connect to the test manager.
   *
   * @param[in]       name          Name of the test manager.
   */
  bool connect_using_name (const ACE_CString & name);

  /// Connect to the logging client using current configuration.
  bool connect (void);

private:

  int connect_i (const char * refstr);

  /// Name of the test manager.
  ACE_CString test_name_;

  /// ORB for the logging client.
  CORBA::ORB_var orb_;

  /// The logger client for the hosting machine.
  CUTS::LocalTestLoggerClient_var log_client_;

  /// Factory for creating/destroying the logger.
  CUTS::TestLoggerFactory_var log_factory_;

  /// The actual CUTS logger.
  CUTS::TestLogger_var logger_;

  /// The test manager for this logger.
  CUTS::TestManager_var test_manager_;

  /// UUID assigned to the test.
  CUTS::TestDetails details_;
};

#endif  // !defined _CUTS_TEST_LOGGER_I_H_
