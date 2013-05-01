// $Id:

#include "Stub_File.h"

#include "Event_ObjectClass.h"
#include "Event_ObjectClass_Factory.h"
#include "Event_Traits.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include "be_extern.h"
#include "be_global.h"
#include "ast_root.h"
#include "ast_component.h"
#include "ast_eventtype.h"
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
    << include_t ("cuts/iccm/arch/portico/servant/Portico_AttributeHandle.h")
    << include_t ("cuts/iccm/arch/portico/servant/Portico_ObjectClass.h")
    << include_t ("cuts/iccm/arch/portico/servant/Portico_ObjectClass_Factory.h")
    << include_t ("RTI.hh")
    << include_t ("vector")
    << include_t (be_global->get_source_basename () + "C.h")
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

  // Write the event traits to the header/source files.
  Event_Traits event_traits (this->hfile_, this->sfile_);
  node->ast_accept (&event_traits);

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
  this->hfile_
    << "namespace " << node->local_name ()->get_string () << std::endl
    << "{" << std::endl;

  this->sfile_
    << "namespace " << node->local_name ()->get_string () << std::endl
    << "{" << std::endl;

  // Generate code for events inside of modules
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  Indentation::Implanter <Indentation::Cxx, char> s_implanter (this->sfile_);

  Event_ObjectClass objectclass (this->hfile_, this->sfile_);
  node->ast_accept (&objectclass);

  Event_ObjectClass_Factory objectclass_factory (this->hfile_, this->sfile_);
  node->ast_accept (&objectclass_factory);

  this->hfile_ << "}" << std::endl;
  this->sfile_ << "}" << std::endl;

  return 0;
}

//
// visit_eventtype
//
int Stub_File::visit_eventtype (AST_EventType * node)
{
  if (!be_global->is_wrapper_eventtype (node))
    return 0;

  // Generate code for events outside of modules
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  Indentation::Implanter <Indentation::Cxx, char> s_implanter (this->sfile_);

  Event_ObjectClass objectclass (this->hfile_, this->sfile_);
  node->ast_accept (&objectclass);

  Event_ObjectClass_Factory objectclass_factory (this->hfile_, this->sfile_);
  node->ast_accept (&objectclass_factory);

  return 0;
}

}
