// -*- C++ -*-

//=============================================================================
/**
 * @file        Trace_Importer_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TRACE_IMPORTER_APP_H_
#define _CUTS_TRACE_IMPORTER_APP_H_

#include "cuts/config.h"
#include "ace/SString.h"

/**
 * @class CUTS_Trace_Importer_App
 *
 * Main entry point object for the application.
 */
class CUTS_Trace_Importer_App
{
public:
  /// Default constructor.
  CUTS_Trace_Importer_App (void);

  /// Destructor.
  ~CUTS_Trace_Importer_App (void);

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

  /// Location of the test database.
  ACE_CString test_file_;

  /// Location of the input file.
  ACE_CString input_file_;

  /// Host that generated the trace file.
  ACE_CString hostname_;
};

#if defined (__CUTS_INLINE__)
#include "Trace_Importer_App.inl"
#endif

#endif  // !defined _CUTS_TRACE_IMPORTER_APP_H_
