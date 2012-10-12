// $Id$

#include "Stub_File.h"
#include "Servant_Context.h"
#include "Servant_Impl.h"
#include "Event_Traits.h"

#include "be_extern.h"
#include "be_global.h"
#include "ast_root.h"
#include "ast_field.h"
#include "ast_component.h"
#include "ast_eventtype.h"
#include "ast_structure.h"
#include "utl_identifier.h"
#include "ast_enum.h"
#include "ast_enum_val.h"

#include "boost/bind.hpp"
#include "ace/Hash_Map_Manager.h"
#include "ace/Thread_Mutex.h"

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

class Operator_Targets : public iCCM::Scope_Visitor
{
public:
  // Typedefs of output variables
  typedef ACE_Unbounded_Set <AST_Decl *> Target_Manager;

  Operator_Targets (Target_Manager & target_mgr)
    : target_mgr_ (target_mgr)
  {

  }

  virtual int visit_root (AST_Root * node)
  {
    AST_Decl * parent = this->parent_;
    this->parent_ = node;

    if (this->visit_scope (node))
      return -1;

    this->parent_ = parent;
    return 0;
  }

  virtual int visit_module (AST_Module * node)
  {
    AST_Decl * parent = this->parent_;
    this->parent_ = node;

    if (this->visit_scope (node))
      return -1;

    this->parent_ = parent;
    return 0;
  }

  virtual int visit_eventtype (AST_EventType * node)
  {
    if (0 != this->target_mgr_.find (node))
      this->target_mgr_.insert (node);
    return this->visit_scope (node);
  }

  int handle_struct (AST_Structure * node)
  {
    // We don't want to visit all structs in the IDL, only
    // those contained by an event.  Therefore, visit_structure
    // is not overloaded.
    this->target_mgr_.insert (node);
    return this->visit_scope (node);
  }

  AST_Decl * lookup (AST_Field * node)
  {
      // Search the parent module/root for the struct
      UTL_ScopedName * sn = dynamic_cast <UTL_ScopedName *> (this->parent_->name ()->copy ());
      UTL_ScopedName * name = 0;
      ACE_NEW_RETURN (name, UTL_ScopedName (node->field_type ()->local_name (), 0), 0);
      sn->nconc (name);

      return node->defined_in ()->lookup_by_name (sn, true, false);
  }

  virtual int visit_field (AST_Field * node)
  {
    AST_Type * field_type = node->field_type ();
    const char * full_name = field_type->full_name ();

    switch (field_type->node_type ())
    {
    case AST_Decl::NT_struct:
    {
      AST_Decl * decl = this->lookup (node);
      if (decl == 0)
        return -1;

      // Skip node type if it has been identified already
      if (0 == this->target_mgr_.find (decl))
        return 0;

      // Recursively look at structs since they can contain complex members
      AST_Structure * unique = dynamic_cast <AST_Structure *> (decl);
      if (!unique)
        return -1;

      if (!this->handle_struct (unique))
        return -1;
      break;
    }

    case AST_Decl::NT_enum:
    {
      AST_Decl * decl = this->lookup (node);
      if (decl == 0)
        return -1;

      // Skip node type if it has been identified already
      if (0 == this->target_mgr_.find (decl))
        return 0;

      this->target_mgr_.insert (decl);
      break;
    }

    default:
      return 0;
    }

    return 0;
  }

private:
  AST_Decl * parent_;
  Target_Manager & target_mgr_;
};

class Output_Operator : public iCCM::Scope_Visitor
{
public:
  Output_Operator (std::ofstream & hfile, std::ofstream & sfile)
    : hfile_ (hfile),
      sfile_ (sfile)
  {

  }

  void write_decl_preamble (AST_Decl * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    if (!be_global->stub_export_macro_.empty ())
      this->hfile_ << be_global->stub_export_macro_ << " ";

    this->hfile_
      << "ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR &, const ::" << local_name  << " &);"
      << std::endl;

    this->sfile_
      << "//" << std::endl
      << "// " << "Output stream operator for ::" << local_name << std::endl
      << "//" << std::endl
      << "ACE_CDR::Boolean operator << "
      << "(CUTS_TCPIP_OutputCDR & stream, const ::" << local_name << " & ev)" << std::endl
      << "{" << std::endl;
  }

