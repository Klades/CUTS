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

#include "Test_export.h"
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
  CUTS_TEST_TRACE ("register_sighandler (void)");

  ACE_Sig_Action sa (&server_sighandler);
  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// main
//
int ACE_TMAIN (int argc, ACE_TCHAR * argv [])
{
  CUTS_TEST_TRACE ("ACE_TMAIN (int, ACE_TCHAR * [])");

  int retval;

  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE;

  ACE_Log_Msg::instance ()->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  try
  {
    // Register the signal handler.
    register_sighandler ();

    // Run the main part of the application.
    retval = TESTING_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
    retval = 1;
  }

  return retval;
}
