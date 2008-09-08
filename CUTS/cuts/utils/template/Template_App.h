// -*- C++ -*-

//=============================================================================
/**
 * @file        Template_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 *              James R. Edmondson
 */
//=============================================================================

#ifndef _CUTS_TEMPLATE_APP_H_
#define _CUTS_TEMPLATE_APP_H_

#include "Template_App_Options.h"
#include "cuts/utils/common/Property_Expander.h"
#include "cuts/utils/common/Property_Map.h"

/**
 * @class CUTS_Template_App
 *
 * Application object for the CUTS template replacement engine.
 */
class CUTS_Template_App
{
public:
  /// Default constructor.
  CUTS_Template_App (void);

  /// Destructor.
  ~CUTS_Template_App (void);

  /**
   * Run the application
   *
   * @param[in]         argc        Number of arguments
   * @param[in]         argv        Command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  /**
   * Parse the command-line arguments
   *
   * @param[in]         argc        Number of arguments
   * @param[in]         argv        Command-line arguments
   */
  int parse_args (int argc, char * argv []);

  /**
   * Expand the template into the specified output stream.
   *
   * @param[out]        out         Target output stream
   */
  void expand_into (std::ostream & out);

  /**
   * Load the property configuration file.
   *
   * @param[in]         file        Source property file
   */
  bool load_property_file (const ACE_CString & file);

  /// Print the help for the application.
  void print_help (void);

  /**
   * Enable severity level(s) for the ACE_Log_Msg.
   */
  void enable_logmsg_severity (u_long severity);

  /// Options for the application.
  CUTS_Template_App_Options opts_;

  CUTS_Property_Map prop_map_;

  CUTS_Property_Expander expander_;
};

#endif  // !defined _CUTS_TEMPLATE_APP_H_