  void write_decl_postamble (AST_Decl * node)
  {
    this->sfile_
      << "  return stream.good_bit ();" << std::endl
      << "}" << std::endl << std::endl;
  }

  virtual int visit_eventtype (AST_EventType * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);
    this->visit_scope (node);
    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_structure (AST_Structure * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);
    this->visit_scope (node);
    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_enum (AST_Enum * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);

    const char * local_name = node->local_name ()->get_string ();
    this->sfile_
      << "  stream << static_cast < ::ACE_CDR::ULong > (ev);" << std::endl;

    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_field (AST_Field * node)
  {
    AST_Type * field_type = node->field_type ();
    const char * local_name = node->local_name ()->get_string ();
    const char * param_type = field_type->full_name ();
    ACE_CString accessor_suffix;

    // Identify accessor suffix
    switch (this->parent_->node_type ())
    {
      case AST_Decl::NT_eventtype:
        accessor_suffix = " ()";
        break;
      default:
        accessor_suffix = "";
        break;
    }

    // Put the value on the stream
    this->sfile_
      << "  stream << ev." << local_name << accessor_suffix.c_str () << ";" << std::endl;

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString accessor_suffix_;
  AST_Decl * parent_;
};

class Input_Operator : public iCCM::Scope_Visitor
{
public:
  Input_Operator (std::ofstream & hfile, std::ofstream & sfile)
    : hfile_ (hfile),
      sfile_ (sfile),
      var_counter_ (300000000)
  {

  }

  void write_decl_preamble (AST_Decl * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    if (!be_global->stub_export_macro_.empty ())
      this->hfile_ << be_global->stub_export_macro_ << " ";

    this->hfile_
      << "ACE_CDR::Boolean operator >> (ACE_InputCDR &, ::" << local_name  << " &);"
      << std::endl;

    this->sfile_
      << "//" << std::endl
      << "// " << "Input stream operator for ::" << local_name << std::endl
      << "//" << std::endl
      << "ACE_CDR::Boolean operator >> "
      << "(ACE_InputCDR & stream, ::" << local_name << " & ev)" << std::endl
      << "{" << std::endl;
  }

  void write_decl_postamble (AST_Decl * node)
  {
    this->sfile_
      << "  return stream.good_bit ();" << std::endl
      << "}" << std::endl << std::endl;
  }

  virtual int visit_eventtype (AST_EventType * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);
    this->visit_scope (node);
    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_structure (AST_Structure * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);
    this->visit_scope (node);
    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_enum (AST_Enum * node)
  {
    this->parent_ = node;
    this->write_decl_preamble (node);

    const char * local_name = node->local_name ()->get_string ();
    this->sfile_
      << "  ACE_CDR::ULong temp = 0;" << std::endl
      << "  stream >> temp;" << std::endl
      << "  ev = static_cast < ::" << local_name << " > (temp);" << std::endl;

    this->write_decl_postamble (node);
    return 0;
  }

