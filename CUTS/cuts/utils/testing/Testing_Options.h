// -*- C++ -*-

//=============================================================================
/**
 * @file        Testing_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_OPTIONS_H_
#define _CUTS_TESTING_OPTIONS_H_

#include "ace/SString.h"
#include "ace/UUID.h"

/**
 * @class CUTS_Testing_Options
 *
 * Container class for options of the testing application
 */
class CUTS_Testing_Options
{
public:
  /// Default constructor.
  CUTS_Testing_Options (void)
    : name_ ("(default)"),
      test_duration_ (static_cast <time_t> (30))
  {

  }

  /// Configuration file for the test.
  ACE_CString config_;

  /// Deployment command for the test.
  ACE_CString deploy_;

  /// Teardown command for the test.
  ACE_CString teardown_;

  /// Name of the testing application. The default name of the
  /// application is '(default)'.
  ACE_CString name_;

  /// The duration of the test.
  ACE_Time_Value test_duration_;

  /// Current working directory for deploy/teardown commands
  ACE_CString working_directory_;

  /// UUID for the testing application.
  ACE_Utils::UUID uuid_;
};

#endif  // !defined _CUTS_TESTING_OPTIONS_H_
