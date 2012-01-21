// -*- C++ -*-

//=============================================================================
/**
 *  @file       null_ast_visitor.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_NULL_AST_VISITOR_H_
#define _ICCM_NULL_AST_VISITOR_H_

#include "ast_visitor.h"

/**
 * @class null_ast_visitor
 */
class null_ast_visitor : public ast_visitor
{
protected:
  /// Default constructor.
  null_ast_visitor (void) { };

public:
  /// Destructor.
  virtual ~null_ast_visitor (void) { };

  virtual int visit_root (AST_Root *node) { return 0; }
  virtual int visit_scope (UTL_Scope *node) { return 0; }
  virtual int visit_module (AST_Module *node) { return 0; }
  virtual int visit_structure (AST_Structure *node) { return 0; }
  virtual int visit_field (AST_Field *node) { return 0; }
  virtual int visit_decl (AST_Decl *d) { return 0; }
  virtual int visit_type (AST_Type *node) { return 0; }
  virtual int visit_predefined_type (AST_PredefinedType *node) { return 0; }
  virtual int visit_interface (AST_Interface *node) { return 0; }
  virtual int visit_interface_fwd (AST_InterfaceFwd *node) { return 0; }
  virtual int visit_valuetype (AST_ValueType *node) { return 0; }
  virtual int visit_valuetype_fwd (AST_ValueTypeFwd *node) { return 0; }
  virtual int visit_component (AST_Component *node) { return 0; }
  virtual int visit_home (AST_Home *node){ return 0; }
  virtual int visit_component_fwd (AST_ComponentFwd *node){ return 0; }
  virtual int visit_template_module (AST_Template_Module *node){ return 0; }
  virtual int visit_template_module_inst (AST_Template_Module_Inst *node){ return 0; }
  virtual int visit_template_module_ref (AST_Template_Module_Ref *node){ return 0; }
  virtual int visit_param_holder (AST_Param_Holder *node){ return 0; }
  virtual int visit_porttype (AST_PortType *node){ return 0; }
  virtual int visit_provides (AST_Provides *node){ return 0; }
  virtual int visit_uses (AST_Uses *node){ return 0; }
  virtual int visit_publishes (AST_Publishes *node){ return 0; }
  virtual int visit_emits (AST_Emits *node){ return 0; }
  virtual int visit_consumes (AST_Consumes *node){ return 0; }
  virtual int visit_extended_port (AST_Extended_Port *node){ return 0; }
  virtual int visit_mirror_port (AST_Mirror_Port *node){ return 0; }
  virtual int visit_connector (AST_Connector *node){ return 0; }
  virtual int visit_eventtype (AST_EventType *node){ return 0; }
  virtual int visit_eventtype_fwd (AST_EventTypeFwd *node){ return 0; }
  virtual int visit_factory (AST_Factory *node){ return 0; }
  virtual int visit_finder (AST_Finder *node){ return 0; }
  virtual int visit_structure_fwd (AST_StructureFwd *node){ return 0; }
  virtual int visit_exception (AST_Exception *node){ return 0; }
  virtual int visit_expression (AST_Expression *node){ return 0; }
  virtual int visit_enum (AST_Enum *node){ return 0; }
  virtual int visit_operation (AST_Operation *node){ return 0; }
  virtual int visit_argument (AST_Argument *node){ return 0; }
  virtual int visit_attribute (AST_Attribute *node){ return 0; }
  virtual int visit_union (AST_Union *node){ return 0; }
  virtual int visit_union_fwd (AST_UnionFwd *node){ return 0; }
  virtual int visit_union_branch (AST_UnionBranch *node){ return 0; }
  virtual int visit_union_label (AST_UnionLabel *node){ return 0; }
  virtual int visit_constant (AST_Constant *node){ return 0; }
  virtual int visit_enum_val (AST_EnumVal *node){ return 0; }
  virtual int visit_array (AST_Array *node){ return 0; }
  virtual int visit_sequence (AST_Sequence *node){ return 0; }
  virtual int visit_string (AST_String *node){ return 0; }
  virtual int visit_typedef (AST_Typedef *node){ return 0; }
  virtual int visit_native (AST_Native *node){ return 0; }
  virtual int visit_valuebox (AST_ValueBox *node){ return 0; }
};

#endif  // !defined _ICCM_NULL_AST_VISITOR_H_
