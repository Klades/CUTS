// $Id$

#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "HelloWorld_svnt.h"
#include "HelloWorld_Basic_Impl.h"

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

    // Create the implemenation.
    ::TCPIP::HelloWorld_Exec_var impl;
    ACE_NEW_RETURN (impl, HelloWorld_Basic_Impl (), -1);

    // Create the servant, giving ownership of implementation.
    ::TCPIP::HelloWorld_Servant servant (impl._retn ());

    // Register the servant with the object manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - activating the object\n"));
    HELLOWORLD_SERVER->the_OM ().activate_object (&servant);

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - UUID:%s\n",
                servant.the_UUID ().to_string ()->c_str ()));

    // Run the ORB event loop.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - running the server's event loop\n"));

    int retval = HELLOWORLD_SERVER->run ();

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - server's event loop is done\n"));

    return retval;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return -1;
}
