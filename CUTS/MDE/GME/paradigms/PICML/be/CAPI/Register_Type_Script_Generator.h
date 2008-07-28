// -*- C++ -*-

//=============================================================================
/**
 * @file          Register_Type_Script_Generator.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CAPI_REGISTER_TYPE_SCRIPT_GENERATOR_H_
#define _CUTS_CAPI_REGISTER_TYPE_SCRIPT_GENERATOR_H_

#include "PICML/PICML.h"

/**
 * @class Register_Type_Script_Generator
 *
 * Generates script for registering the MIO types for the generated
 * system. This makes the assumption that all types are registered under
 * a single user account.
 */
class Register_Type_Script_Generator
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]             basedir         Base directory of output
   */
  Register_Type_Script_Generator (const std::string & basedir);

  /// Destructor.
  ~Register_Type_Script_Generator (void);

  /**
   * Generate the registration script for the following events.
   *
   * @param[in]             events          Events to register.
   */
  void generate (const std::set <PICML::Event> & events);

private:
  void generate_sh_script (const std::set <PICML::Event> & events);

  void generate_bat_script (const std::set <PICML::Event> & events);

  const std::string & basedir_;
};

#endif  // !defined _CUTS_CAPI_REGISTER_TYPE_SCRIPT_GENERATOR_H_
