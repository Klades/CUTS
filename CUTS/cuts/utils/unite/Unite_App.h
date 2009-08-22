// -*- C++ -*-

//=============================================================================
/**
 * @file        Unite_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_APP_H_
#define _CUTS_UNITE_APP_H_

#include "ace/SString.h"
#include "ace/Unbounded_Set.h"
#include "Presentation_Service_Manager.h"

namespace CUTS
{
  // Forward decl.
  class serviceList;

  // Forward decl.
  class serviceType;
}

/**
 * @class CUTS_Unite_App
 *
 * Main entry point for the application represented as an
 * object. This helps prevent pollution of the global namespace.
 */
class CUTS_Unite_App
{
public:
  /// Default constructor
  CUTS_Unite_App (void);

  /// Destructor
  ~CUTS_Unite_App (void);

  /**
   * Main entry point for the application
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguements
   */
  int run_main (int argc, char * argv []);

private:
  /// Helper method to parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Load services from the configuration.
  void load_services (const CUTS::serviceList & list);

  /// Print the help screen for the application.
  void print_help (void);

  /// Location of the configuration file.
  ACE_CString config_;

  /// Location of the test data file.
  ACE_CString datafile_;

  /// Location of the variable tables.
  ACE_CString sandbox_;

  ACE_CString datagraph_;

  /// Show the data trend for the result.
  bool show_trend_;

  typedef ACE_Unbounded_Set <ACE_CString> string_set;

  /// List of services to disable.
  string_set disables_;

  /// Service manager for the application.
  CUTS_Unite_Presentation_Service_Manager svc_mgr_;
};

#endif  // !defined _CUTS_UNITE_APP_H_
