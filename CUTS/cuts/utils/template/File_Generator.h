// -*- C++ -*-

//=============================================================================
/**
 * @file        File_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_FILE_GENERATOR_H_
#define _CUTS_FILE_GENERATOR_H_

#include "cuts/utils/Property_Map.h"
#include "Template_Config_Handler.h"
#include <string>

/**
 * @class CUTS_File_Generator
 *
 * Functor that generates a file for a template.
 */
class CUTS_File_Generator :
  public CUTS_Template_Config_Handler
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]     use_env                 Use environment variables
   * @param[in]     ignore_variables        Replace variables
   * @param[in]     ignore_commands         Replace commands
   * @param[in]     template_file           Use the following template file
   * @param[in]     output                  Output directory for file
   * @param[in]     overrides               Properties used for overriding
   */
  CUTS_File_Generator (const bool & use_env,
                       const bool & ignore_variables,
                       const bool & ignore_commands,
                       const std::string & template_file,
                       const std::string & output);

  /// Destructor.
  ~CUTS_File_Generator (void);

  /**
   * Handle a configuration
   */
  int handle_config (const CUTS_Property_Map & config);

private:
  const bool & use_env_;

  const bool & ignore_variables_;

  const bool & ignore_commands_;

  /// The template file to use for generating real files.
  const std::string & template_;

  /// Target output directory for the files.
  const std::string & output_;
};

#if defined (__CUTS_INLINE__)
#include "File_Generator.inl"
#endif

#endif  // !defined _CUTS_FILE_GENERATOR_H_
