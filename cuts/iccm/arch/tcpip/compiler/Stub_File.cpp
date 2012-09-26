// $Id$

#include "Stub_File.h"
#include "Servant_Context.h"
#include "Servant_Impl.h"

#include "be_extern.h"
#include "be_global.h"
#include "ast_root.h"
#include "ast_component.h"
#include "ast_eventtype.h"
#include "utl_identifier.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include <iomanip>
#include <iostream>

#include "ace/Unbounded_Set.h"

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
// Stub_File
//
Stub_File::Stub_File (void)
{

}

//
// ~Stub_File
//
Stub_File::~Stub_File (void)
{

}

//
// visit_root
//
int Stub_File::visit_root (AST_Root * node)
{
  // Open the header and source file for writing.
  this->hfile_.open (be_global->get_stub_header_filename ().c_str ());
  this->sfile_.open (be_global->get_stub_source_filename ().c_str ());

  if (!this->hfile_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       be_global->get_stub_header_filename ().c_str ()),
                       -1);

  if (!this->sfile_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       be_global->get_stub_source_filename ().c_str ()),
                       -1);

  // Write the preamble for the idl file.
  ACE_CString file_guard;
  BE_GlobalData::get_filename (be_global->get_stub_header_filename (), file_guard);
  BE_GlobalData::normalize (file_guard, file_guard);

  file_guard = "_" + file_guard + "_";

  std::transform (file_guard.begin (),
                  file_guard.end (),
                  file_guard.begin (),
                  &::toupper);

  this->hfile_
    << "// -*- C++ -*-" << std::endl
    << std::endl
    << "#ifndef " << file_guard << std::endl
    << "#define " << file_guard << std::endl
    << std::endl
    << include_t (be_global->get_source_basename () + "C.h")
    << include_t ("cuts/iccm/arch/tcpip/stub/TCPIP_OutputCDR.h")
    << std::endl;

  if (!be_global->stub_export_macro_filename_.empty ())
  {
    this->hfile_
      << include_t (be_global->stub_export_macro_filename_)
      << std::endl;
  }


  this->sfile_
    << "// $" << "Id" << "$" << std::endl
    << std::endl
    << include_t (be_global->get_stub_header_filename ().c_str ())
    << std::endl;

  this->visit_scope (node);

  // Close the file from writing.
  this->hfile_ << "#endif  // !defined " << file_guard << std::endl;

  this->hfile_.close ();
  this->sfile_.close ();

  return 0;
}

//
// visit_module
//
int Stub_File::visit_module (AST_Module * node)
{
  return this->visit_scope (node);
}

//
// visit_eventtype
//
int Stub_File::visit_eventtype (AST_EventType * node)
{
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  Indentation::Implanter <Indentation::Cxx, char> s_implanter (this->sfile_);

  // Define stream operators
  this->hfile_
    << "//============================================================================" << std::endl
    << "// stream operators for ::" << node->local_name ()->get_string () << std::endl
    << "//============================================================================" << std::endl;

  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  // Generate methods
  this->gen_input_oper (node);
  this->gen_output_oper (node);

  return 0;
}

//
// gen_output_oper
//
void Stub_File::gen_output_oper (AST_EventType * node)
{
  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR &, const ::" << node->local_name ()->get_string ()  << " &);";

  this->sfile_
    << "//" << std::endl
    << "// " << "Output operator for ::" << node->local_name ()->get_string () << std::endl
    << "//" << std::endl
    << "ACE_CDR::Boolean operator << "
    << "(CUTS_TCPIP_OutputCDR & stream, const ::" << node->local_name ()->get_string () << " & ev)"
    << "{"
    << "return stream.good_bit ();"
    << "}";
}

//
// gen_input_oper
//
void Stub_File::gen_input_oper (AST_EventType * node)
{
  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << "ACE_CDR::Boolean operator >> (ACE_InputCDR &, ::" << node->local_name ()->get_string ()  << " &);";

  this->sfile_
    << "//" << std::endl
    << "// " << "Input operator for ::" << node->local_name ()->get_string () << std::endl
    << "//" << std::endl
    << "ACE_CDR::Boolean operator >> "
    << "(ACE_InputCDR & stream, ::" << node->local_name ()->get_string () << " & ev)"
    << "{"
    << "return stream.good_bit ();"
    << "}";
}

}
