// $Id$

#include "Testing_App.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_App.inl"
#endif

#include "Testing_Service_Manager.h"
#include "Test_Configuration_File.h"
#include "Testing_Service.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"
#include "ace/Reactor.h"
#include "ace/streams.h"
#include "ace/UUID.h"
#include "boost/bind.hpp"
#include "XSCRT/utils/Console_Error_Handler.h"
#include <sstream>
#include <algorithm>

static const char * __USAGE__ =
"Test manager for CUTS-based experiments\n"
"\n"
"USAGE: cutstest [OPTIONS]\n";

static const char * __HELP__ =
"OPTIONS:\n"
"  -n, --name=NAME         name for test manager (default='(default)')\n"
"  -c, --config=FILE       configuration file for test\n"
"  --time=TIME             test duration in seconds (default=60)\n"
"  --uuid=UUID             user-defined UUID for the test\n"
"\n"
"  -C, --directory=DIR     change to directory DIR\n"
"  --startup=CMD           use CMD to startup test\n"
"  --shutdown=CMD          use CMD to shutdown test\n"
"\n"
"  -v, --verbose           print verbose infomration\n"
"  --debug                 print debugging information\n"
"  -h, --help              print this help message\n"
"\n"
"DEPLOY\\TEARDOWN:\n"
"If you specify the --deploy option, then you must specify the --teardown\n"
"option. Also, the process spawned by the --deploy option must exit so the\n"
"--teardown option can execute.\n";

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
  const char * opts = ACE_TEXT ("n:vht:c:");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("time", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("uuid", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("directory", 'C', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("startup", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("shutdown", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("trace", ACE_Get_Opt::NO_ARG);

  char ch;

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
        this->opts_.deploy_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "shutdown") == 0)
      {
        this->opts_.teardown_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "directory") == 0)
      {
        this->opts_.working_directory_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "uuid") == 0)
      {
        this->opts_.uuid_.from_string (get_opt.opt_arg ());
      }
      break;

    case 'n':
      this->opts_.name_ = get_opt.opt_arg ();
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

  // Instantiate a service manager that valid only in this scope.
  CUTS_Testing_Service_Manager manager (*this);
  this->svc_mgr_ = &manager;

  // Load the configuration this test run.
  if (this->load_configuration (manager, this->opts_.config_) != 0)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to load test configuration\n"));
  }

  if (!this->opts_.deploy_.empty ())
  {
    // Deploy the test into the environment.
    int retval = this->deploy_test ();

    if (retval == 0)
    {
      manager.handle_startup (this->opts_.start_);
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

  if (!this->opts_.teardown_.empty ())
  {
    // Execute the shutdown command for the test.
    int retval = this->teardown_test ();

    if (retval == 0)
    {
      manager.handle_shutdown (this->opts_.stop_);
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

  return 0;
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
int CUTS_Testing_App::deploy_test (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::deploy_test (void)");

  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", this->opts_.deploy_.c_str ());

  if (this->opts_.working_directory_.empty ())
    options.working_directory (this->opts_.working_directory_.c_str ());

  // Process id of the deployment application during its deploy stage
  // of the test.
  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - running deploy command for the test [%s]\n",
              this->opts_.deploy_.c_str ()));

  // Get the current time for test startup.
  this->opts_.start_ = ACE_OS::gettimeofday ();

  ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();
  pid_t pid = proc_man->spawn (options);

  if (pid != ACE_INVALID_PID)
  {
    // The spawned application should return, so we can just wait on it.
    ACE_exitcode status;
    pid_t retval = proc_man->wait (pid, &status);

    if (retval == ACE_INVALID_PID)
    {
      ACE_ERROR_RETURN ((LM_WARNING,
                         "%T (%t) - %M - failed to wait for deploy process "
                         "to exit [%m]\n"),
                         1);
    }
    else if (status != 0)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T - %M - deploy proess exit status was %d\n",
                  status));
    }
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to run deploy process [cmd="
                       "'%s'; cwd='%s']\n",
                       this->opts_.deploy_.c_str (),
                       options.working_directory ()),
                       -1);
  }

  return 0;
}

//
// teardown_test
//
int CUTS_Testing_App::teardown_test (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::teardown_test (void)");

  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", this->opts_.teardown_.c_str ());

  if (this->opts_.working_directory_.empty ())
  {
    options.working_directory (
      this->opts_.working_directory_.c_str ());
  }

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - running teardown command for the test [%s]\n",
              this->opts_.teardown_.c_str ()));

  // Get the current time for test teardown.
  this->opts_.stop_ = ACE_OS::gettimeofday ();

  // Run the teardown command for the test.
  ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();
  pid_t pid = proc_man->spawn (options);

  if (pid != ACE_INVALID_PID)
  {
    // The spawned application should return, so we can just wait on it.
    ACE_exitcode status;
    pid_t retval = proc_man->wait (pid, &status);

    if (retval == ACE_INVALID_PID)
    {
      ACE_ERROR_RETURN ((LM_WARNING,
                         "%T (%t) - %M - failed to wait for teardown process "
                         "to exit [%m]\n"),
                         1);
    }
    else if (status != 0)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T (%t) - %M - teardown proess exit status was %d\n",
                  status));
    }
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to run teardown process [cmd="
                       "'%s'; cwd='%s']\n",
                       this->opts_.deploy_.c_str (),
                       options.working_directory ()),
                       -1);
  }

  return 0;
}

//
// load_configuration
//
int CUTS_Testing_App::load_configuration (CUTS_Testing_Service_Manager & mgr,
                                          const ACE_CString & filename)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::load_configuration (const ACE_CString &)");

  if (filename.empty ())
    return 0;

  // First, read the configuration into memory.
  CUTS_Test_Configuration_File file;

  XSCRT::utils::Console_Error_Handler * error_handler = 0;
  ACE_NEW_NORETURN (error_handler, XSCRT::utils::Console_Error_Handler ());
  file.parser ()->setErrorHandler (error_handler);

  if (!file.read (filename.c_str ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to read configuration file [%s]\n",
                       filename.c_str ()),
                       -1);
  }

  // Transform the XML document into usable objects.
  CUTS::testFile config;
  file >>= config;

  if (config.services_p ())
  {
    std::for_each (config.services ().begin_service (),
                   config.services ().end_service (),
                   boost::bind (&CUTS_Testing_App::load_service,
                                boost::ref (mgr),
                                _1));
  }

  return 0;
}

//
// load_service
//
int CUTS_Testing_App::
load_service (CUTS_Testing_Service_Manager & mgr,
              const CUTS::serviceDescription & desc)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::load_service (const CUTS::serviceDescription &)");

  return mgr.load_service (desc.id ().c_str (),
                           desc.location ().c_str (),
                           desc.entryPoint ().c_str (),
                           desc.params_p () ? desc.params ().c_str () : 0);
}
