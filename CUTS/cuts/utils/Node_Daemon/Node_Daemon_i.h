/* -*- C++ -*- */

//=============================================================================
/**
 * @file      CUTS_Node_Daemon_i.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_DAEMON_I_H_
#define _CUTS_NODE_DAEMON_I_H_

#include "Node_DaemonS.h"
#include "Node_Daemon_Event_Handler.h"
#include "cuts/utils/common/Property_Map.h"
#include "ace/Process_Manager.h"
#include "ace/Timer_Heap.h"
#include "ace/Timer_Queue_Adapters.h"

// Forward decl.
class CUTS_Process_Info;

/**
  * @class CUTS_Node_Daemon_i
  *
  * Main implementation of the Task_Manager interface.
  */
class CUTS_Node_Daemon_i :
  public virtual POA_CUTS::Task_Manager
{
public:
  /// Friend class.
  friend class Node_Daemon_Event_Handler;

  /// Default contructor.
  CUTS_Node_Daemon_i (CORBA::ORB_ptr orb);

  /// Destructor.
  virtual ~CUTS_Node_Daemon_i (void);

  /**
   * Spawn a set of node daemons.
   *
   * @param[in]     task      Task to spawn
   * @return        Number of nodes successfully spawned.
   */
  virtual CORBA::ULong task_spawn (const CUTS::taskDescriptor & task);

  /**
   * Kill a node in the task manager.
   *
   * @param[in]     name      Name of the task.
   */
  virtual CORBA::ULong task_terminate (const char * name,
                                       CORBA::Boolean wait);

  /**
   * Kill a node in the task manager.
   *
   * @param[in]     name      Name of the task.
   */
  virtual CORBA::ULong task_info (const char * name,
                                  CUTS::taskDescriptor_out info);

  /**
   * Restart an existing task.
   *
   * @param[in]     name      Name of the task.
   */
  virtual CORBA::ULong task_restart (const char * name);

  void initial_directory (const ACE_CString & dir);

  void insert_properties (const ACE_Array <ACE_CString> & props);

  void terminate_tasks (void);

private:
  /// Recover as many processes as possible.
  size_t recover (void);

  int task_spawn_i (CUTS_Process_Info & info);

  int task_terminate_i (CUTS_Process_Info & info, bool wait);

  void duplicate_defualt_process_options (ACE_Process_Options & opts);

  /// Initialize the class.
  void init (void);

  /// Unmanage the specified process.
  void unmanage (pid_t pid);

  /// Cleanup the process log.
  void clean (void);

  /// Type definition of mapping ports to processes.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Process_Info *,
                                ACE_RW_Thread_Mutex> Process_Map;

  /// Mapping of task names to their process ids.
  Process_Map process_map_;

  /// Process manager of the daemon used to spawn managers.
  ACE_Process_Manager pm_;

  /// Event handler for the node daemon.
  Node_Daemon_Event_Handler event_handler_;

  /// Common process options used by the daemon.
  ACE_Process_Options p_options_;

  /// The timer queue for the periodic task.
  ACE_Thread_Timer_Queue_Adapter <ACE_Timer_Heap> timer_queue_;

  /// Timeout value for the cleaning thread.
  long timer_;

  /// Locking mechanism for the mappings.
  ACE_RW_Thread_Mutex lock_;

  /// The ORB hosting the node daemon.
  ::CORBA::ORB_var orb_;

  /// The active state of the daemon.
  bool active_;

  /// Initial directory for spawned processes.
  ACE_CString init_dir_;

  /// Property map for the node daemon.
  CUTS_Property_Map prop_map_;
};

#if defined (__CUTS_INLINE__)
#include "Node_Daemon_i.inl"
#endif

#endif  /* !defined _CUTS_NODE_DAEMON_I_H_ */
