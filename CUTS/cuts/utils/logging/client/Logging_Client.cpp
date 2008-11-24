// $Id$

#include "Logging_Client.h"
#include "Logging_Client_Options.h"
#include "Logging_Client_Task.h"
#include "TestLoggerClient_i.h"
#include "tao/IORTable/IORTable.h"
#include "ace/ARGV.h"
#include "ace/Argv_Type_Converter.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include <sstream>

static const char * __HELP__ =
"Logging client daemon for submitting log messages to a CUTS database\n"
"\n"
"USAGE: cutslog_d [OPTIONS]\n"
"\n"
"Options:\n"
"  --port=VAL            localhost port number\n"
"  --thread-count=N      size of the server's thread pool for receiving\n"
"                        log messages from client applications (default N=1)\n"
"  --timeout=TIME        timeout interval to flush message queue\n"
"                        in seconds (default=30)\n"
"\n"
"  -h, --help            print this help message\n"
"  -v, --verbose         print verbose infomration\n"
"  --debug               print debugging information\n"
"  --trace               print tracing information\n"
"\n"
"Remarks:\n"
"If the client's threadpool size is set to 1, then the client will act\n"
"like a single-threaded logging client\n";

//
// CUTS_Logging_Client
//
CUTS_Logging_Client::CUTS_Logging_Client (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::CUTS_Logging_Client (void)");
}

//
// CUTS_Logging_Client
//
CUTS_Logging_Client::~CUTS_Logging_Client (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::~CUTS_Logging_Client (void)");
}

//
// run_main
//
int CUTS_Logging_Client::run_main (int argc, char * argv [])
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::run_main (int, char * [])");

  try
  {
    if (this->parse_args (argc, argv) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T (%t) - %M - failed to parse command-line arguments\n"),
                        -1);
    }

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    PortableServer::POA_var root_poa = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));
    PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
    mgr->activate ();

    // Create a new test logger client.
    CUTS_TestLoggerClient_i * client = 0;

    ACE_NEW_THROW_EX (client,
                      CUTS_TestLoggerClient_i (root_poa.in ()),
                      CORBA::NO_MEMORY ());

    this->client_.reset (client);

    // Activate the object under the RootPOA for now.
    PortableServer::ObjectId_var oid =
      root_poa->activate_object (this->client_.get ());

    // Register the test manager with the IORTable for the ORB.
    if (this->register_with_iortable () == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to register with IOR table; "
                         "aborting...\n"),
                         -1);
    }

    CUTS_Logging_Client_Task task (this->orb_.in ());

    // Activate the server task with N number of threads. We then wait for
    // all the threads to return. This happens when the ORB is shutdown.
    int flags = THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED;
    int retval = task.activate (flags, CUTS_LOGGING_OPTIONS->thr_count_);

    if (retval == 0)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - waiting for client task to return\n"));

      CUTS_Local_Logging_Client_App * local_client = 0;

      ACE_NEW_THROW_EX (local_client,
                        CUTS_Local_Logging_Client_App (*this->client_.get ()),
                        CORBA::NO_MEMORY ());

      this->local_client_.reset (local_client);

      // Activate the local client.
      if (this->local_client_->run_main (CUTS_LOGGING_OPTIONS->localport_) == 0)
      {
        // Wait for all the threads to exit.
        task.wait ();

        // Shutdown and destroy the local client.
        this->local_client_->shutdown ();
        this->local_client_->destroy ();
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to run local server\n"));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to activate server [retval = %d]\n",
                  retval));
    }

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the RootPOA\n"));
    root_poa->destroy (true, true);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the ORB\n"));

    this->orb_->destroy ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
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
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::shutdown (void)");

  try
  {
    // Stop the ORB's main event loop.
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown (1);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// parse_args
//
int CUTS_Logging_Client::parse_args (int argc, char * argv [])
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::parse_args (int, char * [])");

  // Initialize the ORB.
  this->orb_ = CORBA::ORB_init (argc, argv, "cuts.logging.client");

  // Parse the remaining command-line arguments.
  const char * opts = ACE_TEXT ("vh");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("port", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("thread-count", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("timeout", ACE_Get_Opt::ARG_REQUIRED);

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
      if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
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
      else if (ACE_OS::strcmp ("timeout", get_opt.long_option ()) == 0)
      {
        std::istringstream istr (get_opt.opt_arg ());

        time_t seconds;
        istr >> seconds;

        CUTS_LOGGING_OPTIONS->timeout_.sec (seconds);
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp ("thread-count", get_opt.long_option ()) == 0)
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> CUTS_LOGGING_OPTIONS->thr_count_;
      }
      else if (ACE_OS::strcmp ("port", get_opt.long_option ()) == 0)
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> CUTS_LOGGING_OPTIONS->localport_;
      }

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

  // Validate all the command-line options.
  if (CUTS_LOGGING_OPTIONS->thr_count_ == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - --thread-count must be greater than 0\n"),
                       -1);

  return 0;
}

//
// register_with_iortable
//
int CUTS_Logging_Client::register_with_iortable (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::register_with_iortable (void)");

  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to resolve IOR table\n"),
                         -1);
    }

    // Get the IOR string for the test manager.
    CUTS::TestLoggerClient_var client = this->client_->_this ();
    CORBA::String_var obj_str  = this->orb_->object_to_string (client.in ());
    CORBA::String_var ior_name = CORBA::string_dup ("CUTS/TestLoggerClient");

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering test logger client with localhost\n"));

    ior_table->bind (ior_name.in (), obj_str.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// print_help
//
void CUTS_Logging_Client::print_help (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_Logging_Client::print_help (void)");

  std::cout << ::__HELP__ << std::endl;
  ACE_OS::exit (0);
}
