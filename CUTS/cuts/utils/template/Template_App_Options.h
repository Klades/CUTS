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

/**
 * @class CUTS_Template_App_Options
 */
class CUTS_Template_App_Options
{
public:
  /// Default constructor. Set the default values for the command-line
  /// options.
  CUTS_Template_App_Options (void)
    : use_env_ (false)
  {

  }

  /// Input template.
  ACE_CString input_;

  /// Target output file for the conversion.
  ACE_CString output_;

  /// Property configuration file.
  ACE_CString config_;

  /// List of properties defined on the command-line.
  ACE_Vector <ACE_CString> defines_;

  /// Use environment variables in the conversion.
  bool use_env_;
};

#endif  // !defined _CUTS_TEMPLATE_APP_OPTIONS_H_
