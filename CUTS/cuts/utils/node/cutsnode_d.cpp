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

#define CUTS_NODE_DAEMON_APP \
  ACE_Singleton <CUTS_Node_Daemon_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_NODE_DAEMON_APP->shutdown ();
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
    // Initialize the logging priorities.
    u_long default_mask =
      LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

    ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

    // Register the signal handler.
    register_sighandler ();

    // Run the node daemon
    retval = 0 != CUTS_NODE_DAEMON_APP->run_main (argc, argv) ? 1 : 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
    retval = 1;
  }

  CUTS_NODE_DAEMON_APP->close ();
  return retval;
}
