// $Id$

#include "ACE_Log_Interceptor.h"
#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

static const char * __HELP__ =
"General Options:\n"
"  --client=LOCATION            location of the logging client\n"
"  --disable-backend            do not install backend interceptor\n"
"\n"
"Output Options:\n"
"  -h, --help                   print this help message\n";

//
// init
//
int CUTS_ACE_Log_Interceptor::init (int argc, ACE_TCHAR *argv [])
{
  if (-1 == this->parse_args (argc, argv))
    ACE_ERROR_RETURN ((LM_ERROR,
                      "%T (%t) - %M - invalid command line arguments passed."),
                      -1);

  // Install the log message backend.
  ACE_Log_Msg * alm = ACE_Log_Msg::instance ();
  ACE_Log_Msg_Backend * backend = alm->msg_backend (&this->msg_backend_);

  // Set the custom flag for msg_backend logging
  u_long flags = alm->flags ();
  flags |= ACE_Log_Msg::CUSTOM;

  if (-1 == alm->open (ACE_TEXT ("CUTS_ACE_Log_Interceptor"),
                       flags,
                       this->client_.c_str ()))
  {
    // Restore the old backend.
    alm->msg_backend (backend);

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

  static const ACE_TCHAR options[]= ACE_TEXT ("");

  ACE_Get_Opt get_opt (argc, argv, options, 0);

  get_opt.long_option ("client", ACE_Get_Opt::ARG_REQUIRED);

  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
      case 0:
        if (0 == ACE_OS::strcmp ("client", get_opt.long_option ()))
        {
          this->client_ = get_opt.opt_arg ();
        }
        break;

      case ':':
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("-%c requires an argument\n"),
                           get_opt.opt_opt ()),
                           -1);
        break;

      case '?':
        ACE_ERROR ((LM_WARNING,
                    "-%c is an unknown option; ignoring\n",
                    get_opt.opt_opt ()));
        break;

      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - parse error\n")),
                           -1);
    }
  }

  return 0;
}

//
// fini
//
int CUTS_ACE_Log_Interceptor::fini (void)
{
  ACE_Log_Msg_Backend * backend = this->msg_backend_.old_msg_backend ();
  ACE_LOG_MSG->msg_backend (backend);

  return 0;
}

//
// info
//
int CUTS_ACE_Log_Interceptor::info (ACE_TCHAR **str, size_t len) const
{
  return 0;
}

