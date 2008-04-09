// -*- C++ -*-

//=============================================================================
/**
 * @file        Process_Info.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROCESS_INFO_H_
#define _CUTS_PROCESS_INFO_H_

#include "cuts/config.h"
#include "ace/SString.h"
#include "ace/OS.h"

//=============================================================================
/**
 * @class CUTS_Process_Info
 *
 * Detailed information about a process.
 */
//=============================================================================

class CUTS_Process_Info
{
public:
  /// Process id for the entry.
  pid_t pid_;

  /// The active state of the entry.
  char state_;

  /// The name of the process.
  ACE_CString name_;

  /// The executable name of the process.
  ACE_CString exec_;

  /// The arguments of the process.
  ACE_CString args_;

  /**
   * Test the log entry for equality. Two log entries are equal
   * if both have the same name. We do not care about the process's
   * id.
   *
   * @param[in]       rhs       Right hand side of the operator.
   * @retval          true      The log entries are equal.
   * @retval          false     The log entries are not equal.
   */
  bool operator == (const CUTS_Process_Info & rhs);
};

#if defined (__CUTS_INLINE__)
#include "Process_Info.inl"
#endif

#endif  // !defined _CUTS_PROCESS_INFO_H_
