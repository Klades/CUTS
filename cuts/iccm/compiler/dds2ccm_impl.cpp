// $Id$

#include "dds2ccm_impl.h"

#include "ast_decl.h"
#include "ast_field.h"
#include "ast_root.h"
#include "ast_structure.h"

#include "utl_identifier.h"
#include "utl_scope.h"

#include "ace/Log_Msg.h"
#include "ace/OS_NS_stdio.h"

#include "CCF/CodeGenerationKit/IndentationIDL.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include "boost/bind.hpp"
#include <algorithm>

#include "ace/Unbounded_Set.h"

//
// dds2ccm_impl
//
dds2ccm_impl::
dds2ccm_impl (std::ofstream & idl)
: idl_ (idl)
{

}

//
// ~dds2ccm_impl
//
dds2ccm_impl::~dds2ccm_impl (void)
{

}

//
// visit_root
//
int dds2ccm_impl::visit_root (AST_Root *node)
{
  // Open the file for writing.
  Indentation::Implanter <Indentation::IDL, char> implanter (this->idl_);

  for (UTL_ScopeActiveIterator si (node, UTL_Scope::IK_decls);
       !si.is_done (); si.next ())
  {
    AST_Decl * d = si.item ();

    // There is no need to continue if we are processing a node that
    // is not in the main file.
    if (!d->in_main_file ())
      continue;

    AST_Decl::NodeType nt = d->node_type ();

    // We only care to visit modules and structs during our
    // compilation.
    if (nt != AST_Decl::NT_struct && nt != AST_Decl::NT_module)
      continue;

    int retval = d->ast_accept (this);

    if (retval != 0)
      ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("%s (%d) : %M : failed to parse %s\n"),
                        d->file_name ().c_str (),
                        d->line (),
                        d->file_name ().c_str ()),
                        -1);
  }

  return 0;
}

//
// visit_scope
//
int dds2ccm_impl::visit_scope (UTL_Scope *node)
{
  for (UTL_ScopeActiveIterator si (node, UTL_Scope::IK_decls);
       !si.is_done (); si.next ())
  {
    AST_Decl * d = si.item ();
    AST_Decl::NodeType nt = d->node_type ();

    // We only care to visit modules and structs during our
    // compilation.
    if (nt != AST_Decl::NT_struct && nt != AST_Decl::NT_module)
      continue;

    int retval = d->ast_accept (this);

    if (retval != 0)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse %s\n"),
                         d->full_name ()),
                         -1);
  }

  return 0;
}

//
// visit_module
//
int dds2ccm_impl::visit_module (AST_Module *node)
{
  this->idl_
    << "module " << node->local_name ()->get_string ()
    << "{";

  if (0 != this->visit_scope (node))
    return -1;

  this->idl_
    << "};";

  return 0;
}

//
// visit_structure
//
int dds2ccm_impl::visit_structure (AST_Structure *node)
{
  this->idl_
    << "eventtype " << node->local_name ()->get_string () << "Event"
    << "{";

  // Visit each field in this structure. We are going to create
  // an equivalent member in the event type.
  AST_Field ** field = 0;
  ACE_CDR::ULong count = node->nfields ();

  for (ACE_CDR::ULong i = 0; i < count; ++ i)
  {
    node->field (field, i);

    if (0 != *field)
      (*field)->ast_accept (this);
  }

  this->idl_
    << "};";

  return 0;
}

//
// visit_field
//
int dds2ccm_impl::visit_field (AST_Field *node)
{
  // All transformations go into the public domain.
  this->idl_ << "public ";

  AST_Type * field_type = node->field_type ();
  AST_Decl::NodeType nt = field_type->node_type ();

  switch (nt)
  {
  case AST_Decl::NT_pre_defined:
    {
      AST_PredefinedType * pt = AST_PredefinedType::narrow_from_decl (field_type);
      switch (pt->pt ())
      {
      case AST_PredefinedType::PT_long:
        this->idl_ << "long";
        break;

      case AST_PredefinedType::PT_ulong:
        this->idl_ << "unsigned long";
        break;

      case AST_PredefinedType::PT_longlong:
        this->idl_ << "long long";
        break;

      case AST_PredefinedType::PT_ulonglong:
        this->idl_ << "unsigned long long";
        break;

      case AST_PredefinedType::PT_short:
        this->idl_ << "short";
        break;

      case AST_PredefinedType::PT_ushort:
        this->idl_ << "unsigned short";
        break;

      case AST_PredefinedType::PT_float:
        this->idl_ << "float";
        break;

      case AST_PredefinedType::PT_double:
        this->idl_ << "double";
        break;

      case AST_PredefinedType::PT_longdouble:
        this->idl_ << "long double";
        break;

      case AST_PredefinedType::PT_char:
        this->idl_ << "char";
        break;

      case AST_PredefinedType::PT_wchar:
        this->idl_ << "wchar";
        break;

      case AST_PredefinedType::PT_boolean:
        this->idl_ << "boolean";
        break;

      case AST_PredefinedType::PT_octet:
        this->idl_ << "octet";
        break;

      case AST_PredefinedType::PT_any:
        this->idl_ << "any";
        break;

      case AST_PredefinedType::PT_object:
        this->idl_ << "Object";
        break;

      case AST_PredefinedType::PT_void:
        this->idl_ << "void";
        break;

      case AST_PredefinedType::PT_pseudo:
        this->idl_ << pt->full_name ();
        break;
      }
    }
    break;

  case AST_Decl::NT_string:
    this->idl_ << "string";
    break;

  case AST_Decl::NT_wstring:
    this->idl_ << "wstring";
    break;

  case AST_Decl::NT_native:
    this->idl_ << "native";
    break;

  default:
    this->idl_ << "::" << node->field_type ()->full_name ();
  }

  // Finally, write the field name.
  this->idl_ << " " << node->local_name ()->get_string () << ";";

  return 0;
}
