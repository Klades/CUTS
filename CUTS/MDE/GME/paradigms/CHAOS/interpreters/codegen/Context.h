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

#ifndef _CUTS_BE_OPENSPLICE_CTX_H_
#define _CUTS_BE_OPENSPLICE_CTX_H_

#include <set>
#include <fstream>
#include "ccm/CCM.h"

// Forward decl.
struct CUTS_BE_IDL_Node;

namespace CUTS_CHAOS
{
/**
 * Context for the CIAO backend generator.
 */
struct Context :
  public CUTS_BE_CCM::Cpp::Context
{
  /// Type definition of the architecture type.
  typedef CUTS_BE_CCM::Cpp::Context arch_type;

  /// Type definition of the behavior type.
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
}

#endif  // !defined _CUTS_BE_OPENSPLICE_CTX_H_
