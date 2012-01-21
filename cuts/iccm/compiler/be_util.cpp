
//=============================================================================
/**
 *  @file    be_util.cpp
 *
 *  $Id$
 *
 *  Static helper methods used by multiple visitors.
 *
 *
 *  @author Jeff Parsons
 */
//=============================================================================

#include "be_util.h"
#include "be_extern.h"

#include "ast_generator.h"

#include <iostream>

//
// prep_be_arg
//
void be_util::prep_be_arg (char * s)
{
  static const char stub_export_macro[] = "stub_export_macro=";
  static const char stub_export_include[] = "stub_export_include=";
  static const char svnt_export_macro[] = "svnt_export_macro=";
  static const char svnt_export_include[] = "svnt_export_include=";

  char* last = 0;

  for (char * arg = ACE_OS::strtok_r (s, ",", &last);
       0 != arg;
       arg = ACE_OS::strtok_r (0, ",", &last))
  {
    if (ACE_OS::strstr (arg, stub_export_macro) == arg)
    {
      char * val = arg + sizeof (stub_export_macro) - 1;
      be_global->stub_export_macro_ = val;
    }
    else if (ACE_OS::strstr (arg, stub_export_include) == arg)
    {
      char * val = arg + sizeof (stub_export_include) - 1;
      be_global->stub_export_macro_filename_ = val;
    }
    else if (ACE_OS::strstr (arg, svnt_export_macro) == arg)
    {
      char * val = arg + sizeof (svnt_export_macro) - 1;
      be_global->svnt_export_macro_ = val;
    }
    else if (ACE_OS::strstr (arg, svnt_export_include) == arg)
    {
      char * val = arg + sizeof (svnt_export_include) - 1;
      be_global->svnt_export_macro_filename_ = val;
    }
  }
}

//
// arg_post_proc
//
void be_util::arg_post_proc (void)
{
}

//
// usage
//
void be_util::usage (void)
{
  // Print the following timestamp since we want to what version
  // and build our clients are using.
  std::cerr
    << std::endl
    << "This executable was created on "
    << __DATE__ << " at " << __TIME__ << std::endl;
}

//
// generator_init
//
AST_Generator * be_util::generator_init (void)
{
  AST_Generator *gen = 0;
  ACE_NEW_RETURN (gen, AST_Generator, 0);

  return gen;
}

