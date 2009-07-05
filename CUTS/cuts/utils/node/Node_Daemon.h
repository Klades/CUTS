// -*- C++ -*-

//=============================================================================
/**
 * @file        Node_Daemon_Server.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_DAEMON_H_
#define _CUTS_NODE_DAEMON_H_

#include "ace/Condition_T.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/Thread_Mutex.h"
#include "cuts/config.h"
#include "Node_Daemon_Options.h"

// Forward decl.
class CUTS_Virtual_Env;

/**
 * @class CUTS_Node_Daemon
 */
class CUTS_Node_Daemon
{
public:
  /// Type definition for collection of virtual environments.
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          CUTS_Virtual_Env *,
                          ACE_RW_Thread_Mutex> VIRTUAL_ENV_TABLE;

  /// Default constructor.
  CUTS_Node_Daemon (void);

  /// Destructor.
  ~CUTS_Node_Daemon (void);

  /**
   * Run the server main event loop.
   *
   * @param[in]         argc          Number of arguments
   * @param[in]         argv          Command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the server.
  void shutdown (void);

  /// Close the node daemon
  void close (void);

private:
  /// Helper method to parse command-line options.
  int parse_args (int argc, char * argv []);

  /// Helper method to load the initial configuration.
  int load_initial_config (CUTS_Virtual_Env * & active);

  /// Options for the server.
  CUTS_Node_Daemon_Options opts_;

  /// Mutex for \a is_shutdown_ condition variable.
  ACE_Thread_Mutex shutdown_;

  /// Condition variable that sync's node shutdown.
  ACE_Condition <ACE_Thread_Mutex> is_shutdown_;

  /// Collection of virtual environments for the node.
  VIRTUAL_ENV_TABLE virtual_envs_;
};

#if defined (__CUTS_INLINE__)
#include "Node_Daemon.inl"
#endif

#endif  // !defined _CUTS_NODE_DAEMON_SERVER_H_
