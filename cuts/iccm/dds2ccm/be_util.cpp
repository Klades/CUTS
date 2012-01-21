
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
void be_util::prep_be_arg (char *)
{
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

