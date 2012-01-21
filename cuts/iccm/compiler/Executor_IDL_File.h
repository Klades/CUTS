// -*- C++ -*-

//=============================================================================
/**
 *  @file       Executor_IDL_File.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_EXECUTOR_IDL_FILE_H_
#define _ICCM_EXECUTOR_IDL_FILE_H_

#include <fstream>
#include "null_ast_visitor.h"

/**
 * @class Executor_IDL_File
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class Executor_IDL_File : public null_ast_visitor
{
public:
  /// Default constructor.
  Executor_IDL_File (void);

  /// Destructor.
  virtual ~Executor_IDL_File (void);

  // used methods
  virtual int visit_root (AST_Root *node);
};

#endif  // !defined _ICCM_EXECUTOR_IDL_FILE_
