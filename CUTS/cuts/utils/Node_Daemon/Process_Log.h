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
#include "ace/Unbounded_Set.h"
#include "ace/iosfwd.h"

/// Type definition for a listing of processes.
typedef ACE_Unbounded_Set <CUTS_Process_Info *> CUTS_Process_Info_Set;

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

  /**
   * Insert a new process into the log.
   *
   * @param[in]       info              The process's information.
   */
  bool process_insert (CUTS_Process_Info & info);

  /**
   * Set a processes entry to inactive. This does not remove the
   * entry from the log file.
   *
   * @param[in]       id                Target process id.
   */
  bool process_remove (pid_t id);

  /**
   * Get a listing of all the active processes.
   */
  bool get_active_processes (CUTS_Process_Info_Set & list);

  /**
   * Clean the log. This will remove all entries for processes
   * that have terminated (i.e., have an inactive state).
   *
   * @param[in]       active_count      Number of active processes.
   */
  bool clean (size_t * active_count = 0);

private:
  static size_t batch_read (std::istream & in,
                            CUTS_Process_Info_Set & buffer,
                            size_t bufsize);

  int read_string (std::ifstream & file,
                   ACE_CString & str);

  int write_string (std::ofstream & file,
                    const ACE_CString & str);

  int write_string (std::ofstream & file,
                    const char * str,
                    size_t length);

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
