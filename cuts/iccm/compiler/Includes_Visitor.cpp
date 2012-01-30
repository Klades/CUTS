// $Id4

#include "Includes_Visitor.h"

#include "ast_decl.h"
#include "ast_field.h"
#include "ast_root.h"
#include "ast_structure.h"

#include "be_global.h"

namespace iCCM
{

//
// Includes_Visitor
//
Includes_Visitor::Includes_Visitor (std::ofstream & idl)
: idl_ (idl)
{

}

//
// ~Includes_Visitor
//
Includes_Visitor::~Includes_Visitor (void)
{

}

//
// visit_root
//
int Includes_Visitor::visit_root (AST_Root *node)
{
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

  if (this->includes_.size ())
    this->idl_ << std::endl;

  return 0;
}

//
// visit_scope
//
int Includes_Visitor::visit_scope (UTL_Scope *node)
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
int Includes_Visitor::visit_module (AST_Module *node)
{
  return this->visit_scope (node);
}

//
// visit_structure
//
int Includes_Visitor::visit_structure (AST_Structure *node)
{
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

  return 0;
}

//
// visit_field
//
int Includes_Visitor::visit_field (AST_Field *node)
{
  AST_Type * field_type = node->field_type ();
  AST_Decl::NodeType nt = field_type->node_type ();

  if (nt != AST_Decl::NT_pre_defined &&
      nt != AST_Decl::NT_string &&
      nt != AST_Decl::NT_wstring)
  {
    AST_Type * field_type = node->field_type ();

    if (0 != this->includes_.find (field_type->file_name ()))
    {
      ACE_CString filename;
      BE_GlobalData::get_filename (field_type->file_name (), filename);

      this->idl_
        << "#include \"" << filename << "\"" << std::endl;

      // Save the file name so we do not generate its include
      // the next time we see it.
      this->includes_.insert (field_type->file_name ());
    }
  }

  return 0;
}

}
