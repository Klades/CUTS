// -*- C++ -*-

//=============================================================================
/**
 * @file      Virtual_Env.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_VIRTUAL_ENV_H_
#define _CUTS_VIRTUAL_ENV_H_

#include "ace/Array.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Process_Manager.h"
#include "ace/SString.h"
#include "ace/Event_Handler.h"
#include "cuts/utils/Property_Map.h"
#include "Delay_Handler.h"
#include "Node_Daemon_Common_export.h"
#include "Process_Options_List.h"

// Forward decl.
class CUTS_Process_Options;

/**
 * @class CUTS_Virtual_Env
 *
 * Container for executing processes within a common environment.
 */
class CUTS_NODE_DAEMON_COMMON_Export CUTS_Virtual_Env :
  public ACE_Event_Handler
{
public:
  /// Default constructor.
  CUTS_Virtual_Env (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Virtual_Env (void);

  /**
   * Get the name of the environent.
   *
   * @return        Name of the environment.
   */
  const ACE_CString & name (void) const;

  /// Close the environment.
  int close (void);

  /**
   * Spawn a new process into the environment.
   *
   * @param[in]       name        Unique name associated with process
   * @param[in]       opts        Options for the process.
   */
  int spawn (const CUTS_Process_Options & opts);

  int spawn (const CUTS_Process_Options_List & proc_list);

  /**
   * Terminate an existing process in the environment.
   *
   * @param[in]       name        Name of the process.
   */
  int terminate (const ACE_CString & name);

  /**
   * Start the environment. This will spawn all the process that have
   * be installed as "startup" processes.
   *
   * @return          Number of errors.
   */
  int start (void);

  /**
   * Shutdown the environment. This will terminate all active tasks and
   * spawn all the processes installed as "shutdown" processes.
   *
   * @return          Number of errors
   */
  int shutdown (void);

  /// Restart the environment.
  int restart (void);

  /**
   * Get the environment table for the virtual table.
   *
   * @return        Current environment table for virtual environment.
   */
  CUTS_Property_Map & env_table (void);

  /**
   * @overloaded
   */
  const CUTS_Property_Map & env_table (void) const;

  /**
   * Get the list of startup process options.
   */
  CUTS_Process_Options_List & startup_list (void);

  /**
   * @overloaded
   */
  const CUTS_Process_Options_List & startup_list (void) const;

  /**
   * Get the list of shutdown process options.
   */
  CUTS_Process_Options_List & shutdown_list (void);

  /**
   * @overloaded
   */
  const CUTS_Process_Options_List & shutdown_list (void) const;

private:
  /// Name of the environment.
  ACE_CString name_;

  /// Process manager for the environment.
  ACE_Process_Manager proc_man_;

  /// Set of variables for the environment.
  CUTS_Property_Map env_;

  /// Inherit settings/environment of host environment.
  bool inherit_;

  /// Mapping of process ids to the actual process options.
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          pid_t,
                          ACE_RW_Thread_Mutex> PROCESS_MANAGER;

  /// Listing of processes currently executing.
  PROCESS_MANAGER managed_;

  /// Processes to execute at startup.
  CUTS_Process_Options_List startup_;

  /// Processes to execute at shutdown.
  CUTS_Process_Options_List shutdown_;

  /// Delay handler for spawning process.
  CUTS_Delay_Handler delay_;
};

#if defined (__CUTS_INLINE__)
#include "Virtual_Env.inl"
#endif

#endif  // !defined _CUTS_VIRTUAL_ENV_H_
