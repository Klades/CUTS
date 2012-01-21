// $Id$

#include "Executor_IDL_File.h"
#include "Executor_IDL_File_Visitor.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_root.h"

#include <fstream>

//
// Executor_IDL_File
//
Executor_IDL_File::Executor_IDL_File (void)
{

}

//
// ~Executor_IDL_File
//
Executor_IDL_File::~Executor_IDL_File (void)
{

}

//
// visit_root
//
int Executor_IDL_File::visit_root (AST_Root *node)
{
  // Open the idl file for writing.
  std::ofstream idl_file (be_global->get_target_executor_idl_filename ().c_str ());

  if (!idl_file.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       be_global->get_target_executor_idl_filename ().c_str ()),
                       -1);

  // Write the preamble for the idl file.
  ACE_CString file_guard;
  BE_GlobalData::get_filename (be_global->get_target_executor_idl_filename (), file_guard);
  BE_GlobalData::normalize (file_guard, file_guard);

  file_guard = "_" + file_guard + "_";

  std::transform (file_guard.begin (),
                  file_guard.end (),
                  file_guard.begin (),
                  &::toupper);

  idl_file
    << "// -*- IDL -*-" << std::endl
    << std::endl
    << "#ifndef " << file_guard << std::endl
    << "#define " << file_guard << std::endl
    << std::endl
    << "#include \"" << be_global->get_source_basename () << "E.idl\"" << std::endl
    << std::endl;

  Executor_IDL_File_Visitor eifv (idl_file);
  node->ast_accept (&eifv);

  // Close the file from writing.
  idl_file << "#endif  // !defined " << file_guard << std::endl;
  idl_file.close ();

  return 0;
}
