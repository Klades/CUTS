// $Id$

#include "Node_Daemon.h"

#if !defined (__CUTS_INLINE__)
#include "Node_Daemon.inl"
#endif

#include "cutsnode.h"
#include "Node_File_Reader.h"
#include "Process_Options.h"
#include "Text_Variable_Importer.h"
#include "Virtual_Env.h"

#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "XSC/utils/XML_Error_Handler.h"

#include "boost/bind.hpp"
#include "boost/graph/adjacency_list.hpp"

#include <algorithm>
#include <iostream>

/**
 * @struct install_process
 *
 * Functor for installing a process into an enviroment.
 */
struct install_process
{
  typedef CUTS::schemas::ProcessList::process_iterator::value_type value_type;

  install_process (CUTS_Virtual_Env & env, bool startup)
    : env_ (env),
      startup_ (startup)
  {

  }

  void operator () (const value_type & value)
  {
    CUTS_Process_Options opts;

    // Initialize the process options.
    opts.name_ = value->id ().c_str ();
    opts.exec_ = value->executable ().c_str ();

    if (value->arguments_p ())
      opts.args_  = value->arguments ().c_str ();

    if (value->workingdirectory_p ())
      opts.cwd_ = value->workingdirectory ().c_str ();

    if (value->delay_p ())
      opts.delay_.set (value->delay ());

    if (value->waitforcompletion_p ())
      opts.wait_for_completion_ = value->waitforcompletion ();

    // Install the process into the environment.
    int retval;

    if (this->startup_)
      retval = this->env_.startup_list ().append (opts);
    else
      retval = this->env_.shutdown_list ().append (opts);

    if (0 != retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to add %s to %s process list\n"),
                  opts.name_.c_str (),
                  this->startup_ ? ACE_TEXT ("startup") : ACE_TEXT ("shutdown")));
  }

private:
  CUTS_Virtual_Env & env_;

  bool startup_;
};

/**
 * @struct import_variables
 *
 * Functor for importing variables from a file into the
 * environment table
 */
struct import_variables
{
  typedef ::CUTS::schemas::VariableList::import_iterator::value_type value_type;

  import_variables (CUTS_Property_Map & env_table)
    : env_table_ (env_table)
  {

  }

  void operator () (const value_type & value)
  {
    CUTS_Variable_Importer_Strategy * strategy = 0;

    if (value->type () == CUTS::schemas::FileType::text)
    {
      static CUTS_Text_Variable_Importer text_import;
      strategy = &text_import;
    }

    if (0 != strategy)
    {
      int retval =
        strategy->handle_import (value->location ().c_str (),
                                 this->env_table_);

      if (0 != retval)
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to import variables from %s\n"),
                    value->location ().c_str ()));
    }
  }

private:
  /// Target environment variable table.
  CUTS_Property_Map & env_table_;
};

/**
 * @struct insert_variable
 *
 * Functor for inserting variables into an environment table
 */
struct insert_variable
{
  typedef ::CUTS::schemas::VariableList::variable_iterator::value_type value_type;

  insert_variable (CUTS_Property_Map & env_table)
    : env_table_ (env_table)
  {

  }

  void operator () (const value_type & var)
  {
    int retval =
      this->env_table_.set (var->name ().c_str (), var->value ().c_str ());

    if (1 == retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - %s already exists\n"),
                  var->name ().c_str ()));
  }

private:
  /// Target environment variable table.
  CUTS_Property_Map & env_table_;
};

//
// operator <<= (CUTS_Property_Map &, const CUTS::schemas::VariableList &)
//
bool
operator <<= (CUTS_Property_Map & env_table, const CUTS::schemas::VariableList & variables)
{
  // First, import the specified environment variables
  std::for_each (variables.begin_import (),
                 variables.end_import (),
                 import_variables (env_table));

  // Next, insert the new environment variables.
  std::for_each (variables.begin_variable (),
                 variables.end_variable (),
                 insert_variable (env_table));

  return true;
}

//
// operator <<= (CUTS_Virtual_Env &, const CUTS::schemas::EnvConfig &)
//
bool
operator <<= (CUTS_Virtual_Env & env, const CUTS::schemas::EnvConfig & config)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading environment's configuration\n")));

  if (config.variables_p ())
    env.env_table () <<= config.variables ();

  if (config.startup_p ())
    std::for_each (config.startup ().begin_process (),
                   config.startup ().end_process (),
                   install_process (env, true));

  if (config.shutdown_p ())
    std::for_each (config.shutdown ().begin_process (),
                   config.shutdown ().end_process (),
                   install_process (env, false));

  return true;
}

/**
 * @struct insert_environment
 *
 * Functor for inserting environments into the node.
 */
struct insert_environment
{
  typedef ::CUTS::schemas::NodeConfig::environment_iterator::value_type value_type;

  insert_environment (CUTS_Virtual_Env_Manager & env_mgr, ACE_CString & active_env)
    : env_mgr_ (env_mgr),
      active_env_ (active_env)
  {

  }

  void operator () (const value_type & val)
  {
    ACE_DEBUG ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - constructing %s environment\n"),
                val->id ().c_str ()));

    // Allocate a new virtual environment.
    CUTS_Virtual_Env * env = 0;
    this->env_mgr_.create (val->id ().c_str (), env);

    *env <<= *val;

    if (val->active_p () && val->active ())
      this->active_env_ = val->id ().c_str ();
  }

