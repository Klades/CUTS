// $Id$

#include "NodeDaemon_Client_App.h"

#if !defined (__CUTS_INLINE__)
#include "NodeDaemon_Client_App.inl"
#endif

#include "../server/NodeDaemonC.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

const char * __HELP__ =
"Remote client for the CUTS node daemon\n"
"\n"
"USAGE: cutsnode [OPTIONS]\n"
"\n"
"General options:\n"
"  --reset=VAL              reset current environment\n"
"  --set-active-env=NAME    set active environment to NAME\n"
"  --get-active-env         get name of the active environment\n"
"\n"
"Printing options:\n"
"  -h, --help               print this help message\n";

//
// run_main
//
int CUTS_NodeDaemon_Client_App::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")),
                         -1);

    // Resolve the node daemon.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("NodeDaemon");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve NodeDaemon\n")),
                         -1);

    ::CUTS::NodeDaemon_var daemon = ::CUTS::NodeDaemon::_narrow (obj.in ());

    if (::CORBA::is_nil (daemon.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a CUTS::NodeDaemon\n")),
                         -1);

    // Perform the requested operation. Right now, reseting the current
    // environment takes precedence over setting an active environment.
    if (this->reset_env_)
    {
      daemon->reset ();
    }
    else if (!this->set_active_env_.empty ())
    {
      daemon->set_active_environment (this->set_active_env_.c_str ());
    }

    if (this->get_active_env_)
    {
      ::CORBA::String_var str = daemon->active_environment ();
      std::cout << "active environment is: " << str.in () << std::endl;
    }

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// parse_args
//
int CUTS_NodeDaemon_Client_App::parse_args (int argc, char * argv [])
{
  // Initialize the CORBA ORB
  this->orb_ = ::CORBA::ORB_init (argc, argv);

  // Parse the remaining command-line arguments.
  const char * optargs = "h";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("reset");
  get_opt.long_option ("set-active-env", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("get-active-env");

  get_opt.long_option ("help", 'h');

  char ch;

  while (EOF != (ch = get_opt ()))
  {
    switch (ch)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
      {
        this->print_help ();
      }
      else if (0 == ACE_OS::strcmp ("reset", get_opt.long_option ()))
      {
        this->reset_env_ = true;
      }
      else if (0 == ACE_OS::strcmp ("set-active-env", get_opt.long_option ()))
      {
        this->set_active_env_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("get-active-env", get_opt.long_option ()))
      {
        this->get_active_env_ = true;
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
void CUTS_NodeDaemon_Client_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (1);
}
