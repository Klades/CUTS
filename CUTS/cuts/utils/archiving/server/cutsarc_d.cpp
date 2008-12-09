// $Id$

#include "Test_Archive_Server.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#define CUTS_TEST_ARCHIVE_SERVER \
  ACE_Singleton <CUTS_Test_Archive_Server, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_TEST_ARCHIVE_SERVER->shutdown ();
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
    // Register the signal handler.
    register_sighandler ();

    // Run the server.
    retval = CUTS_TEST_ARCHIVE_SERVER->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));

    retval = 1;
  }

  // Destroy the server's resources.
  CUTS_TEST_ARCHIVE_SERVER->destroy ();

  return retval;
}
