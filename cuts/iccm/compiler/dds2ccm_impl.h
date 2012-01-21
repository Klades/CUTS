// -*- C++ -*-

//=============================================================================
/**
 *  @file       dds2ccm_impl.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#include <fstream>
#include "null_ast_visitor.h"

/**
 * @class dds2ccm_impl
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class dds2ccm_impl : public null_ast_visitor
{
public:
  /// Default constructor.
  dds2ccm_impl (std::ofstream & idl);

  /// Destructor.
  virtual ~dds2ccm_impl (void);

  // used methods
  virtual int visit_root (AST_Root *node);
  virtual int visit_scope (UTL_Scope *node);
  virtual int visit_module (AST_Module *node);
  virtual int visit_structure (AST_Structure *node);
  virtual int visit_field (AST_Field *node);

private:
  /// Target idl file for generation.
  std::ofstream & idl_;
};
