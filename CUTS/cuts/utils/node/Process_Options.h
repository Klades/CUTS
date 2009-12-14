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

#include "ace/SString.h"
#include "ace/Time_Value.h"
#include "ace/Unbounded_Set.h"
#include "Node_Daemon_Core_export.h"

/**
 * @class CUTS_Process_Options
 *
 * Detailed information about a process.
 */
class CUTS_NODE_DAEMON_CORE_Export CUTS_Process_Options
{
public:
  CUTS_Process_Options (void);

  /**
   * Copy constructor.
   *
   * @param[in]       copy        Source object
   */
  CUTS_Process_Options (const CUTS_Process_Options & copy);

  /// Default destructor.
  ~CUTS_Process_Options (void);

  /**
   * Assignment operator
   *
   * @param[in]       opts        Right-hand side of operator
   */
  const CUTS_Process_Options & operator = (const CUTS_Process_Options & opts);

  /// Name associated with the options.
  ACE_CString name_;

  /// Full path to the executable.
  ACE_CString exec_;

  /// Command-line arguments for the process.
  ACE_CString args_;

  /// Working directory for the process.
  ACE_CString cwd_;

  /// Delay value for process startup
  ACE_Time_Value delay_;

  /// Pipe location for the standard error.
  ACE_CString stderr_;

  /// Pipe location for the standard output.
  ACE_CString stdout_;

  /// Wait for the process to complete.
  bool wait_for_completion_;
};

#if defined (__CUTS_INLINE__)
#include "Process_Options.inl"
#endif

#endif  // !defined _CUTS_PROCESS_INFO_H_
