// $Id$

#include "Testing_App.h"
#include "Testing_App_Task.h"
#include "Testing_Options.h"

#include "cuts/utils/ODBC/ODBC_Connection.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Parameter.h"
#include "cuts/Auto_Functor_T.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "ace/Reactor.h"
#include "ace/Guard_T.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"
#include "ace/UUID.h"

#include <sstream>

static const char * __USAGE__ =
"Test manager for CUTS-based experiments\n"
"\n"
"USAGE: cutstest [OPTIONS]\n";

static const char * __HELP__ =
"OPTIONS:\n"
"  -n, --name=NAME         name for test manager (default='(default)')\n"
"  --database=HOSTNAME     location of CUTS database (default='localhost')\n"
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
: test_number_ (-1),
  test_timer_id_ (-1),
  shutdown_ (this->lock_)
{
  // Create the testing application task.
  CUTS_Testing_App_Task * task = 0;
  ACE_NEW (task, CUTS_Testing_App_Task (*this));
  this->task_.reset (task);

  // Initialize the UUID generator.
  ACE_Utils::UUID_GENERATOR::instance ()->init ();
}

//
// CUTS_Testing_App
//
CUTS_Testing_App::~CUTS_Testing_App (void)
{

}

//
// parse_args
//
int CUTS_Testing_App::parse_args (int argc, char * argv [])
{
  // Now, parse the remaining command-line options.
  const char * opts = ACE_TEXT ("n:vht:");
  ACE_Get_Opt get_opt (argc, argv, opts);

  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("database", ACE_Get_Opt::ARG_REQUIRED);
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
      if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
      {
        CUTS_TESTING_OPTIONS->name_ = get_opt.opt_arg ();
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
      else if (ACE_OS::strcmp (get_opt.long_option (), "database") == 0)
      {
        this->server_addr_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "time") == 0)
      {
        time_t seconds;
        std::istringstream istr (get_opt.opt_arg ());
        istr >> seconds;

        CUTS_TESTING_OPTIONS->test_duration_.sec (seconds);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "deploy") == 0)
      {
        CUTS_TESTING_OPTIONS->deploy_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "teardown") == 0)
      {
        CUTS_TESTING_OPTIONS->teardown_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "directory") == 0)
      {
        CUTS_TESTING_OPTIONS->working_directory_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "uuid") == 0)
      {
        ACE_Utils::UUID * uuid = 0;
        ACE_NEW_NORETURN (uuid, ACE_Utils::UUID (get_opt.opt_arg ()));

        this->test_uuid_.reset (uuid);
      }
      break;

    case 'n':
        CUTS_TESTING_OPTIONS->name_ = get_opt.opt_arg ();
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
      CUTS_TESTING_OPTIONS->working_directory_ = get_opt.opt_arg ();
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - -%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;
    };
  }

  if (!CUTS_TESTING_OPTIONS->deploy_.empty () &&
      CUTS_TESTING_OPTIONS->teardown_.empty ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - deploy command MUST also have a teardown "
                       "command; please add a --teardown option\n"),
                       -1);
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

  return this->run_main_i ();
}

//
// run_main_i
//
int CUTS_Testing_App::run_main_i (void)
{
  if (!this->server_addr_.empty ())
    this->connect_to_database ();

  if (this->start_new_test () != 0)
  {
    ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to start a new test on %s\n",
                  this->server_addr_.c_str ()));
  }

  // Start the testing application's task.
  this->task_->start ();

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

  // Start the actual test.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - running test for %d second(s)\n",
              CUTS_TESTING_OPTIONS->test_duration_.sec ()));

  this->test_timer_id_ =
    this->task_->start_test (CUTS_TESTING_OPTIONS->test_duration_);

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

  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - stopping the current test\n"));

  if (this->stop_current_test () == -1)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to stop current test (%d)\n",
                this->test_number_));
  }

  // Shutdown the testing application task.
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - waiting for application task to stop\n"));
  this->task_->stop ();

  return 0;
}

//
// shutdown
//
int CUTS_Testing_App::shutdown (void)
{
  // Teardown the current test.
  this->teardown_test ();

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
  std::cout << ::__USAGE__ << std::endl;
  this->print_help_i ();
  ACE_OS::exit (0);
}

//
// print_help_i
//
void CUTS_Testing_App::print_help_i (void)
{
  std::cout << ::__HELP__ << std::endl;
}

