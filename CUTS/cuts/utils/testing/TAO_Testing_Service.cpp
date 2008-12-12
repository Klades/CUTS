// $Id$

#include "TAO_Testing_Service.h"

#if !defined (__CUTS_INLINE__)
#include "TAO_Testing_Service.inl"
#endif

#include "ace/ARGV.h"
#include "ace/Argv_Type_Converter.h"

//
// init
//
int CUTS_TAO_Testing_Service::init (int argc, char * argv [])
{
  // Construct a new argument list, making sure required arguments
  // appear in the command-line.
  ACE_ARGV_T <char> args_list;
  args_list.add (argv);
  args_list.add ("-ORBGestalt CURRENT");

  // Copy command line parameter not to corrupt the original.
  argc = args_list.argc ();
  ACE_Argv_Type_Converter command_line (argc, args_list.argv ());

  this->orb_ = ::CORBA::ORB_init (command_line.get_argc (),
                                  command_line.get_ASCII_argv (),
                                  command_line.get_ASCII_argv ()[0]);

  return 0;
}
