// $Id$

#include "Barrier_Client.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#define CUTS_BARRIER_CLIENT \
  ACE_Singleton <CUTS_Barrier_Client, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_BARRIER_CLIENT->shutdown ();
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
    // Register the sighandler for the application.
    register_sighandler ();

    // Run the client.
    retval = CUTS_BARRIER_CLIENT->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));

    retval = 1;
  }

  // Destroy the client.
  CUTS_BARRIER_CLIENT->destroy ();

  return retval;
}
