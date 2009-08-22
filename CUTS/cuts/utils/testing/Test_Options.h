// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_OPTIONS_H_
#define _CUTS_TEST_OPTIONS_H_

#include "Test_export.h"
#include "ace/Process.h"
#include "ace/SString.h"
#include "ace/Time_Value.h"
#include "ace/UUID.h"

/**
 * @class CUTS_Test_Options
 *
 * Container class for options of the testing application
 */
class CUTS_TEST_Export CUTS_Test_Options
{
public:
  /// Default constructor.
  CUTS_Test_Options (void)
    : name_ ("(default)"),
      ignore_errors_ (false),
      shutdown_timeout_ (ACE_Time_Value::max_time),
      daemonize_ (false)
  {

  }

  /// Configuration file for the test.
  ACE_CString config_;

  /// Deployment command for the test.
  ACE_Auto_Ptr <ACE_Process_Options> startup_;

  /// Teardown command for the test.
  ACE_Auto_Ptr <ACE_Process_Options> shutdown_;

  /// Name of the testing application.
  ACE_CString name_;

  /// The duration of the test.
  ACE_Time_Value test_duration_;

  /// Timeout value for the shutdown process.
  ACE_Time_Value shutdown_timeout_;

  /// Current working directory for deploy/teardown commands
  ACE_CString working_directory_;

  /// UUID for the testing application.
  ACE_Utils::UUID uuid_;

  /// Start time of the test
  ACE_Time_Value start_;

  /// Stop time of the test.
  ACE_Time_Value stop_;

  bool ignore_errors_;

  /// Name of the test file.
  ACE_CString filename_;

  /// The application is a daemon.
  bool daemonize_;
};

#endif  // !defined _CUTS_TEST_OPTIONS_H_
