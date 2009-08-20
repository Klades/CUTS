// $Id$

#include "Testing_App.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_App.inl"
#endif

#include "Test_Configuration_File.h"
#include "Testing_Service_Manager.h"
#include "cuts/utils/Property_Parser.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"
#include "ace/Reactor.h"
#include "ace/streams.h"
#include "ace/UUID.h"
#include "boost/bind.hpp"
#include "XSC/utils/XML_Error_Handler.h"
#include <sstream>
#include <algorithm>

static const char * __USAGE__ =
"Test manager for CUTS-based experiments\n"
"\n"
"USAGE: cutstest [OPTIONS]\n";

static const char * __HELP__ =
"General options:\n"
"  -n, --name=NAME           name for test manager (default='(default)')\n"
"  -c, --config=FILE         configuration file for test\n"
"  --time=TIME               test duration in seconds (default=60)\n"
"  --uuid=UUID               user-defined UUID for the test\n"
"  -f, --file=ARCHIVE        store results in ARCHIVE\n"
"\n"
"  -DNAME=VALUE              set property NAME=VALUE\n"
"\n"
"Execution options:\n"
"  -C, --directory=DIR       change to directory DIR\n"
"  --startup=CMD             use CMD to startup test\n"
"  --shutdown=CMD            use CMD to shutdown test\n"
"  --shutdown-timeout=N      timeout shutdown after N seconds\n"
"  --ignore-errors           ignore errors at startup/shutdown\n"
"\n"
"Output options:\n"
"  -v, --verbose             print verbose information\n"
"  --debug                   print debug information\n"
"  --trace                   print trace information (requires compile support)\n"
"  -h, --help                print this help message\n";

//
// CUTS_Testing_App
//
CUTS_Testing_App::CUTS_Testing_App (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::CUTS_Testing_App (void)");

  ACE_Utils::UUID_GENERATOR::instance ()->init ();
}

//
// CUTS_Testing_App
//
CUTS_Testing_App::~CUTS_Testing_App (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::~CUTS_Testing_App (void)");
}


//
// parse_args
//
int CUTS_Testing_App::parse_args (int argc, char * argv [])
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::parse_args (int argc, char * argv [])");

  // Now, parse the remaining command-line options.
  const char * opts = ACE_TEXT ("n:vht:c:D:f:");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("time", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("uuid", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("file", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("directory", 'C', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("startup", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("shutdown", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("shutdown-timeout", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("ignore-errors", ACE_Get_Opt::NO_ARG);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("trace", ACE_Get_Opt::NO_ARG);

  char ch;
  CUTS_Property_Parser property_parser (this->props_);

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
      {
        this->opts_.config_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
      {
        this->opts_.name_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "debug") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);
        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);
        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "time") == 0)
      {
        time_t seconds;
        std::istringstream istr (get_opt.opt_arg ());
        istr >> seconds;

        this->opts_.test_duration_.sec (seconds);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "trace") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);
        mask |= LM_TRACE;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "startup") == 0)
      {
        // Allocate a process option for the startup command.
        ACE_Process_Options * options = 0;

        ACE_NEW_THROW_EX (options,
                          ACE_Process_Options (),
                          ACE_bad_alloc ());

        this->opts_.startup_.reset (options);

        // Save the command-line for the startup command.
        options->command_line (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "shutdown") == 0)
      {
        // Allocate a process option for the shutdown command.
        ACE_Process_Options * options = 0;

        ACE_NEW_THROW_EX (options,
                          ACE_Process_Options (),
                          ACE_bad_alloc ());

        this->opts_.shutdown_.reset (options);

        // Save the command-line for the shutdown command.
        options->command_line (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "ignore-errors") == 0)
      {
        this->opts_.ignore_errors_ = true;
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "shutdown-timeout") == 0)
      {
        time_t seconds;
        std::istringstream istr (get_opt.opt_arg ());
        istr >> seconds;

        this->opts_.shutdown_timeout_.sec (seconds);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "directory") == 0)
      {
        this->opts_.working_directory_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "uuid") == 0)
      {
        this->opts_.uuid_.from_string (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "file") == 0)
      {
        this->opts_.filename_  = get_opt.opt_arg ();
      }
      break;

    case 'n':
      this->opts_.name_ = get_opt.opt_arg ();
      break;

    case 'f':
      this->opts_.filename_ = get_opt.opt_arg ();
      break;

    case 'c':
      this->opts_.config_ = get_opt.opt_arg ();
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

    case 'D':
      if (!property_parser.parse (get_opt.opt_arg ()))
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to parse property %s\n",
                    get_opt.opt_arg ()));
      }

      break;

    case 'C':
      this->opts_.working_directory_ = get_opt.opt_arg ();
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - -%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;
    };
  }

  // Generate a new UUID for the deployment, if necessary.
  if (this->opts_.uuid_ == ACE_Utils::UUID::NIL_UUID)
    ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (this->opts_.uuid_);

  // Make sure we have the filename set.
  if (this->opts_.filename_.empty ())
    this->opts_.filename_ = *this->opts_.uuid_.to_string () + ".cdb";

  return 0;
}

