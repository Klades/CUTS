// -*- C++ -*-

//=============================================================================
/**
 *  @file       Servant_File.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_SERVANT_FILE_H_
#define _ICCM_SERVANT_FILE_H_

#include "Scope_Visitor.h"
#include <fstream>

namespace iCCM
{

/**
 * @class Servant_File
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class Servant_File : public Scope_Visitor
{
public:
  /// Default constructor.
  Servant_File (void);

  /// Destructor.
  virtual ~Servant_File (void);

  // used methods
  virtual int visit_root (AST_Root *node);
  virtual int visit_module (AST_Module * node);
  virtual int visit_component (AST_Component * node);

private:
  std::ofstream hfile_;
  std::ofstream sfile_;
};

}

#endif  // !defined _ICCM_EXECUTOR_IDL_FILE_
