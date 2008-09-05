// $Id$

//=============================================================================
/**
 * @file        cutsnode_d.cpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/Process_Mutex.h"
#include "Node_Daemon_Server.h"

#define NODE_DAEMON_SERVER \
  ACE_Singleton <CUTS_Node_Daemon_Server, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  NODE_DAEMON_SERVER->shutdown ();
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&server_sighandler);

  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    // Initialize the logging priorities.
    u_long default_mask =
      LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

    ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

    // We only allow one instance of the daemon to run at a time. This
    // way we don't have any confusion as to which one we are talking to.
    ACE_Process_Mutex process_lock ("cutsnode_d");
    ACE_Guard <ACE_Process_Mutex> guard (process_lock, 0);

    if (guard.locked () == 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T - %M - cutsnode_d is already active\n"),
                        1);
    }

    // Register the signal handler.
    register_sighandler ();

    // Run the node daemon
    return NODE_DAEMON_SERVER->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return 1;
}