//
// run_main
//
int CUTS_Testing_App::run_main (int argc, char * argv [])
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::run_main (int, char * [])");

  // Parse the command-line arguments.
  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Service manager for the application.
  CUTS_Testing_Service_Manager svc_mgr (this);

  try
  {
    // Open the test database for writing.
    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - writing test data to %s\n",
                this->opts_.filename_.c_str ()));

    this->test_db_.create (this->opts_.filename_, this->opts_.uuid_);

    // Load the configuration this test run.
    if (this->load_configuration (svc_mgr, this->opts_.config_) != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to load test configuration\n"));
    }

    if (this->opts_.startup_.get ())
    {
      // Deploy the test into the environment.
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - running startup process for test\n"));

      int retval = this->deploy_test (*this->opts_.startup_.get ());

      if (retval == 0 || this->opts_.ignore_errors_)
      {
        // Start a new test run in the database.
        this->test_db_.start_new_test (this->opts_.start_);

        // Notify loaded services of test startup.
        svc_mgr.handle_startup (this->opts_.start_);
      }
      else
      {
        if (retval == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - aborting test since deployment failed\n"));
        }
        else if (retval == 1)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - state of deployment unknown; aborting...\n"));
        }

        return -1;
      }
    }

    if (this->opts_.test_duration_ != ACE_Time_Value::zero)
    {
      // Execute a timed version of the test.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - running the test\n"));

      if (this->task_.run_test (this->opts_.test_duration_) != 0)
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to run test\n"));
      }
    }

    if (this->opts_.shutdown_.get ())
    {
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - running shutdown process for test\n"));

      // Execute the shutdown command for the test.
      int retval = this->teardown_test (*this->opts_.shutdown_.get ());

      if (retval == 0 || this->opts_.ignore_errors_)
      {
        // Stop the current test in the database.
        this->test_db_.stop_current_test (this->opts_.stop_);

        // Notify loaded service of test shutdown.
        svc_mgr.handle_shutdown (this->opts_.stop_);
      }
      else
      {
        if (retval == -1)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to teardown test\n"));
        }
        else if (retval == 1)
        {
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - the state of shutdown is unknown\n"));
        }

        return -1;
      }
    }

    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - test is complete\n")));
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  return 1;
}

//
// shutdown
//
int CUTS_Testing_App::shutdown (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::shutdown (void)");

  // Wake all threads waiting for shutdown event.
  if (this->opts_.test_duration_ != ACE_Time_Value::zero)
    this->task_.stop_test ();

  return 0;
}

//
// print_help
//
void CUTS_Testing_App::print_help (void)
{
  std::cout
    << ::__USAGE__ << std::endl
    << ::__HELP__ << std::endl;

  ACE_OS::exit (0);
}

