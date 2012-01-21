// $Id$

#include "global_extern.h"
#include "be_extern.h"
#include "fe_extern.h"
#include "ast_root.h"

#include "Executor_IDL_File.h"
#include "Servant_File.h"
#include "Stub_File.h"

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

    // Generate the stub files.
    iCCM::Stub_File stub_file;
    root->ast_accept (&stub_file);

    // Generate the executor idl file.
    Executor_IDL_File executor_idl_file;
    root->ast_accept (&executor_idl_file);

    // Generate the servant files.
    iCCM::Servant_File svnt_file;
    root->ast_accept (&svnt_file);

    BE_cleanup ();
  }
  catch (...)
  {
    BE_abort ();
  }
}
