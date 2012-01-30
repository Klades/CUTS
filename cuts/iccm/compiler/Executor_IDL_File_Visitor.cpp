// $Id$

#include "Executor_IDL_File_Visitor.h"
#include "Scope_Visitor.h"

#include "ast_decl.h"
#include "ast_field.h"
#include "ast_root.h"
#include "ast_component.h"
#include "ast_publishes.h"
#include "ast_emits.h"

#include "utl_identifier.h"
#include "utl_scope.h"

#include "ace/Log_Msg.h"

#include "CCF/CodeGenerationKit/IndentationIDL.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

namespace iCCM
{

/**
 * @class Local_Context_Method_Visitor
 *
 * Helper visitor that generates methods on an iCCM local context. The
 * main methods are those for creating an event for a given port.
 */
class Local_Context_Method_Visitor : public Scope_Visitor
{
public:
  Local_Context_Method_Visitor (std::ofstream & idl)
    : idl_ (idl)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes *node)
  {
    this->idl_
      << "::" << node->field_type ()->full_name ()
      << " new_" << node->local_name ()->get_string () << "_event ();";

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits *node)
  {
    this->idl_
      << "::" << node->field_type ()->full_name ()
      << " new_" << node->local_name ()->get_string () << "_event ();";

    return 0;
  }

private:
  std::ofstream & idl_;
};

//
// Executor_IDL_File_Visitor
//
Executor_IDL_File_Visitor::
Executor_IDL_File_Visitor (std::ofstream & idl)
: idl_ (idl)
{

}

//
// ~Executor_IDL_File_Visitor
//
Executor_IDL_File_Visitor::~Executor_IDL_File_Visitor (void)
{

}

//
// visit_root
//
int Executor_IDL_File_Visitor::visit_root (AST_Root *node)
{
  // Open the file for writing.
  Indentation::Implanter <Indentation::IDL, char> implanter (this->idl_);
  return Scope_Visitor::visit_root (node);
}

//
// visit_module
//
int Executor_IDL_File_Visitor::visit_module (AST_Module *node)
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
int Executor_IDL_File_Visitor::visit_component (AST_Component *node)
{
  const char * local_name = node->local_name ()->get_string ();

  this->idl_
    << "local interface iCCM_" << local_name << "_Context : "
    << "CCM_" << local_name << "_Context"
    << "{";

  Local_Context_Method_Visitor lcv (this->idl_);
  lcv.visit_scope (node);

  this->idl_
    << "};";

  return 0;
}

}
