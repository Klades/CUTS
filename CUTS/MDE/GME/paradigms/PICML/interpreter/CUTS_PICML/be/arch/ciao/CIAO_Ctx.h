// -*- C++ -*-

//=============================================================================
/**
 * @file          CIAO_Ctx.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CIAO_CTX_H_
#define _CUTS_BE_CIAO_CTX_H_

#include <set>
#include <fstream>
#include "../../lang/cpp/Cpp.h"

// Forward decl.
struct CUTS_BE_IDL_Node;

/**
 * Context for the CIAO backend generator.
 */
struct CUTS_BE_Ciao : public CUTS_BE_CPP::Context
{
  typedef CUTS_BE_CPP::Context behavior_type;

  /// Type definition for a collection of nodes.
  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  /// Collection of visited nodes.
  IDL_Node_Set visited_nodes_;

  /// The target workspace file.
  std::ofstream workspace_;

  /// The target project file.
  std::ofstream project_;
};

#endif  // !defined _CUTS_BE_CIAO_CTX_H_
