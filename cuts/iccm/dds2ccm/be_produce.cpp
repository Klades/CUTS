// $Id$

#include "global_extern.h"
#include "be_extern.h"
#include "fe_extern.h"
#include "ast_root.h"

#include "dds2ccm_impl.h"
#include "Includes_Visitor.h"

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
              ACE_TEXT ("%T (%t) - %M - fatal error; aborting...\n")));

  throw Bailout ();
}

//
// BE_produce
//
void BE_produce (void)
{
  try
  {
    // Open the target output file for writing.
    std::ofstream idl_file (be_global->get_target_filename ().c_str ());

    if (!idl_file.is_open ())
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                  be_global->get_target_filename ().c_str ()));

      BE_abort ();
    }

    ACE_CString file_guard = "_" + be_global->get_target_basename () + "_";
    std::transform (file_guard.begin (),
                    file_guard.end (),
                    file_guard.begin (),
                    &::toupper);

    file_guard = BE_GlobalData::normalize (file_guard);

    idl_file
      << "// -*- IDL -*-" << std::endl
      << std::endl
      << "#ifndef " << file_guard << std::endl
      << "#define " << file_guard << std::endl
      << std::endl;

    // Visit all the elements in the file.
    AST_Root * ast_root = idl_global->root ();

    Includes_Visitor includes (idl_file);
    ast_root->ast_accept (&includes);

    dds2ccm_impl dds2ccm_file (idl_file);
    ast_root->ast_accept (&dds2ccm_file);

    // Close the file.
    idl_file << "#endif  // !defined " << file_guard << std::endl;
    idl_file.close ();

    BE_cleanup ();
  }
  catch (...)
  {
    BE_abort ();
  }
}