private:
  CUTS_Virtual_Env_Manager & env_mgr_;

  ACE_CString & active_env_;
};

//
// __HELP__
//
static const char * __HELP__ =
"CUTS node manager for remotely invoking task on target \n"
"\n"
"USAGE: cutsnode_d [OPTIONS]\n"
"\n"
"Options:\n"
"  -d, --working-directory=DIR        working directory for the daemon\n"
"  -c, --config=FILE                  initial configuration file\n"
"  --active-env=NAME                  set NAME as the active environment\n"
"\n"
"  --disable-server                   disable remoting server\n"
"  --server-args=ARGS                 arguments for the server\n"
"\n"
"  -DNAME=VALUE                       define property NAME=VALUE\n"
"\n"
"  -v, --verbose                      print verbose infomration\n"
"  --debug                            print debugging information\n"
"  -h, --help                         print this help message\n";

//
// CUTS_Node_Daemon_App
//
CUTS_Node_Daemon_App::CUTS_Node_Daemon_App (void)
: is_shutdown_ (shutdown_),
  server_ (virtual_envs_)
{

}

//
// run_main
//
int CUTS_Node_Daemon_App::run_main (int argc, char * argv [])
{
  // Parse the remaining arguments.
  if (this->parse_args (argc, argv) == -1)
    return 1;

  // Load the initial configuration.
  ACE_CString active_env;

  if (-1 == this->load_initial_config (active_env))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                       -1);

  if (!this->opts_.disable_server_)
    this->server_.init (this->opts_.server_opts_.argc (),
                        this->opts_.server_opts_.argv ());

  // The active environment specified at the command-line overrides
  // the one specified in the configuration file.
  if (!this->opts_.active_env_.empty ())
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - setting %s to active environment\n"),
                this->opts_.active_env_.c_str ()));

    this->virtual_envs_.set_active_environment (this->opts_.active_env_);
  }
  else if (!active_env.empty ())
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - setting %s to active environment\n"),
                active_env.c_str ()));

    this->virtual_envs_.set_active_environment (active_env);
  }
  else
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - no environment is active\n")));
  }

  // Wait for the process to shutdown.
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - node daemon is now active\n")));

  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->shutdown_, -1);
  this->is_shutdown_.wait ();

  // Shutdown the server.
  if (!this->opts_.disable_server_)
    this->server_.fini ();

  return 0;
}

//
// close
//
void CUTS_Node_Daemon_App::close (void)
{
  this->virtual_envs_.close ();
}

//
// parse_args
//
int CUTS_Node_Daemon_App::parse_args (int argc, char * argv [])
{
  // Setup the <ACE_Get_Opt> variable.
  const char * opts = "c:vd:D:";
  ACE_Get_Opt get_opt (argc, argv, opts);

  // Setup the long options for the command-line
  get_opt.long_option ("working-directory", 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("active-env", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("disable-server");
  get_opt.long_option ("server-args", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  int option;
  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "working-directory") == 0)
      {
        this->opts_.init_dir_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "debug") == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
      {
        this->opts_.config_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "active-env") == 0)
      {
        this->opts_.active_env_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        std::cout << __HELP__ << std::endl;
        ACE_OS::exit (1);
      }
      else if (0 == ACE_OS::strcmp (get_opt.long_option (), "server-args"))
      {
        this->opts_.server_opts_.add (get_opt.opt_arg ());
      }
      else if (0 == ACE_OS::strcmp (get_opt.long_option (), "disable-server"))
      {
        this->opts_.disable_server_ = true;
      }
      break;

    case 'c':
      this->opts_.config_ = get_opt.opt_arg ();
      break;

    case 'd':
      this->opts_.init_dir_ = get_opt.opt_arg ();
      break;

    case 'h':
      std::cout << __HELP__ << std::endl;
      ACE_OS::exit (1);
      break;

    case 'D':
      this->opts_.defines_.push_back (get_opt.opt_arg ());
      break;

    case 'v':
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case '?':
      /* unknown option; do nothing */
      break;

    case ':':
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - %c is missing an argument\n",
                  get_opt.opt_opt ()));
      return -1;
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// shutdown
//
void CUTS_Node_Daemon_App::shutdown (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->shutdown_);
  this->is_shutdown_.signal ();
}

//
// load_initial_config
//
int CUTS_Node_Daemon_App::load_initial_config (ACE_CString & active)
{
  if (this->opts_.config_.empty ())
    return -1;

  ACE_DEBUG ((LM_INFO,
              "%T (%t) - %M - loading initial configuration [file=%s]\n",
              this->opts_.config_.c_str ()));

  try
  {
    CUTS_Node_File_Reader reader;

    // Configure the error handler.
    XSC::XML::XML_Error_Handler error_handler;
    reader->setErrorHandler (&error_handler);

    // Open the default configuration.
    if (!reader.read (this->opts_.config_.c_str ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open configuration file [%s]\n"),
                         this->opts_.config_.c_str ()),
                         -1);
    }

    // Read the configuration from the XML file.
    CUTS::schemas::NodeConfig config;
    reader >>= config;

    insert_environment inserter (this->virtual_envs_, active);

    // Construct the virtual environments from the configuration.
    std::for_each (config.begin_environment (),
                   config.end_environment (),
                   inserter);

    return 0;
  }
  catch (const xercesc::DOMException & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.getMessage ()));
  }
  catch (const xercesc::XMLException & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.getMessage ()));
  }

  return -1;
}
