// $Id$

#include "Stub_File.h"
#include "Servant_Context.h"
#include "Servant_Impl.h"

#include "Event_Traits.h"
#include "Upcall_Event.h"
#include "Downcall_Event.h"

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

/**
 * @class List_Dcps_Impl_Includes
 *
 * Visitor that is responsible for listing the include files for
 * a CORBA's corresponding DDS event type.
 */
class List_Dcps_Impl_Includes : public iCCM::Scope_Visitor
{
public:
  //
  // List_Dcps_Impl_Includes
  //
  List_Dcps_Impl_Includes (std::ofstream & hfile)
    : hfile_ (hfile)
  {

  }

  //
  // visit_root
  //
  virtual int visit_root (AST_Root * node)
  {
    AST_Decl * parent = this->parent_;
    this->parent_ = node;

    if (0 != this->visit_scope (node))
      return -1;

    this->parent_ = parent;
    return 0;
  }

  //
  // visit_module
  //
  virtual int visit_module (AST_Module * node)
  {
    AST_Decl * parent = this->parent_;
    this->parent_ = node;

    if (0 != this->visit_scope (node))
      return -1;

    this->parent_ = parent;
    return 0;
  }

  //
  // visit_eventtype
  //
  virtual int visit_eventtype (AST_EventType * node)
  {
    // Get the corresponding DDS event type.
    ACE_CString dds_event;
    if (!be_global->get_wrapper_eventtype (node, dds_event))
      return 0;

    // Search for the type declaration of this DDS event type. It
    // should be an AST_Struct type.
    Identifier * id = 0;
    ACE_NEW_RETURN (id, Identifier (dds_event.c_str ()), -1);

    UTL_ScopedName * sn = dynamic_cast <UTL_ScopedName *> (this->parent_->name ()->copy ());
    UTL_ScopedName * name = 0;
    ACE_NEW_RETURN (name, UTL_ScopedName (id, 0), -1);
    sn->nconc (name);

    AST_Decl * decl = node->defined_in ()->lookup_by_name (sn, true, false);

    if (decl == 0)
      return -1;

    // Get the basename of the source IDL file. This will be used to
    // calculate the Dcps_impl.h include file.
    ACE_CString basename;
    be_global->get_filename (decl->file_name (), basename);
    be_global->get_basename (basename, basename);

    if (0 != this->includes_.find (basename))
    {
      this->hfile_ << include_t (basename + "Dcps_impl.h");
      this->includes_.insert (basename);
    }

    // Destroy the scoped name.
    sn->destroy ();
    return 0;
  }

private:
  /// Target output stream for generation.
  std::ofstream & hfile_;

  /// Parent declaration.
  AST_Decl * parent_;

  /// Let of files that have already been included.
  ACE_Unbounded_Set <ACE_CString> includes_;
};

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
    << include_t ("cuts/iccm/arch/dds/servant/DDS_Traits_T.h")
    << std::endl;

  // List the include files for the DDS event types.
  List_Dcps_Impl_Includes list_includes (this->hfile_);
  node->ast_accept (&list_includes);
  this->hfile_ << std::endl;

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

  Upcall_Event upcall_event (this->hfile_, this->sfile_);
  node->ast_accept (&upcall_event);

  Downcall_Event downcall_event (this->hfile_, this->sfile_);
  node->ast_accept (&downcall_event);


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

  Upcall_Event upcall_event (this->hfile_, this->sfile_);
  node->ast_accept (&upcall_event);

  Downcall_Event downcall_event (this->hfile_, this->sfile_);
  node->ast_accept (&downcall_event);

  return 0;
}
}
