// $Id$

#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_ComponentServer.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "HelloWorld_svnt.h"
#include "HelloWorld_Basic_Impl.h"

#define TCPIP_COMPONENT_SERVER \
  ACE_Singleton <CUTS_TCPIP_CCM_ComponentServer, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  TCPIP_COMPONENT_SERVER->shutdown ();
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
    // Register the signal handler for Ctrl+C
    register_sighandler ();

    // Initialize the component server.
    TCPIP_COMPONENT_SERVER->init (argc, argv);

    // Create the implemenation.
    ::TCPIP::HelloWorld_Exec_var impl;
    ACE_NEW_RETURN (impl, HelloWorld_Basic_Impl (), -1);

    // Create the servant, giving ownership of implementation.
    ::TCPIP::HelloWorld_Servant servant (impl._retn ());

    // Register the servant with the object manager.
    ACE_DEBUG ((LM_DEBUG, "%T - %M - installing the component\n"));
    TCPIP_COMPONENT_SERVER->install_component ("HelloWorld", &servant);

    // Get the EventConsumerBase object for <handle_message>
    Components::EventConsumerBase_var consumer = servant.get_consumer ("handle_message");

    // Subscribe the returned consumer.
    servant.connect_consumer ("handle_message", consumer.in ());

    servant.configuration_complete ();

    // Let's force the activation of the component.
    servant.ccm_activate ();

    TCPIP_COMPONENT_SERVER->activate ();

    servant.ccm_passivate ();

    servant.ccm_remove ();

    TCPIP_COMPONENT_SERVER->destroy ();

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return -1;
}
