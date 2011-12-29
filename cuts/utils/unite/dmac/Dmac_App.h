#ifndef _CUTS_DMAC_APP_H_
#define _CUTS_DMAC_APP_H_

#include <iostream>
#include "ace/SString.h"
#include "ace/streams.h"
#include "ace/OS_NS_fcntl.h"
#include "ace/OS_NS_unistd.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Log_Miner.h"
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

  // A common menthod to wrap ACE_Procees methods
  int execute_process (const char * args,
                       const char * working_dir,
                       ACE_HANDLE & pipe);

  // Construct log formats
  void find_log_formats (void);

  // Initial sequence mining
  int mine_sequences (void);

  // Add the found log formats to the current list
  void accumulate (CUTS_Dmac_Log_Miner * log_miner);

  // Print the coverage
  void print_coverage (void);

  // Print the final log format
  void print_final_patterns (void);

  // open the system execution trace database
  bool open_database (void);

  // print the help
  void print_help (void);

  // Database file
  ACE_CString data_file_;

  // Database file
  CUTS_Test_Database testdata_;

  // minimum support for sequence mining
  ACE_CString min_sup_;

  // Name of the dataflow model
  ACE_CString name_;

  // Delimiter string
  ACE_CString delims_;

  // Current mining round
  int round_;

  // The log format list
  std::vector <CUTS_Dmac_Log_Format *> log_formats_;

  // current coverage
  long current_coverage_;

  // All coverage
  float coverage_;

  // Number or records in the current data file
  long current_records_;

  // Total number of records
  long total_records_;

};

#endif  // !defined _CUTS_DMAC_APP_H_