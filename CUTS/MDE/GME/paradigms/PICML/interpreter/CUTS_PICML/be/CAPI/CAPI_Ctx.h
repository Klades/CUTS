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

#include "../String_Set.h"
#include "PICML/PICML.h"
#include "Uml.h"

// ACE includes
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

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
class CUTS_BE_Capi
{
public:
  static std::string setter_method (const std::string & name);

  static std::string getter_method (const std::string & name);

  static std::string fq_name (const PICML::NamedType & type,
                              char separator = '.');

  static std::string scope (const PICML::NamedType & type,
                            char separator = '.');

  static std::string import (const PICML::Worker & worker);

  static std::string classname (const std::string & str);

  typedef std::map <Uml::Class, std::string> PredefinedType_Map;

  static PredefinedType_Map predefined_type_map_;

  /// Default constructor.
  CUTS_BE_Capi (void);

  /// Target source file.
  std::ofstream outfile_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::Java, char> _formatter_type;

  /// Pointer to the formatter.
  std::auto_ptr <_formatter_type> formatter_;

  /// Indentation implanter.
  typedef Indentation::Implanter <
    Indentation::XML, char> _project_formatter_type;

  /// Target project file.
  std::ofstream project_file_;

  std::ofstream workspace_file_;

  std::auto_ptr <_project_formatter_type> project_formatter_;

  std::auto_ptr <_project_formatter_type> workspace_formatter_;

  void reset (void);

  void generate_accessor_methods (std::string type, string varname);

  void generate_required_method_impl (const std::string & method);

  void generate_throws_signature (const std::string & method);

  typedef std::map <std::string, PICML::PeriodicEvent> Periodic_Map;

  // <port name, event>
  typedef std::map <std::string, PICML::Event> Event_Port_Map;

  Event_Port_Map sinks_;

  Event_Port_Map sources_;

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

// Singleton declaration for the backend generator.
#define CUTS_BE_CAPI() \
  ACE_Singleton <CUTS_BE_Capi, ACE_Null_Mutex>::instance ()

#endif  // !defined _CUTS_CAPI_CTX_H_
