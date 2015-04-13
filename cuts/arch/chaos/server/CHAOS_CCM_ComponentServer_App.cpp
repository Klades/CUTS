// $Id$

#include "CHAOS_CCM_ComponentServer_App.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_CCM_ComponentServer_App.inl"
#endif

#include "CHAOS_CCM_ComponentServer.h"
#include "ace/ARGV.h"
#include "ace/Get_Opt.h"

//
// run_main
//
int CUTS_CHAOS_CCM_ComponentServer_App::
run_main (int argc, char * argv[])
{
  ACE_ARGV_T <char> argv_list (argc, argv);
  this->parse_args (argv_list.argc (), argv_list.argv ());

  return base_type::run_main (argc, argv);
}

//
// parse_args
//
int CUTS_CHAOS_CCM_ComponentServer_App::
parse_args (int argc, char * argv [])
{
  const char * optargs = ACE_TEXT ("h");
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option (ACE_TEXT("help"), 'h');

  int opt;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp (ACE_TEXT ("help"), get_opt.long_option ()))
      {
        this->print_help ();
      }
      break;

    case 'h':
      this->print_help ();
      break;
    };
  }

  return 0;
}

//
// print_help
//
void CUTS_CHAOS_CCM_ComponentServer_App::print_help (void)
{
  ACE_OS::exit (1);
}
