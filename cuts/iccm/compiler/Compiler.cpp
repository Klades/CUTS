// $Id$

#include "be_extern.h"
#include "fe_extern.h"

#include "global_extern.h"
#include "ast_root.h"

#include "tao/Version.h"

#include "Executor_IDL_File.h"
#include "Servant_File.h"

#include <iostream>

//
// BE_version
//
void BE_version (void)
{
  std::cerr << "iCCM compiler, version " << std::endl;
}

//
// BE_post_init
//
void BE_post_init (char * files [], long nfiles)
{
  // We do not support processing multiple files.
  idl_global->multi_file_input (false);

  // Set the source file, which will always be the first file
  // in our case.
  be_global->source_file_ = files[0];
}

//
// BE_cleanup
//
void BE_cleanup (void)
{
  idl_global->destroy ();
}

//
// BE_abort
//
void BE_abort (void)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("fatal error; aborting...")));

  throw Bailout ();
}

//
// BE_produce
//
void BE_produce (void)
{
  try
  {
    AST_Root * root = idl_global->root ();

    if (be_global->generate_lem_)
    {
      // Generate the executor idl file.
      iCCM::Executor_IDL_File executor_idl_file;
      root->ast_accept (&executor_idl_file);
    }

    if (be_global->generate_svnt_)
    {
      // Generate the servant files.
      iCCM::Servant_File svnt_file;
      root->ast_accept (&svnt_file);
    }

    be_global->post_produce ();

    // Clean up the backend.
    BE_cleanup ();
  }
  catch (...)
  {
    BE_abort ();
  }
}