//
// connect_to_database
//
void CUTS_Testing_App::connect_to_database (void)
{
  // Create a new database connection.
  CUTS_DB_Connection * conn = 0;
  ACE_NEW (conn, ODBC_Connection ());
  this->conn_.reset (conn);

  // Connect to the specified server using the default port.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - connecting to test database on %s\n",
              this->server_addr_.c_str ()));

  this->conn_->connect (CUTS_USERNAME,
                        CUTS_PASSWORD,
                        this->server_addr_.c_str (),
                        CUTS_DEFAULT_PORT);
}

//
// start_new_test
//
int CUTS_Testing_App::start_new_test (void)
{
  if (this->test_uuid_.get () == 0)
  {
    // First, generate a new UUID for the test.
    ACE_Utils::UUID * uuid =
      ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID ();

    this->test_uuid_.reset (uuid);
  }

  ACE_DEBUG ((LM_INFO,
              "%T - %M - test UUID is %s\n",
              this->test_uuid_->to_string ()->c_str ()));

  if (this->server_addr_.empty ())
  {
    ACE_DEBUG ((LM_INFO,
                "%T - %M - not registering test run with database\n",
                this->server_addr_.c_str ()));
    return 0;
  }

  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare the statement for exection.
    const char * str_stmt = "CALL cuts.start_new_test (?, NOW())";
    query->prepare (str_stmt);

    char uuid[64];
    ACE_OS::strcpy (uuid, this->test_uuid_->to_string ()->c_str ());

    query->parameter(0)->bind (uuid, 0);

    // Execute the statement and get the last inserted id.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - creating a new test in database\n"));
    query->execute_no_record (str_stmt);
    this->test_number_ = query->last_insert_id ();
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }

  return -1;
}

//
// stop_current_test
//
int CUTS_Testing_App::stop_current_test (void)
{
  if (this->test_timer_id_ != -1)
  {
    // Stop the currently executing test.
    this->task_->stop_test (this->test_timer_id_);
    this->test_timer_id_ = -1;
  }

  if (this->test_number_ == -1)
    return 0;

  // Let the database know the current test has stopped.
  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare the statement for execution.
    const char * str_stmt = "CALL cuts.stop_existing_test (?, NOW())";
    query->prepare (str_stmt);

    char uuid[64];
    ACE_OS::strcpy (uuid, this->test_uuid_->to_string ()->c_str ());

    query->parameter(0)->bind (uuid, 0);

    // Execute the statement and reset the test number.
    query->execute_no_record ();
    this->test_number_ = -1;

    // Reset the test uuid.
    this->test_uuid_.reset ();
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught known exception\n"));
  }

  return -1;
}

//
// current_test_number
//
long CUTS_Testing_App::current_test_number (void) const
{
  return this->test_number_;
}

//
// name
//
const ACE_CString & CUTS_Testing_App::name (void) const
{
  return CUTS_TESTING_OPTIONS->name_;
}

//
// deploy_test
//
int CUTS_Testing_App::deploy_test (void)
{
  if (CUTS_TESTING_OPTIONS->deploy_.empty ())
    return 0;

  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", CUTS_TESTING_OPTIONS->deploy_.c_str ());

  if (CUTS_TESTING_OPTIONS->working_directory_.empty ())
  {
    options.working_directory (
      CUTS_TESTING_OPTIONS->working_directory_.c_str ());
  }

  // Process id of the deployment application during its deploy stage
  // of the test.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - running deploy command for the test [%s]\n",
              CUTS_TESTING_OPTIONS->deploy_.c_str ()));

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
                       CUTS_TESTING_OPTIONS->deploy_.c_str (),
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
  if (CUTS_TESTING_OPTIONS->teardown_.empty ())
    return 0;

  // Initialize the process options.
  ACE_Process_Options options;
  options.command_line ("%s", CUTS_TESTING_OPTIONS->teardown_.c_str ());

  if (CUTS_TESTING_OPTIONS->working_directory_.empty ())
  {
    options.working_directory (
      CUTS_TESTING_OPTIONS->working_directory_.c_str ());
  }

  // Run the teardown command for the test.
  ACE_DEBUG ((LM_INFO,
              "%T - %M - running teardown command for the test [%s]\n",
              CUTS_TESTING_OPTIONS->teardown_.c_str ()));
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
                       CUTS_TESTING_OPTIONS->deploy_.c_str (),
                       options.working_directory ()),
                       -1);
  }

  return 0;
}

//
// test_uuid
//
const ACE_Utils::UUID & CUTS_Testing_App::test_uuid (void) const
{
  return *this->test_uuid_.get ();
}

//
// test_name
//
const ACE_CString & CUTS_Testing_App::test_name (void) const
{
  return CUTS_TESTING_OPTIONS->name_;
}
