// $Id$

#include "Testing_App.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_App.inl"
#endif

#include "Test_Configuration_File.h"
#include "Testing_Service.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"
#include "ace/Reactor.h"
#include "ace/Service_Types.h"
#include "ace/streams.h"
#include "ace/UUID.h"
#include "boost/bind.hpp"
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
"  --deploy=CMD            use CMD to deploy test\n"
"  --teardown=CMD          use CMD to teardown test\n"
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
: test_timer_id_ (-1),
  task_ (*this),
  shutdown_ (this->lock_)
{
  ACE_Utils::UUID_GENERATOR::instance ()->init ();
  this->svc_config_.open ("cutstest");
}

//
// parse_args
//
int CUTS_Testing_App::parse_args (int argc, char * argv [])
{
  // Now, parse the remaining command-line options.
  const char * opts = ACE_TEXT ("n:vht:c:");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("time", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("uuid", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("directory", 'C', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("deploy", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("teardown", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

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

        ACE_Log_Msg::instance ()->priority_mask (mask);
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
      else if (ACE_OS::strcmp (get_opt.long_option (), "deploy") == 0)
      {
        this->opts_.deploy_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "teardown") == 0)
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

  return 0;
}

//
// run_main
//
int CUTS_Testing_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) == -1)
    return -1;

  if (!this->opts_.config_.empty ())
  {
    if (this->load_configuration () != 0)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to load test configuration\n"));
    }
  }

  // Start the testing application's task.
  this->task_.start ();

  if (this->opts_.deploy_.empty ())
  {
    // Deploy the test into the environment.
    int retval = this->deploy_test ();

    if (retval == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T - %M - aborting test since deployment failed\n"),
                        -1);
    }
    else if (retval == 1)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T - %M - state of deployment unknown; continuing...\n"));
    }
  }

  // Start the actual test.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - running test for %d second(s)\n",
              this->opts_.test_duration_.sec ()));

  this->test_timer_id_ =
    this->task_.start_test (this->opts_.test_duration_);

  if (this->test_timer_id_ != -1)
  {
    // Wait for testing application to receive shutdown event.
    ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, -1);
    this->shutdown_.wait ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to start test\n"));
  }

  // Shutdown the testing application task.
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - waiting for application task to stop\n"));
  this->task_.stop ();

  return 0;
}

//
// shutdown
//
int CUTS_Testing_App::shutdown (void)
{
  if (!this->opts_.teardown_.empty ())
  {
    // Teardown the current test.
    int retval = this->teardown_test ();

    if (retval == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T - %M - failed to teardown test\n"),
                        -1);
    }
  }

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - notifying all threads of shutdown event\n"));

  // Wake all threads waiting for shutdown event.
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, -1);
  this->shutdown_.broadcast ();
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
  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", this->opts_.deploy_.c_str ());

  if (this->opts_.working_directory_.empty ())
    options.working_directory (this->opts_.working_directory_.c_str ());

  // Process id of the deployment application during its deploy stage
  // of the test.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - running deploy command for the test [%s]\n",
              this->opts_.deploy_.c_str ()));

  // Get the current time for test startup.
  ACE_Time_Value tv = ACE_OS::gettimeofday ();

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
                         "%T - %M - failed to wait for deploy process "
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
                       "%T - %M - failed to run deploy process [cmd="
                       "'%s'; cwd='%s']\n",
                       this->opts_.deploy_.c_str (),
                       options.working_directory ()),
                       -1);
  }

  // Generate a new UUID for the deployment.
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (this->opts_.uuid_);

  // Finally, signal all the loaded services that a new test has been
  // activated. This will allow them to perform any initialization for
  // the test, such as storing its information.
  // Create an iterator to the underlying repo so we can
  // iterate over all the loaded services.
  const ACE_Service_Type * svc_type = 0;
  const ACE_Service_Type_Impl * type = 0;
  CUTS_Testing_Service * svc;

  ACE_Service_Repository_Iterator
    iter (*this->svc_config_.current_service_repository ());

  for (; !iter.done (); iter.advance ())
  {
    // Get the next service in the configurator.
    iter.next (svc_type);

    // Extract the CUTS_Testing_Service from the service object.
    if (svc_type != 0)
    {
      type = svc_type->type ();

      if (type != 0)
      {
        svc = reinterpret_cast <CUTS_Testing_Service *> (type->object ());
        svc->handle_startup (tv);
      }
    }
  }

  return 0;
}

