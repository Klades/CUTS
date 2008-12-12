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
    : name_ ("(default)")
  {

  }

  /// Configuration file for the test.
  ACE_CString config_;

  /// Deployment command for the test.
  ACE_CString deploy_;

  /// Teardown command for the test.
  ACE_CString teardown_;

  /// Name of the testing application.
  ACE_CString name_;

  /// The duration of the test.
  ACE_Time_Value test_duration_;

  /// Current working directory for deploy/teardown commands
  ACE_CString working_directory_;

  /// UUID for the testing application.
  ACE_Utils::UUID uuid_;

  /// Start time of the test
  ACE_Time_Value start_;

  /// Stop time of the test.
  ACE_Time_Value stop_;
};

#endif  // !defined _CUTS_TEST_OPTIONS_H_
