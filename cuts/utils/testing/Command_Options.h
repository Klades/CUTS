// -*- C++ -*-

//=============================================================================
/**
 * @file        Command_Options.h
 *
 * $Id$
 *
 * @author      Manjula Peiris
 */
//=============================================================================

#ifndef _CUTS_COMMAND_OPTIONS_H_
#define _CUTS_Command_OPTIONS_H_

#include "ace/SString.h"
#include "ace/Time_Value.h"
#include "ace/Unbounded_Set.h"
#include "Test_export.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"

/**
 * @class CUTS_Command_Options
 *
 * Detailed information about a Command.
 */
class CUTS_TEST_Export CUTS_Command_Options
{
public:
  CUTS_Command_Options (void);

  /**
   * Copy constructor.
   *
   * @param[in]       copy        Source object
   */
  CUTS_Command_Options (const CUTS_Command_Options & copy);

  /// Default destructor.
  ~CUTS_Command_Options (void);

  /**
   * Assignment operator
   *
   * @param[in]       opts        Right-hand side of operator
   */
  const CUTS_Command_Options & operator = (const CUTS_Command_Options & opts);

  /// Name associated with the options.
  ACE_CString name_;

  /// Full path to the executable.
  ACE_CString exec_;

  /// Command-line arguments for the Command.
  ACE_CString args_;

  /// Working directory for the Command.
  ACE_CString cwd_;

  /// Delay value for Command startup
  ACE_Time_Value delay_;

  /// Pipe location for the standard error.
  ACE_CString stderr_;

  /// Pipe location for the standard output.
  ACE_CString stdout_;

  /// Wait for the Command to complete.
  bool wait_for_completion_;

  /// Options for the spawning process as a result of
  /// the command
  ACE_Process_Options options_;
};

#if defined (__CUTS_INLINE__)
#include "Command_Options.inl"
#endif

#endif  // !defined _CUTS_COMMAND_OPTIONS_H_
