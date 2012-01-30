// -*- C++ -*-

//=============================================================================
/**
 *  @file       Includes_Visitor.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _DDS4CCM_INCLUDES_VISITOR_H_
#define _DDS4CCM_INCLUDES_VISITOR_H_

#include "Null_Visitor.h"
#include "ace/Unbounded_Set.h"
#include "ace/SString.h"

#include <fstream>

namespace iCCM
{

/**
 * @class Includes_Visitor
 */
class Includes_Visitor : public Null_Visitor
{
public:
  /// Initializing constructor.
  Includes_Visitor (std::ofstream & idl);

  /// Destructor.
  virtual ~Includes_Visitor (void);

  virtual int visit_root (AST_Root *node);
  virtual int visit_scope (UTL_Scope *node);
  virtual int visit_module (AST_Module *node);
  virtual int visit_structure (AST_Structure *node);
  virtual int visit_field (AST_Field *node);

private:
  /// Target IDL file.
  std::ofstream & idl_;

  /// List of seen includes.
  ACE_Unbounded_Set <ACE_CString> includes_;
};

}

#endif  // !defined _DDS4CCM_INCLUDES_VISITOR_H_
