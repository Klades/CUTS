// -*- C++ -*-

//=============================================================================
/**
 * @file          Template_App_Options.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEMPLATE_APP_OPTIONS_H_
#define _CUTS_TEMPLATE_APP_OPTIONS_H_

#include "ace/SString.h"
#include "ace/Vector_T.h"
#include <string>

/**
 * @class CUTS_Template_App_Options
 */
class CUTS_Template_App_Options
{
public:
  /// Default constructor. Set the default values for the command-line
  /// options.
  CUTS_Template_App_Options (void)
    : use_env_ (false),
      ignore_variables_ (false),
      ignore_commands_ (false)
  {

  }

  /// Input template.
  std::string input_;

  /// Target output file for the conversion.
  std::string output_;

  /// Property configuration file.
  std::string config_;

  /// File with list of configurations.
  std::string config_list_;

  /// List of properties defined on the command-line.
  ACE_Vector <ACE_CString> defines_;

  /// Use environment variables in the conversion.
  bool use_env_;

  bool ignore_variables_;

  bool ignore_commands_;
};

#endif  // !defined _CUTS_TEMPLATE_APP_OPTIONS_H_
