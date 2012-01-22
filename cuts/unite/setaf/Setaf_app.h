// $Id: Setaf_App.h

#ifndef _CUTS_SETAF_APP_H_
#define _CUTS_SETAF_APP_H_

#include <iostream>
#include "ace/SString.h"

class CUTS_Setaf_App
{
public:
  /// Default constructor
  CUTS_Setaf_App (void);

  /// Destructor
  ~CUTS_Setaf_App (void);

  /**
   * Main entry point for the application
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguements
   */
  int run_main (int argc, char * argv []);

private:

   // Helper method to pass the command line arguments
  int parse_args (int argc, char * argv []);

  // print the help
  void print_help (void);

  // Get the name of the CUTS_Setaf from the input file path
  const char * extract_name ();

  // the file containg the adaptation script
  ACE_CString input_file_;

  // Folder to output the code
  ACE_CString output_dir_;

};

#endif  // !defined _CUTS_SETAF_APP_H_