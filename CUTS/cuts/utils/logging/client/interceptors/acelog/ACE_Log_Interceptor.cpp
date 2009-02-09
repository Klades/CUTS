// $Id$

#include "ACE_Log_Interceptor.h"
#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"
#include "ace/Get_Opt.h"

#include <iostream>

static const char * __HELP__ =
"CUTS_ACE_Log_Interceptor for CUTS"
"\n"
"USAGE: CUTS_ACE_Log_Interceptor [OPTIONS]\n"
"\n"
"General Options:\n"
"  -p, --connect-port=PORT    set the port for connection\n"
"  -l, --connect-location=LOCATION    set the location to search for connection\n"
"  -n, --connect-name=NAME    set the name to serch for connection\n"
"  -h, --help                 print this help message\n";

//
// init
//
int CUTS_ACE_Log_Interceptor::init (int argc, ACE_TCHAR *argv[])
{
  // initialize callback_

  CUTS_ACE_Log_Callback * callback = 0;
  
  ACE_NEW_RETURN (callback, CUTS_ACE_Log_Callback (logger_),-1);
  this->callback_.reset (callback);

  // parse command line parameters and set up msg_callback for logger
  if (this->parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR, 
    									"%T (%t) - %M - Invalid command line arguments passed."),
    									-1);
  }
  
  // retval=1 means help option was printed
  if (this->parse_args (argc, argv) == 1)
  {
  	return 0;
  }

  // Make connection to Test-Manager based on parsed arguments
  if (this->make_connection () == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR, 
    									"%T (%t) - %M - Connection to CUTS_Logger failed."),
    									-1);
  }

  ACE_LOG_MSG->set_flags (ACE_Log_Msg::MSG_CALLBACK);

  // Pooja, please cache the previous set callback in ACE_Log. You need
  // to ensure this is restored before this service exits. Also, if the 
  // previous callback is not 0, then you need to invoke it manually,
  // which is called ``chaining''. I am sure that a end-user that
  // installs their own callback will be pretty upset if you replace
  // their callback with your and aren't nice enough to invoke it on
  // their behave when you handle log messages. ;-)
  this->callback_->set_old_callback (ACE_LOG_MSG->msg_callback 
  																		(this->callback_.get()));

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
    std::cerr << "Option= " << option;
    switch (option)
    {
      case 0:
        if (ACE_OS::strcmp ("help", cmd_opts.long_option ()) == 0)
        {
          this->print_help ();
        }
        else if (ACE_OS::strcmp ("connect-port", cmd_opts.long_option ()) == 0)
        {
          this->app_options_.connect_port_ = ACE_OS::atoi (cmd_opts.opt_arg ());
        }
        else if (ACE_OS::strcmp ("connect-name", cmd_opts.long_option ()) == 0)
        {
          this->app_options_.is_connect_name_ = true;
          this->app_options_.connect_string = cmd_opts.opt_arg ();
        }
        else if (ACE_OS::strcmp ("connect-location", cmd_opts.long_option ()) == 0)
        {
          this->app_options_.is_connect_location_ = true;
          this->app_options_.connect_string = cmd_opts.opt_arg ();
        }
        break;

      case 'h':
        this->print_help ();

      case 'p':
        this->app_options_.connect_port_ = ACE_OS::atoi (cmd_opts.opt_arg ());
        break;

      case 'n':
        this->app_options_.is_connect_name_ = true;
        this->app_options_.connect_string = cmd_opts.opt_arg ();
        break;

      case 'l':
        this->app_options_.is_connect_location_ = true;
        this->app_options_.connect_string = cmd_opts.opt_arg ();
        break;

      case ':':
        ACE_ERROR_RETURN ((LM_ERROR,
        									 ACE_TEXT ("Logger_Interceptor::init():")
          								 ACE_TEXT ("-%c requires an argument.\n"),
          								 cmd_opts.opt_opt ()), -1);
        break;

      case '?':
        ACE_ERROR ((LM_WARNING,
          					"Logger_Interceptor::init():"
          					"-%c is an unknown option; ignoring\n",
          					cmd_opts.opt_opt ()));
        break;

      default:
        ACE_ERROR_RETURN ((LM_ERROR,
          								 ACE_TEXT ("Logger_Interceptor::init():"
          								 "Parse Error.\n")),
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
  // Pooja, please make sure to restore the previous callback. Right now,
  // once this service goes away, you reset the callback. That deletes
  // the callback, however, it is still registered with ACE_Log!! This 
  // will cause a segfault.
  ACE_LOG_MSG->clr_flags (ACE_Log_Msg ::MSG_CALLBACK);
	
	// Restore the old callback
	ACE_LOG_MSG->msg_callback (this->callback_->get_old_callback ());
  callback_.reset();

  return 0;
}

//
// make_connection
//
int CUTS_ACE_Log_Interceptor::make_connection ()
{
  this->logger_.configure (this->app_options_.connect_port_);

  if ( this->app_options_.is_connect_name_ )
  {
    this->logger_.connect_using_name (this->app_options_.connect_string);
  }
  else if ( this->app_options_.is_connect_location_ )
  {
    this->logger_.connect_using_location (this->app_options_.connect_string);
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT (
      "Logger_Interceptor: No connect options found\n")), -1);
  }

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


