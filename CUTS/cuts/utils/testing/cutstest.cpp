// $Id$

//=============================================================================
/**
 * @file        cuts_test.cpp
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#include "Testing_App.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#define TESTING_APP \
  ACE_Singleton <CUTS_Testing_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  TESTING_APP->shutdown ();
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

    // Run the main part of the application.
    retval = TESTING_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR, "*** error : caught unknown exception\n"));
    retval = 1;
  }

  return retval;
}