  virtual int visit_predefined_type (AST_PredefinedType * node)
  {
    const char * local_name = this->predefined_field_->local_name ()->get_string ();
    const char * param_type = node->full_name ();
    std::stringstream target;
    std::stringstream var_name;

    // If node is not an object then we need to allocate the type to read into
    if (node->pt () != AST_PredefinedType::PT_object)
    {
      std::stringstream target;
      var_name << "_var_" << this->var_counter_;
      this->var_counter_++;

      this->sfile_
        << "  " << param_type << " " << var_name.str () << ";" << std::endl;
    }

    switch (node->pt ())
    {
      case AST_PredefinedType::PT_boolean:
        target << "::ACE_InputCDR::to_boolean (" << var_name.str () << ")";
        break;

      case AST_PredefinedType::PT_char:
        target << "::ACE_InputCDR::to_char (" << var_name.str () << ")";
        break;

      case AST_PredefinedType::PT_wchar:
        target << "::ACE_InputCDR::to_wchar (" << var_name.str () << ")";
        break;

      case AST_PredefinedType::PT_octet:
        target << "::ACE_InputCDR::to_octet (" << var_name.str () << ")";
        break;

      case AST_PredefinedType::PT_object:
        target << "ev." << local_name;
        if (this->parent_->node_type () == AST_Decl::NT_eventtype)
          target << " ()";
        break;

      default:
        target << var_name.str ();
    }

    // Read from the stream to the target
    this->sfile_
      << "  stream >> " << target.str () << ";" << std::endl;

    // If target was allocated previously, assign it.
    if (node->pt () != AST_PredefinedType::PT_object)
    {
      this->sfile_ << "  ev." << local_name;

      if (this->parent_->node_type () == AST_Decl::NT_eventtype)
        this->sfile_ << " (" << var_name.str () << ");" << std::endl << std::endl;
      else
        this->sfile_ << " = " << var_name.str () << ";" << std::endl << std::endl;
    }

    return 0;
  }


  virtual int visit_field (AST_Field * node)
  {
    AST_Type * field_type = node->field_type ();
    const char * local_name = node->local_name ()->get_string ();
    const char * param_type = field_type->full_name ();
    std::stringstream target;
    ACE_CString assign_suffix = "";

    // If the field is returned by reference from TAO
    // then read the stream directly into it
    switch (field_type->node_type ())
    {
      case AST_Decl::NT_struct:
        this->sfile_
          << "  stream >> ev." << local_name;
        if (this->parent_->node_type () == AST_Decl::NT_eventtype)
          this->sfile_ << " ()";
        this->sfile_ << ";" << std::endl;
        return 0;
        break;

      case AST_Decl::NT_sequence:
        this->sfile_
          << "  ev." << local_name;
        if (this->parent_->node_type () == AST_Decl::NT_eventtype)
          this->sfile_ << " ()";
        this->sfile_ << ";" << std::endl;
        return 0;
        break;

      case AST_Decl::NT_union:
        this->sfile_
          << "  ev." << local_name;
        if (this->parent_->node_type () == AST_Decl::NT_eventtype)
          this->sfile_ << " ()";
        this->sfile_ << ";" << std::endl;
        return 0;
        break;

      case AST_Decl::NT_pre_defined:
        // Visit the pre_defined type for extra processing
        this->predefined_field_ = node;
        field_type->ast_accept (this);
        return 0;
        break;
    }
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString accessor_suffix_;
  AST_Decl * parent_;
  AST_Decl * predefined_field_;
  size_t var_counter_;
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
  // Gather all unique events and their complex member types
  Operator_Targets::Target_Manager targets;
  Operator_Targets ot (targets);
  node->ast_accept (&ot);

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

  Indentation::Implanter <Indentation::Cxx, char> h_implanter (this->hfile_);

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
    << include_t ("cuts/iccm/arch/tcpip/servant/TCPIP_Event.h")
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

  // Generate Output Operators
  this->hfile_
    << "//" << std::endl
    << "// Output Operators" << std::endl
    << "//" << std::endl;
  Output_Operator output (this->hfile_, this->sfile_);
  std::for_each (targets.begin (),
                 targets.end (),
                 boost::bind (&AST_Decl::ast_accept,
                              _1,
                              &output));

  // Generate Input Operators
  this->hfile_
    << "//" << std::endl
    << "// Input Operators" << std::endl
    << "//" << std::endl;
  Input_Operator input (this->hfile_, this->sfile_);
  std::for_each (targets.begin (),
                 targets.end (),
                 boost::bind (&AST_Decl::ast_accept,
                              _1,
                              &input));

  // Write the event traits to the header/source files.
  Event_Traits event_traits (this->hfile_, this->sfile_);
  node->ast_accept (&event_traits);

  // Close the file from writing.
  this->hfile_ << "#endif  // !defined " << file_guard << std::endl;

  this->hfile_.close ();
  this->sfile_.close ();

  return 0;
}

}
