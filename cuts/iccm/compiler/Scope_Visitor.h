// -*- C++ -*-

//=============================================================================
/**
 *  @file       Scope_Vistor.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_SCOPE_VISITOR_H_
#define _ICCM_SCOPE_VISITOR_H_

#include "null_ast_visitor.h"

/**
 * @class Scope_Visitor
 *
 * Visitor that provides default implementation for methods that require
 * visiting elements in a scope.
 */
class Scope_Visitor : public null_ast_visitor
{
public:
  /// Initializing constructor.
  Scope_Visitor (void);

  /// Destructor.
  virtual ~Scope_Visitor (void);

  virtual int visit_root (AST_Root *node);
  virtual int visit_scope (UTL_Scope *node);
};

#endif  // !defined _DDS4CCM_INCLUDES_VISITOR_H_
