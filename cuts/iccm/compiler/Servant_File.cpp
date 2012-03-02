// $Id$

#include "Servant_File.h"

#include "be_extern.h"
#include "be_global.h"
#include "ast_root.h"
#include "ast_component.h"

#include "Servant_Context.h"
#include "Servant_Impl.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include <iomanip>

struct include_t
{
  include_t (const ACE_CString & include)
    : value_ (include)
  {

  }

  const ACE_CString & value_;
};

static ostream & operator << (ostream & out, const include_t & i)
{
  out << "#include \"" << i.value_ << "\"" << std::endl;
  return out;
}

namespace iCCM
{
/**
 * @class Include_Event_Stub_Header_File
 */
class Include_Event_Stub_Header_File : public Scope_Visitor
{
public:
  //
  // Include_Event_Stub_Header_File
  //
  Include_Event_Stub_Header_File (std::ofstream & hfile)
    : hfile_ (hfile)
  {

  }

  //
  // ~Include_Event_Stub_Header_File
  //
  virtual ~Include_Event_Stub_Header_File (void)
  {

  }

  //
  // visit_module
  //
  virtual int visit_module (AST_Module * node)
  {
    return this->visit_scope (node);
  }

  //
  // visit_component
  //
  virtual int visit_component (AST_Component * node)
  {
    return this->visit_scope (node);
  }

  //
  // visit_eventtype
  //
  virtual int visit_eventtype (AST_EventType * node)
  {
    if (0 == this->includes_.find (node->file_name ()))
      return 0;

    ACE_CString filename;
    be_global->get_filename (node->file_name (), filename);

    ACE_CString basename;
    be_global->get_basename (filename, basename);

    /// @todo This needs to use information from the BE_GlobalData to
    /// ensure the source code is portable across differnt backends.
    this->hfile_ << include_t (be_global->get_stub_file_prefix () + basename + "C.h");
    this->includes_.insert (node->file_name ());

    return 0;
  }

private:
  std::ofstream & hfile_;
  ACE_Unbounded_Set <ACE_CString> includes_;
};

//
// Servant_File
//
Servant_File::Servant_File (void)
{

}

//
// ~Servant_File
//
Servant_File::~Servant_File (void)
{

}

//
// visit_root
//
int Servant_File::visit_root (AST_Root * node)
{
  // Open the header and source file for writing.
  this->hfile_.open (be_global->get_svnt_header_filename ().c_str ());
  this->sfile_.open (be_global->get_svnt_source_filename ().c_str ());

  if (!this->hfile_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       be_global->get_svnt_header_filename ().c_str ()),
                       -1);

  if (!this->sfile_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       be_global->get_svnt_source_filename ().c_str ()),
                       -1);

  // Write the preamble for the idl file.
  ACE_CString file_guard;
  BE_GlobalData::get_filename (be_global->get_svnt_header_filename (), file_guard);
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
    << include_t (be_global->get_source_basename () + "_iCCMC.h")
    << include_t (be_global->get_source_basename () + "S.h")
    << std::endl;

  //======================================================================
  // TODO THIS CODE HERE SHOULD BE CUSTOMIZED FOR EACH IMPLEMENTATION OF
  // AN ICCM BACKEND.

  this->hfile_
    << include_t (be_global->get_source_basename () + "C.h");

  Include_Event_Stub_Header_File event_stub_header (this->hfile_);
  event_stub_header.visit_scope (node);

  this->hfile_
    << std::endl
    << include_t (be_global->get_context_template_header_filename ())
    << include_t (be_global->get_servant_template_header_filename ())
    << std::endl;

  //======================================================================

  this->sfile_
    << "// $" << "Id" << "$" << std::endl
    << std::endl
    << include_t (be_global->get_svnt_header_filename ())
    << std::endl;

  if (!be_global->svnt_export_macro_filename_.empty ())
  {
    this->hfile_
      << include_t (be_global->svnt_export_macro_filename_)
      << std::endl;
  }

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
int Servant_File::visit_module (AST_Module * node)
{
  this->hfile_ << "module" << "{";
  this->sfile_ << "module" << "{";

  if (0 != this->visit_scope (node))
    return -1;

  this->hfile_ << "}";
  this->sfile_ << "}";

  return 0;
}

//
// visit_component
//
int Servant_File::visit_component (AST_Component * node)
{
  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);
  Indentation::Implanter <Indentation::Cxx, char> s_implanter (this->sfile_);

  // Generate the servant's context.
  Servant_Context sc (this->hfile_, this->sfile_);
  node->ast_accept (&sc);

  // Generate the servant's implementation.
  Servant_Impl si (this->hfile_, this->sfile_);
  node->ast_accept (&si);

  return 0;
}

}