//
// teardown_test
//
int CUTS_Testing_App::teardown_test (void)
{
  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", this->opts_.teardown_.c_str ());

  if (this->opts_.working_directory_.empty ())
  {
    options.working_directory (
      this->opts_.working_directory_.c_str ());
  }

  ACE_DEBUG ((LM_INFO,
              "%T - %M - running teardown command for the test [%s]\n",
              this->opts_.teardown_.c_str ()));

  // Get the current time for test teardown.
  ACE_Time_Value tv = ACE_OS::gettimeofday ();

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
                         "%T - %M - failed to wait for teardown process "
                         "to exit [%m]\n"),
                         1);
    }
    else if (status != 0)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T - %M - teardown proess exit status was %d\n",
                  status));
    }
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to run teardown process [cmd="
                       "'%s'; cwd='%s']\n",
                       this->opts_.deploy_.c_str (),
                       options.working_directory ()),
                       -1);
  }

  // Finally, signal all the loaded services that a the test has been
  // ended. This will allow them to perform any finalization for
  // the test, such as storing its information.
  const ACE_Service_Type * svc_type = 0;
  const ACE_Service_Type_Impl * type = 0;
  CUTS_Testing_Service * svc;

  ACE_Service_Repository_Iterator
    iter (*this->svc_config_.current_service_repository ());

  for (; !iter.done (); iter.advance ())
  {
    // Get the next service in the configurator.
    iter.next (svc_type);

    // Extract the CUTS_Testing_Service from the service object.
    if (svc_type != 0)
    {
      type = svc_type->type ();

      if (type != 0)
      {
        svc = reinterpret_cast <CUTS_Testing_Service *> (type->object ());
        svc->handle_shutdown (tv);
      }
    }
  }

  return 0;
}

//
// load_configuration
//
int CUTS_Testing_App::load_configuration (void)
{
  // First, read the configuration into memory.
  CUTS_Test_Configuration_File file;

  if (!file.read (this->opts_.config_.c_str ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to read configuration file [%s]\n",
                       this->opts_.config_.c_str ()),
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
                                this,
                                _1));
  }

  return 0;
}

//
// load_configuration
//
int CUTS_Testing_App::load_service (const CUTS::serviceDescription & desc)
{
  // Construct the directive for the service.
  std::ostringstream directive;
  directive
    << "dynamic " << desc.id () << " Service_Object * "
    << desc.location () << ":" << desc.entryPoint () << "() active";

  if (desc.params_p ())
  {
    directive
      << " \"" << desc.params () << "\"";
  }

  // Load the service into the service configurator.
  int retval =
    this->svc_config_.process_directive (directive.str ().c_str ());

  if (retval == 0)
  {
    // We need to locate the service that we just loaded.
    const ACE_Service_Type * svc_type = 0;

    if (this->svc_config_.find (desc.id ().c_str (), &svc_type) == 0)
    {
      // Extract the CUTS_Testing_Service object
      const ACE_Service_Type_Impl * type = svc_type->type ();

      CUTS_Testing_Service * svc =
        reinterpret_cast <CUTS_Testing_Service *> (type->object ());

      // Set the testing application for this service.
      if (svc != 0)
        svc->app_ = this;
    }
    else
    {
      ACE_ERROR ((LM_DEBUG,
                  "%T - %M - failed to initialize service %s\n",
                  desc.id ().c_str ()));
    }
  }

  return retval;
}
