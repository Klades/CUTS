// -*- C++ -*-

//=============================================================================
/**
 * @file        CAPI_Ctx.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CAPI_CTX_H_
#define _CUTS_CAPI_CTX_H_

// Forward decl.
struct CUTS_BE_Impl_Node;

#include "../../lang/java/Java.h"
#include "Uml.h"

// code generation headers
#include "CCF/CodeGenerationKit/IndentationJava.hpp"
#include "CCF/CodeGenerationKit/IndentationXML.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

// STL includes
#include <string>
#include <fstream>

/**
 * @struct CUTS_BE_Capi
 *
 * Context for the CAPI backend. This is used to store persistant data
 * needed by the CAPI backend generator when writing the implemenation
 * files.
 */
namespace CUTS_BE_Capi
{
class Context : public CUTS_BE_Java::Context
{
public:
  /// Type definition of the architecture type.
  typedef CUTS_BE_Capi::Context architecture_type;

  /// Type definition of the behavior type.
  typedef CUTS_BE_Java::Context behavior_type;

  static std::string import (const PICML::Worker & worker);
  /// Indentation implanter.
  typedef Indentation::Implanter <Indentation::XML, char> xml_formatter_type;

  /// Target project file.
  std::ofstream project_file_;

  std::auto_ptr <xml_formatter_type> project_formatter_;

  std::ofstream workspace_file_;

  std::auto_ptr <xml_formatter_type> workspace_formatter_;

  Context (void);

  void reset (void);

  void generate_accessor_methods (std::string type, string varname);

  void generate_required_method_impl (const std::string & method);

  void generate_throws_signature (const std::string & method);

  typedef std::map <std::string, PICML::PeriodicEvent> Periodic_Map;

  Periodic_Map periodics_;

  typedef std::map <std::string, bool> Env_Seen_Map;

  Env_Seen_Map env_seen_;

  /// The classname of the current implementation.
  std::string impl_classname_;

  /// Keeps track of the current branch depth.
  std::stack <size_t> branches_;

  /// Number of parameters.
  size_t param_count_;

  /**
   * Current implementation's node. This can be used to store
   * information needed by the project/workspace generators.
   */
  CUTS_BE_Impl_Node * impl_node_;

  /// The event types used throughout all the projects.
  std::set <PICML::Event> workspace_events_;
};
}

#endif  // !defined _CUTS_CAPI_CTX_H_
