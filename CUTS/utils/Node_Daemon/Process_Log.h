// -*- C++ -*-

//=============================================================================
/**
 * @file      Process_Log.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _PROCESS_LOG_H_
#define _PROCESS_LOG_H_

#include /**/ "ace/pre.h"

#include "Process_Info.h"
#include "ace/SString.h"
#include "ace/Thread_Mutex.h"
#include "ace/Containers_T.h"
#include "ace/iosfwd.h"

/// Type definition for a listing of processes.
typedef ACE_Array <CUTS_Process_Info> CUTS_Process_Info_Set;

//=============================================================================
/**
 * @class Process_Log
 *
 * Logging mechanism for process spawned by a process manager. The
 * Process_Log is responsible for serializing the state of process.
 * In the case of failure/recovery, the process manager can learn
 * about which processes it was managing.
 */
//=============================================================================

class Process_Log
{
public:
  /// Default constructor.
  Process_Log (void);

  /**
   * Initializing constructor.
   *
   * @param[in]     log       Name of the log.
   */
  Process_Log (const char * log);

  /// Destructor
  ~Process_Log (void);

  /**
   * Set the name of the log file.
   *
   * @param[in]     log       Name of the log.
   */
  void log_file (const char * log);

  /**
   * Get the name of the log file.
   *
   * @return      Name of the log file (including path).
   */
  const ACE_CString & log_file (void) const;

  bool process_spawn (const CUTS_Process_Info & info);

  bool process_exit (pid_t id);

  bool get_active_processes (CUTS_Process_Info_Set & list);

  bool clean (size_t * active_count = 0);

private:
  static size_t batch_read (std::istream & in,
                            CUTS_Process_Info_Set & buffer,
                            size_t bufsize);

  /// Name of the log file.
  ACE_CString log_file_;

  /// Locking mechanism for synchronized access.
  ACE_Thread_Mutex lock_;
};

#if defined (__CUTS_INLINE__)
#include "Process_Log.inl"
#endif

#include /**/ "ace/post.h"

#endif  // _PROCESS_LOG_H_
