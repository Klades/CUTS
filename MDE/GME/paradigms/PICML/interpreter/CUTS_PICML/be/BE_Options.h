// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Options.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_OPTIONS_H_
#define _CUTS_BE_OPTIONS_H_

#include <string>
#include "BE_export.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/**
 * @class CUTS_BE_Options
 *
 * Collection of options for the backend generators. The class is
 * a singleton, which allows developers to access this information
 * as if it was global.
 */
struct CUTS_BE_Export CUTS_BE_Options
{
  CUTS_BE_Options (void)
    : iccm_compliant_ (false)
  {

  }

  /// Name of the project.
  std::string project_name_;

  /// Selected output directory for the backend.
  std::string output_directory_;

  /// Suffix for the executor files.
  std::string exec_suffix_;

  enum Menu_Option
  {
    /// Generate CoWorkEr models.
    OPT_GENERATE_MODELS = 0,

    /// Generate CoWorkEr proxy assemblies.
    OPT_GENERATE_PROXY_ASSEMBLIES = 1,

    /// Generate source files from the model.
    OPT_GENERATE_SOURCE = 2
  };

  bool iccm_compliant_;

  /// Menu options for the backend.
  Menu_Option option_;
};

CUTS_BE_SINGLETON_DECLARE (ACE_Singleton, CUTS_BE_Options, ACE_Null_Mutex);

#define CUTS_BE_OPTIONS() \
  ACE_Singleton <CUTS_BE_Options, ACE_Null_Mutex>::instance ()

#endif  // !defined _CUTS_BE_OPTIONS_H_
