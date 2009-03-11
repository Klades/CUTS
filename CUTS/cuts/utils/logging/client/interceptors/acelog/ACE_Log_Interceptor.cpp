// $Id$

#include "ACE_Log_Interceptor.h"
#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

static const char * __HELP__ =
"ACE logging interceptor for CUTS\n"
"\n"
"USAGE: CUTS_ACE_Log_Interceptor [OPTIONS]\n"
"\n"
"General Options:\n"
"  -p, --connect-port=PORT            set the port for connection\n"
"  -l, --connect-location=LOCATION    set the location to search for connection\n"
"  -n, --connect-name=NAME            set the name to serch for connection\n"
"  -h, --help                         print this help message\n";

//
// init
//
int CUTS_ACE_Log_Interceptor::init (int argc, ACE_TCHAR *argv[])
{
  // Parse command line parameters and set up
  // connect parameters for message back-end

  if (this->parse_args (argc, argv) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                      "%T (%t) - %M - invalid command line arguments passed."),
                      -1);

  // get the Log_MSg singleton instance
  alm_ = ACE_Log_Msg::instance ();

  // Set the new message_backend
  ACE_Log_Msg_Backend * backend = alm_->msg_backend (&this->msg_backend_);

  // Set the custom flag for msg_backend logging
  u_long flags = alm_->flags ();
  flags |= ACE_Log_Msg::CUSTOM;

  // Intialize ACE_Logger for backend
  if (-1 == alm_->open (ACE_TEXT ("CUTS_ACE_Log_Interceptor"), flags))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "%T (%t) - %M -failed to open ACE_Log_Msg_Backend."),
                        -1);
    }

  // Save the previous backend
  this->msg_backend_.old_msg_backend (backend);

  return 0;
}

int CUTS_ACE_Log_Interceptor::parse_args (int argc, char * argv [])
{
  char option;

  // Options are :  -p/--port port
  //                -n/--test-manager-name for connect using name
  //                -l/--test-manager-location for connect using location
  //                -h/--help

  static const ACE_TCHAR options[]= ACE_TEXT ("n:l:p:h");

  ACE_Get_Opt cmd_opts(argc,argv,options,0);

  cmd_opts.long_option ("connect-name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  cmd_opts.long_option ("connect-location", 'l', ACE_Get_Opt::ARG_REQUIRED);
  cmd_opts.long_option ("connect-port", 'p', ACE_Get_Opt::ARG_REQUIRED);
  cmd_opts.long_option ("help", 'h');

  while ((option = cmd_opts ()) != EOF)
  {
    switch (option)
    {
      case 0:
        if (ACE_OS::strcmp ("help", cmd_opts.long_option ()) == 0)
          this->print_help ();

        else if (ACE_OS::strcmp ("connect-port", cmd_opts.long_option ()) == 0)
           this->msg_backend_.connect_port (ACE_OS::atoi (cmd_opts.opt_arg ()));

        else if (ACE_OS::strcmp ("connect-name", cmd_opts.long_option ()) == 0)
        {
          this->msg_backend_.is_connect_name (true);
          this->msg_backend_.connect_string ((ACE_CString)cmd_opts.opt_arg ());
        }
        else if (ACE_OS::strcmp ("connect-location", cmd_opts.long_option ()) == 0)
        {
          this->msg_backend_.is_connect_name (false);
          this->msg_backend_.connect_string ((ACE_CString)cmd_opts.opt_arg ());
        }
        break;

      case 'h':
        this->print_help ();

      case 'p':
        this->msg_backend_.connect_port (ACE_OS::atoi (cmd_opts.opt_arg ()));
        break;

      case 'n':
        this->msg_backend_.is_connect_name (true);
        this->msg_backend_.connect_string ((ACE_CString)cmd_opts.opt_arg ());
        break;

      case 'l':
        this->msg_backend_.is_connect_name (false);
        this->msg_backend_.connect_string ((ACE_CString)cmd_opts.opt_arg ());
        break;

      case ':':
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("-%c requires an argument.\n"),
                           cmd_opts.opt_opt ()), -1);
        break;

      case '?':
        ACE_ERROR ((LM_WARNING,
                    "-%c is an unknown option; ignoring\n",
                    cmd_opts.opt_opt ()));
        break;

      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("parse error.\n")),
                           -1);
    }
  }

  return 0;
}

//
// print_help
//
int CUTS_ACE_Log_Interceptor::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  return 1;
}

//
// fini
//
int CUTS_ACE_Log_Interceptor::fini (void)
{
  ACE_LOG_MSG->msg_backend (this->msg_backend_.old_msg_backend ());
  return 0;
}


//
// info
//
int CUTS_ACE_Log_Interceptor::info (ACE_TCHAR **str, size_t len) const
{
  return 0;
}

/*int Logger_Interceptor::suspend()
{
}
int Logger_Interceptor::resume()
{
}*/


