// $Id$

#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "HelloWorld_svnt.h"

#define HELLOWORLD_SERVER \
  ACE_Singleton <CUTS_TCPIP_ORB, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  HELLOWORLD_SERVER->shutdown ();
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
  try
  {
    // Initialize a new ORB for the server.
    HELLOWORLD_SERVER->init (argc, argv);

    // Register the servant with the object manager.
    CUTS_TCPIP::HelloWorld_svnt servant;
    HELLOWORLD_SERVER->the_OM ().activate_object (&servant);

    // Run the ORB event loop.
    return HELLOWORLD_SERVER->run ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return -1;
}
