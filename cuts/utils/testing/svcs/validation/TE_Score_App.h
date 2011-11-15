// -*- C++ -*-

//=============================================================================
/**
 * @file        TE_Score.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TE_SCORE_APP_H_
#define _CUTS_TE_SCORE_APP_H_

#include "TE_Score_App_Options.h"
#include "cuts/config.h"

/**
 * @class CUTS_TE_Score_App
 *
 * Main entry point object for the application.
 */
class CUTS_TE_Score_App
{
public:
  /// Default constructor.
  CUTS_TE_Score_App (void);

  /// Destructor.
  ~CUTS_TE_Score_App (void);

  /**
   * Run the application
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method for printing the help.
  void print_help (void);

  /// Options for the application.
  CUTS_TE_Score_App_Options opts_;
};

#if defined (__CUTS_INLINE__)
#include "TE_Score_App.inl"
#endif

#endif  // !defined _CUTS_TRACE_IMPORTER_APP_H_
