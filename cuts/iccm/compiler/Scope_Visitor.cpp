// $Id4

#include "Scope_Visitor.h"

#include "ast_root.h"
#include "utl_scope.h"

namespace iCCM
{

//
// Scope_Visitor
//
Scope_Visitor::Scope_Visitor (void)
{

}

//
// ~Includes_Visitor
//
Scope_Visitor::~Scope_Visitor (void)
{

}

//
// visit_root
//
int Scope_Visitor::visit_root (AST_Root *node)
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

    if (0 != d->ast_accept (this))
      return -1;
  }

  return 0;
}

//
// visit_scope
//
int Scope_Visitor::visit_scope (UTL_Scope *node)
{
  for (UTL_ScopeActiveIterator si (node, UTL_Scope::IK_decls);
       !si.is_done (); si.next ())
  {
    AST_Decl * d = si.item ();

    if (!d->in_main_file ())
      continue;

    AST_Decl::NodeType nt = d->node_type ();

    if (0 != d->ast_accept (this))
      return -1;
  }

  return 0;
}

}
