// $Id$

#include "Testing_App.h"
#include "Testing_App_Task.h"

#include "cuts/utils/ODBC/ODBC_Connection.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Parameter.h"
#include "cuts/Auto_Functor_T.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "ace/Reactor.h"
#include "ace/Guard_T.h"

#include <sstream>

#define VERBOSE_MSG(params) \
  if (this->verbose_) \
  { \
    ACE_DEBUG (params); \
  }

static const char * __help__ =
"Usage: cuts_test [OPTIONS]\n"
"Test manager for CUTS-based experiments.\n"
"\n"
"OPTIONS:\n"
"  -n=NAME               Name for test manager; '(default)' is default\n"
"  --server=HOSTNAME     Location of CUTS test database\n"
"  -t, --time            Test duration in seconds (default = 60)\n"
"\n"
"  -v, --verbose         Print verbose infomration\n" 
"  -h, --help            Print this help message\n";

//
// CUTS_Testing_App
// 
CUTS_Testing_App::CUTS_Testing_App (void)
: name_ ("(default)"),
  verbose_ (false),
  test_number_ (-1),
  test_duration_ (60),
  test_timer_id_ (-1),
  shutdown_ (this->lock_)
{
  CUTS_Testing_App_Task * task = 0;
  ACE_NEW (task, CUTS_Testing_App_Task (*this));
  this->task_.reset (task);
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
  ACE_Get_Opt get_opt (argc, argv, opts, 0);

  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("database", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("time", 't', ACE_Get_Opt::ARG_REQUIRED);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
      {
        this->name_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        this->verbose_ = true;
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
        std::istringstream istr (get_opt.opt_arg ());
        istr >> this->test_duration_;
      }
      else
      {
        ACE_ERROR ((LM_NOTICE,
                    "ignoring --%s unknown argument\n",
                    get_opt.long_option ()));
      }

      break;

    case 'n':
      this->name_ = get_opt.opt_arg ();
      break;

    case 'v':
      this->verbose_ = true;
      break;

    case 'h':
      this->print_help ();
      break;

    case 't':
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> this->test_duration_;
      }
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR, 
                         "-%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;

    case '?':
      ACE_ERROR ((LM_WARNING, 
                  "-%c is an unknown argument\n",
                  get_opt.opt_opt ()));
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

  if (!this->server_addr_.empty ())
  {
    // Establish a connection with the database, and create a new
    // test for this experiment.
    this->connect_to_database ();

    if (this->start_new_test () != 0)
    {
      ACE_ERROR ((LM_ERROR,
                   "*** error: failed to start a new test on %s",
                   this->server_addr_.c_str ()));
    }
  }
  else
  {
    VERBOSE_MSG ((LM_INFO,
                  "*** info: not registering test run with database\n",
                  this->server_addr_.c_str ()));
  }

  // Start the testing application's task.
  this->task_->start ();

  // Start the actual test.
  ACE_DEBUG ((LM_INFO,
              "*** info: running test for %d second(s)\n",
              this->test_duration_));

  ACE_Time_Value duration (this->test_duration_);
  this->test_timer_id_ = this->task_->start_test (duration);
  
  if (this->test_timer_id_ != -1)
  {
    // Wait for testing application to receive shutdown event.
    ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, -1);
    this->shutdown_.wait ();
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error: failed to start test\n"));
  }

  if (this->test_timer_id_ != -1)
  {
    // Stop the currently executing test.
    this->task_->stop_test (this->test_timer_id_);
    this->test_timer_id_ = -1;
  }

  VERBOSE_MSG ((LM_DEBUG, 
                "*** info: stopping the current test\n"));

  if (this->stop_current_test () == -1)
  {
    ACE_ERROR ((LM_ERROR, 
                "*** error: failed to stop current test (%d)\n",
                this->test_number_));
  }

  // Shutdown the testing application task.
  VERBOSE_MSG ((LM_DEBUG,
                "*** debug: waiting for application task to stop\n"));
  this->task_->stop ();

  return 0;
}

//
// shutdown
//
void CUTS_Testing_App::shutdown (void)
{
  // Wake all threads waiting for shutdown event.
  VERBOSE_MSG ((LM_DEBUG,
                "*** debug: notifying all threads of shutdown event\n"));
  ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
  this->shutdown_.broadcast ();
}

//
// print_help
//
void CUTS_Testing_App::print_help (void)
{
  std::cerr << ::__help__ << std::endl;
  ACE_OS::exit (0);
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
  VERBOSE_MSG ((LM_INFO,
                "*** info: connecting to test database on %s\n",
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
  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare the statement for exection.
    const char * str_stmt =
      "INSERT INTO tests (start_time, status) VALUES (NOW(), 'active')";

    // Execute the statement and get the last inserted id.
    VERBOSE_MSG ((LM_DEBUG, "*** debug : creating a new test in database\n"));
    query->execute_no_record (str_stmt);
    this->test_number_ = query->last_insert_id ();
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error : %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error : caught unknown exception\n"));
  }

  return -1;
}

//
// stop_current_test
//
int CUTS_Testing_App::stop_current_test (void)
{
  if (this->test_number_ == -1)
    return 1;

  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    const char * str_stmt =
      "UPDATE tests SET stop_time = NOW(), status = 'inactive' "
      "WHERE (test_number = ?)";

    // Create the binding for initializing a test.
    query->prepare (str_stmt);
    query->parameter (0)->bind (&this->test_number_);

    // Execute the statement and reset the test number.
    query->execute_no_record ();
    this->test_number_ = -1;
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error : %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error : caught known exception\n"));
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
  return this->name_;
}
