// $Id$

#include "ace/Singleton.h"
#include "ace/Signal.h"
#include "ace/Null_Mutex.h"
#include "TCPIP_CCM_ComponentServer_App.h"

#define CUTS_TCPIP_COMPONENT_SERVER_APP \
  ACE_Singleton <CUTS_TCPIP_CCM_ComponentServer_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  CUTS_TCPIP_COMPONENT_SERVER_APP->shutdown ();
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
int ACE_TMAIN (int argc, char * argv [])
{
  int retval;

  try
  {
    try
    {
      // Register the signal handler for Ctrl+C
      register_sighandler ();

      // Run the component server's app.
      retval = CUTS_TCPIP_COMPONENT_SERVER_APP->run_main (argc, argv);
    }
    catch (const CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T - %M - %s\n"),
                  ex._info ().c_str ()));

      retval = 1;
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));

      retval = 1;
    }

    // Destroy the component server.
    CUTS_TCPIP_COMPONENT_SERVER_APP->destroy ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return retval;
}