//
// deploy_test
//
int CUTS_Testing_App::deploy_test (ACE_Process_Options & options)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::deploy_test (void)");

  if (!options.working_directory () &&
      !this->opts_.working_directory_.empty ())
  {
    options.working_directory (this->opts_.working_directory_.c_str ());
  }

  ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();
  pid_t pid = proc_man->spawn (options);

  if (pid != ACE_INVALID_PID)
  {
    // The spawned application should return, so we can just wait on it.
    ACE_exitcode status;
    pid_t retval = proc_man->wait (pid, &status);

    switch (retval)
    {
    case 0:
      // Get the current time for test startup.
      this->opts_.start_ = ACE_OS::gettimeofday ();
      break;

    case ACE_INVALID_PID:
      ACE_ERROR_RETURN ((LM_WARNING,
                         "%T (%t) - %M - failed to wait for startup process "
                         "to exit [%m]\n"),
                         1);
      break;

    default:
      if (status == 0)
      {
        this->opts_.stop_ = ACE_OS::gettimeofday ();
      }
      else
      {
        ACE_ERROR_RETURN ((LM_WARNING,
                           "%T - %M - startup proess exit status was %d\n",
                           status),
                           -1);
      }
    }
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to execute startup process\n"),
                       -1);
  }

  return 0;
}

//
// teardown_test
//
int CUTS_Testing_App::
teardown_test (ACE_Process_Options & options)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::teardown_test (void)");

  if (!options.working_directory () &&
      !this->opts_.working_directory_.empty ())
  {
    options.working_directory (this->opts_.working_directory_.c_str ());
  }

  // Run the teardown command for the test.
  ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();
  pid_t pid = proc_man->spawn (options);

  if (pid != ACE_INVALID_PID)
  {
    // Run the shutdown command. But, let's only wait for a certain
    // amount of time just in case it doesn't want to return. ;-)
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - waiting %d second(s) for shutdown process...\n",
                this->opts_.shutdown_timeout_.sec ()));

    ACE_exitcode status;
    pid_t retval = proc_man->wait (pid,
                                   this->opts_.shutdown_timeout_,
                                   &status);

    switch (retval)
    {
    case 0:
      // There was a timeout.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - shutdown process timed out\n"));
      this->opts_.stop_ = ACE_OS::gettimeofday ();
      break;

    case ACE_INVALID_PID:
      ACE_ERROR_RETURN ((LM_WARNING,
                         "%T (%t) - %M - failed to wait for teardown process "
                         "to exit [%m]\n"),
                         1);
      break;

    default:
      // Save the time of day, but check the return status.
      this->opts_.stop_ = ACE_OS::gettimeofday ();

      if (status != 0)
        ACE_ERROR_RETURN ((LM_WARNING,
                           "%T - %M - shutdown process exit status was %d\n",
                           status),
                           -1);
    }
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to execute shutdown process\n"),
                       -1);
  }

  return 0;
}

//
// load_configuration
//
int CUTS_Testing_App::
load_configuration (CUTS_Testing_Service_Manager & mgr,
                    const ACE_CString & filename)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::load_configuration (const ACE_CString &)");

  if (filename.empty ())
    return 0;

  // First, read the configuration into memory.
  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - loading configuration %s\n",
              filename.c_str ()));

  CUTS_Test_Configuration_File file (this->props_);

  XSC::XML::XML_Error_Handler error_handler;
  file->setErrorHandler (&error_handler);

  if (!file.load (filename.c_str ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to read configuration file [%s]\n",
                       filename.c_str ()),
                       -1);
  }

  // First, load the services from the configuration.
  if (file.config ().services_p ())
    mgr.load_services (file.config ().services ());

  // Next, load the startup/shutdown commands, if present.
  if (this->opts_.startup_.get () == 0 &&
      file.config ().startup_p ())
  {
    ACE_Process_Options * options = 0;

    ACE_NEW_THROW_EX (options,
                      ACE_Process_Options (),
                      ACE_bad_alloc ());

    this->opts_.startup_.reset (options);

    // Get the startup process for the test.
    file.get_startup_process (*options);
  }

  if (this->opts_.shutdown_.get () == 0 &&
      file.config ().shutdown_p ())
  {
    ACE_Process_Options * options = 0;

    ACE_NEW_THROW_EX (options,
                      ACE_Process_Options (),
                      ACE_bad_alloc ());

    this->opts_.shutdown_.reset (options);

    // Get the shutdown process for the test.
    file.get_shutdown_process (*options);
  }

  return 0;
}
