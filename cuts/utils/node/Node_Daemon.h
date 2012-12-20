// -*- C++ -*-

//=============================================================================
/**
 * @file        Node_Daemon_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_DAEMON_APP_H_
#define _CUTS_NODE_DAEMON_APP_H_

#include "ace/Service_Gestalt.h"
#include "ace/Process_Mutex.h"

#if (ACE_MAJOR_VERSION >= 6 && ACE_MINOR_VERSION >= 1 && ACE_BETA_VERSION >= 4)
#include "ace/Condition_Thread_Mutex.h"
#else
#include "ace/Condition_T.h"
#endif


#include "Node_Daemon_Options.h"
#include "Virtual_Env_Manager.h"
#include "server/NodeDaemon_Server.h"

/**
 * @class CUTS_Node_Daemon
 */
class CUTS_Node_Daemon_App
{
public:
  /// Default constructor.
  CUTS_Node_Daemon_App (void);

  /// Destructor.
  ~CUTS_Node_Daemon_App (void);

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
  int load_initial_config (ACE_CString & active);

  /// Options for the server.
  CUTS_Node_Daemon_Options opts_;

  /// Mutex for \a is_shutdown_ condition variable.
  ACE_Thread_Mutex shutdown_;

  /// Condition variable that sync's node shutdown.
  ACE_Condition <ACE_Thread_Mutex> is_shutdown_;

  /// Collection of virtual environments for the node.
  CUTS_Virtual_Env_Manager virtual_envs_;

  /// The server object for the node daemon.
  CUTS_NodeDaemon_Server server_;

  /// The mutex for preventing multiple node daemons.
  ACE_Process_Mutex process_lock_;
};

#if defined (__CUTS_INLINE__)
#include "Node_Daemon.inl"
#endif

#endif  // !defined _CUTS_NODE_DAEMON_APP_H_
