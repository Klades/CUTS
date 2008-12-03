// -*- C++ -*-

//=============================================================================
/**
 * @file          Context.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_EISA_CTX_H_
#define _CUTS_BE_EISA_CTX_H_

#include <set>
#include <fstream>

// Forward decl.
struct CUTS_BE_IDL_Node;

/**
 * Context for the EISA backend generator.
 */
struct CUTS_BE_Eisa
{
  /// The target workspace file.
  std::ofstream workspace_file_;

  /// The target project file.
  std::ofstream project_file_;

  /// Type definition for a collection of nodes.
  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  /// Collection of visited nodes.
  IDL_Node_Set visited_nodes_;
};

#endif  // !defined _CUTS_BE_CIAO_CTX_H_
