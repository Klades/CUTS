// $Id$

#include "Logging_Client.h"
#include "Logger_Task.h"

#include "cuts/ORB_Server_Task.h"

#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/Reactor.h"
#include "ace/streams.h"

#include <sstream>

//
// __HELP__
//
static const char * __HELP__ =
"CUTS logging client responsible for sending log messages to a CUTS logging server\n"
"\n"
"USAGE: cuts-logging-client [OPTIONS]\n"
"\n"
"  -o, --iorfile=FILE                 write IOR to specified FILE\n"
"  --register-with-iortable=NAME      register client with IORTable under NAME\n"
"\n"
"Output options:\n"
"  -v, --verbose                      print verbose infomration\n"
"  --debug                            print debugging information\n"
"  --trace                            print tracing information\n"
"  -h, --help                         print this help message\n";

//
// CUTS_Logging_Client
//
CUTS_Logging_Client::CUTS_Logging_Client (void)
{

}

//
// CUTS_Logging_Client
//
CUTS_Logging_Client::~CUTS_Logging_Client (void)
{

}

//
// run_main
//
int CUTS_Logging_Client::run_main (int argc, char * argv [])
{
  try
  {
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")),
                         -1);

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - resolving RootPOA\n")));

    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ::PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
    mgr->activate ();

    // Create a new test logger client.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating logging client servant\n")));

    CUTS_LoggingClient_i * client = 0;

    ACE_NEW_THROW_EX (client,
                      CUTS_LoggingClient_i (root_poa.in (), &this->cleaning_task_),
                      ::CORBA::NO_MEMORY ());

    this->client_.reset (client);
    this->client_.activate (root_poa.in ());

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - initializing active objects\n")));

    CUTS_ORB_Server_Task task (this->orb_.in ());

    if (0 != this->cleaning_task_.init (this->orb_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize cleaning task\n")),
                         -1);

    // Activate the cleaning task.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating cleaning task\n")));

    if (0 != this->cleaning_task_.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate cleaning task\n")),
                         -1);

    // Activate the server task with N number of threads. We then wait for
    // all the threads to return. This happens when the ORB is shutdown.
    int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    int retval = task.activate (flags, this->opts_.thr_count_);

    if (0 == retval)
    {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - waiting for ORB to shutdown\n")));

      task.wait ();
    }

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destroying RootPOA\n")));

    root_poa->destroy (1, 1);

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// shutdown
//
void CUTS_Logging_Client::shutdown (void)
{
  try
  {
    // Deactivate the client.
    this->client_.deactivate ();

    // End the cleaning task for the client.
    this->cleaning_task_.reactor ()->end_reactor_event_loop ();
    this->cleaning_task_.wait ();

    // Stop the ORB's main event loop.
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown ();
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception in shutdown ()\n")));
  }
}

//
// destroy
//
void CUTS_Logging_Client::destroy (void)
{
  try
  {
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception in destroy ()\n")));
  }
}

//
// parse_args
//
int CUTS_Logging_Client::parse_args (int argc, char * argv [])
{
  // Initialize the ORB.
  this->orb_ = ::CORBA::ORB_init (argc, argv, "cuts.logging.client");

  // Parse the remaining command-line arguments.
  const char * opts = ACE_TEXT ("vho:");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("iorfile", 'o', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("register-with-iortable", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("trace", ACE_Get_Opt::NO_ARG);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp ("iorfile", get_opt.long_option ()) == 0)
      {
        this->client_.set_trait_value (CUTS_IOR_File_Trait (), get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp ("register-with-iortable", get_opt.long_option ()) == 0)
      {
        this->client_.set_trait_value (CUTS_IOR_Table_Trait (), get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("debug", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("trace", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_TRACE;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case 'o':
      this->client_.set_trait_value (CUTS_IOR_File_Trait (), get_opt.opt_arg ());
      break;

    case 'v':
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  return 0;
}

//
// print_help
//
void CUTS_Logging_Client::print_help (void)
{
  std::cout << ::__HELP__ << std::endl;
  ACE_OS::exit (1);
}
