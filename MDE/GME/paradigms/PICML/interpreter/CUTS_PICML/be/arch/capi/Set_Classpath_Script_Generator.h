// -*- C++ -*-

//=============================================================================
/**
 * @file          Set_Classpath_Script_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CAPI_SET_CLASSPATH_SCRIPT_GENERATOR_H_
#define _CUTS_CAPI_SET_CLASSPATH_SCRIPT_GENERATOR_H_

#include "PICML/PICML.h"

/**
 * @class Set_Classpath_Script_Generator
 *
 * Visitor that generates scripts for setting the CLASSPATH environment
 * variable for the auto-generated system.
 */
class Set_Classpath_Script_Generator : public PICML::Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         basedir         Base directory for scripts
   */
  Set_Classpath_Script_Generator (const std::string & basedir);

  /// Destructor.
  virtual ~Set_Classpath_Script_Generator (void);

  // Visit a RootFolder element.
  void Visit_RootFolder (
    const PICML::RootFolder &);

  // Visit a ComponentImplementations element.
  void Visit_ComponentImplementations (
    const PICML::ComponentImplementations &);

  // Visit a ComponentImplementationContainer element.
  void Visit_ComponentImplementationContainer (
    const PICML::ComponentImplementationContainer &);

  // Visit a MonolithicImplementation element.
  void Visit_MonolithicImplementation (
    const PICML::MonolithicImplementation &);

private:
  void generate_bat_script (const std::string & bindir);

  void generate_sh_script (const std::string & bindir);

  /// Base directory for the scripts.
  std::string basedir_;

  /// Collection of JAR file to add to classpath.
  std::set <std::string> impls_;

  std::set <std::string> lit_jars_;
};

#endif  // !defined _CUTS_CAPI_SET_CLASSPATH_SCRIPT_GENERATOR_H_
