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

#include "Testing_Base_export.h"
#include "ace/SString.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_Testing_Options
 */
class CUTS_TESTING_BASE_Export CUTS_Testing_Options
{
public:
  /// Default constructor.
  CUTS_Testing_Options (void)
    : name_ ("(default)"),
      test_duration_ (static_cast <time_t> (30))
  {

  }

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
};

CUTS_TESTING_BASE_SINGLETON_DECLARE(ACE_Singleton,
                                    CUTS_Testing_Options,
                                    ACE_Null_Mutex);

#define CUTS_TESTING_OPTIONS \
  ACE_Singleton <CUTS_Testing_Options, ACE_Null_Mutex>::instance ()

#endif  // !defined _CUTS_TESTING_OPTIONS_H_
