// -*- C++ -*-

//=============================================================================
/**
 * @file        Process_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROCESS_OPTIONS_H_
#define _CUTS_PROCESS_OPTIONS_H_

#include "cuts/config.h"
#include "ace/SString.h"
#include "ace/Time_Value.h"
#include "ace/Unbounded_Set.h"

/**
 * @class CUTS_Process_Options
 *
 * Detailed information about a process.
 */
class CUTS_Process_Options
{
public:
  CUTS_Process_Options (void);

  /// Full path to the executable.
  ACE_CString executable_;

  /// Command-line arguments for the process.
  ACE_CString arguments_;

  /// Working directory for the process.
  ACE_CString working_directory_;

  /// Delay value for process startup
  ACE_Time_Value delay_;

  /// Pipe location for the standard error.
  ACE_CString stderr_;

  /// Pipe location for the standard output.
  ACE_CString stdout_;

  /// Wait for the process to complete.
  bool wait_for_completion_;

  /// Set of process that must execute before this process.
  ACE_Unbounded_Set <ACE_CString> after_;
};

#if defined (__CUTS_INLINE__)
#include "Process_Options.inl"
#endif

#endif  // !defined _CUTS_PROCESS_INFO_H_
