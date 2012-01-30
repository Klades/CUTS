// $Id$

#include "be_util.h"
#include "be_global.h"

#include "ast_generator.h"

//
// prep_be_arg
//
void be_util::prep_be_arg (char * s)
{
  be_global->prep_be_arg (s);
}

//
// arg_post_proc
//
void be_util::arg_post_proc (void)
{
  be_global->arg_post_proc ();
}

//
// usage
//
void be_util::usage (void)
{
  be_global->print_usage ();
}

//
// generator_init
//
AST_Generator * be_util::generator_init (void)
{
  AST_Generator * gen = 0;
  ACE_NEW_RETURN (gen, AST_Generator, 0);

  return gen;
}

