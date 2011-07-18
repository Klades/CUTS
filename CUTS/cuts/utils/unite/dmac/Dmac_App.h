#ifndef _CUTS_DMAC_APP_H_
#define _CUTS_DMAC_APP_H_

#include <iostream>
#include "ace/SString.h"
#include "ace/streams.h"
#include "ace/OS_NS_fcntl.h"
#include "ace/OS_NS_unistd.h"
#include <vector>

class CUTS_Dmac_App
{
public:
  /// Default constructor
  CUTS_Dmac_App (void);

  /// Destructor
  ~CUTS_Dmac_App (void);

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

  // A coomon menthod to wrap ACE_Procees methods
  int execute_process (const char * args,
                       const char * working_dir,
                       ACE_HANDLE & pipe);

  // Convert to vertical data format
  int convert_to_vertical ();

  // Initial sequence mining
  int mine_sequences ();

  // Generate the dataflow
  int generate_dataflow ();

  // print the help
  void print_help (void);

  // Database file
  ACE_CString data_file_;

  // minimum support for sequence mining
  ACE_CString min_sup_;

  // Name of the dataflow model
  ACE_CString name_;

  //location of the spade
  ACE_CString spade_location_;

  // tells whether to delete the immediate files or not
  bool delete_intermediate_;

};

#endif  // !defined _CUTS_DMAC_APP_H_