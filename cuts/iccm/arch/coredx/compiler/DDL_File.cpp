// $Id$

#include "DDL_File.h"

#include "Context.h"

#include "be_extern.h"
#include "be_global.h"
#include "ast_root.h"
#include "utl_identifier.h"

#include <iomanip>
#include <iostream>

/**
 * @struct include_t
 *
 * Functor for writing a string as an include value.
 */
struct include_t
{
  include_t (const ACE_CString & include)
    : value_ (include)
  {

  }

  const ACE_CString & value_;
};

//
// operator <<
//
static ostream & operator << (ostream & out, const include_t & i)
{
  out << "#include \"" << i.value_ << "\"" << std::endl;
  return out;
}

namespace iCCM
{

//
// DDL_File
//
DDL_File::DDL_File (void)
{

}

//
// ~DDL_File
//
DDL_File::~DDL_File (void)
{

}

//
// visit_root
//
int DDL_File::visit_root (AST_Root * node)
{
  iCCM::CoreDX::Context * cdx_context = dynamic_cast <iCCM::CoreDX::Context *> (be_global);

  if (!cdx_context)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to convert Context\n")),
                       -1);

  // Open the ddl file for writing.
  this->ddl_file_.open (cdx_context->get_ddl_filename ().c_str ());

  if (!this->ddl_file_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       cdx_context->get_ddl_filename ().c_str ()),
                       -1);

  // Write the preamble for the idl file.
  ACE_CString file_guard;
  BE_GlobalData::get_filename (cdx_context->get_ddl_filename (), file_guard);
  BE_GlobalData::normalize (file_guard, file_guard);

  file_guard = "_" + file_guard + "_";

  std::transform (file_guard.begin (),
                  file_guard.end (),
                  file_guard.begin (),
                  &::toupper);

  this->ddl_file_
    << "#ifndef " << file_guard << std::endl
    << "#define " << file_guard << std::endl
    << std::endl
    << "module CoreDX" << std::endl
    << "{" << std::endl
    << include_t (be_global->get_source_basename () + ".idl")
    << "};" << std::endl
    << std::endl;

  // Close the file from writing.
  this->ddl_file_ << "#endif  // !defined " << file_guard << std::endl;
  this->ddl_file_.close ();

  return 0;
}

}
