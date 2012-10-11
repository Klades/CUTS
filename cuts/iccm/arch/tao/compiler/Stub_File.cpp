// $Id$

#include "Stub_File.h"
#include "Servant_Context.h"
#include "Servant_Impl.h"

#include "Event_Traits.h"

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
    << include_t ("cuts/iccm/arch/tao/servant/TAO_Event.h")
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

  if (0 != this->visit_scope (node))
    return -1;

  this->hfile_ << "}" << std::endl;
  this->sfile_ << "}" << std::endl;

  return 0;
}

//
// visit_eventtype
//
int Stub_File::visit_eventtype (AST_EventType * node)
{
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  Indentation::Implanter <Indentation::Cxx, char> s_implanter (this->sfile_);

  // Define class
  this->hfile_
    << "class ";

  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << "TAO_" << node->local_name ()->get_string () << " :" << std::endl
    << "  public virtual ::iCCM::TAO_Event," << std::endl
    << "  public virtual ::OBV_" << node->local_name ()->get_string () << "," << std::endl
    << "  public virtual ::CORBA::DefaultValueRefCountBase" << std::endl
    << "{"
    << "public:" << std::endl;

  // Generate methods
  this->gen_default_ctor (node);
  this->gen_dtor (node);

  this->hfile_ << "};";

  return 0;
}

//
// gen_default_ctor
//
void Stub_File::gen_default_ctor (AST_EventType * node)
{
  this->hfile_
    << "  // Default ctor" << std::endl
    << "  TAO_" << node->local_name ()->get_string () << " (void);"
    << std::endl;

  this->sfile_
    << "//" << std::endl
    << "// " << "TAO_" << node->local_name ()->get_string () << std::endl
    << "//" << std::endl
    << "TAO_" << node->local_name ()->get_string ()
    << "::" << "TAO_" << node->local_name ()->get_string () << " (void)"
    << "{"
    << "}";
}

//
// gen_dtor
//
void Stub_File::gen_dtor (AST_EventType * node)
{
  this->hfile_
    << "  // Dtor" << std::endl
    << "  virtual ~TAO_" << node->local_name ()->get_string () << " (void);"
    << std::endl;

  this->sfile_
    << "//" << std::endl
    << "// ~TAO_" << node->local_name ()->get_string () << std::endl
    << "//" << std::endl
    << "TAO_" << node->local_name ()->get_string ()
    << "::~TAO_" << node->local_name ()->get_string () << " (void)"
    << "{"
    << "}";
}


}
