// -*- C++ -*-

//=============================================================================
/**
 *  @file       Executor_IDL_File_Visitor.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_EXECUTOR_IDL_FILE_VISITOR_H_
#define _ICCM_EXECUTOR_IDL_FILE_VISITOR_H_

#include <fstream>
#include "Scope_Visitor.h"

/**
 * @class Executor_IDL_File_Visitor
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class Executor_IDL_File_Visitor : public Scope_Visitor
{
public:
  /// Default constructor.
  Executor_IDL_File_Visitor (std::ofstream & idl);

  /// Destructor.
  virtual ~Executor_IDL_File_Visitor (void);

  // used methods
  virtual int visit_root (AST_Root *node);
  virtual int visit_module (AST_Module *node);
  virtual int visit_component (AST_Component *node);

private:
  /// Target idl file for generation.
  std::ofstream & idl_;
};

#endif  // !defined _ICCM_EXECUTOR_IDL_FILE_VISITOR_H_
