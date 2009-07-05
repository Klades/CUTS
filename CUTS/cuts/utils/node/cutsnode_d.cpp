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

#include "ace/Null_Mutex.h"
#include "ace/Process_Mutex.h"
#include "ace/Signal.h"
#include "ace/Singleton.h"
#include "Node_Daemon.h"

#define CUTS_NODE_DAEMON \
  ACE_Singleton <CUTS_Node_Daemon, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_NODE_DAEMON->shutdown ();
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
  int retval;

  try
  {
    // We only allow one instance of the daemon to run at a time. This
    // way we don't have any confusion as to which one we are talking to.
    ACE_Process_Mutex process_lock ("cutsnode_d");
    ACE_Guard <ACE_Process_Mutex> guard (process_lock, 0);

    if (0 == guard.locked ())
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T (%t) - %M - cutsnode_d is already active\n"),
                        1);
    }

    // Initialize the logging priorities.
    u_long default_mask =
      LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

    ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

    // Register the signal handler.
    register_sighandler ();

    // Run the node daemon
    retval = CUTS_NODE_DAEMON->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
    retval = 1;
  }

  CUTS_NODE_DAEMON->close ();
  return retval;
}
