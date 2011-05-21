#ifndef _CUTS_DMAC_APP_H_
#define _CUTS_DMAC_APP_H_

#include <iostream>
#include "ace/SString.h"
#include <algorithm>
#include <sstream>
#include "Dmac_Utils.h"
#include "Dmac_Sequence.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Execution.h"
#include "cuts/utils/testing/Test_Database.h"


/**
 * @class CUTS_Dmac_App
 *
 * Dmac Application class
 */

class CUTS_Dmac_App
{
public:

  typedef std::vector <CUTS_Dmac_Sequence *> sequence_vector;

  typedef std::vector <CUTS_Dmac_Sequence *>::iterator seq_iter;

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

  // print the help
  void print_help (void);

  // Populate the sequences after reading from the file.
  void populate_candidates (void);

  // Print the candidate patterns
  void print_candidates (void);

  // Categorize the patterns which belongs to the same log format
  void categorize_patterns (void);

  // Create the final sequence
  void create_final_pattern (std::set <int> & values);

  // Combine the qualified sequences to create the log format
  void combine_patterns (void);

  // Print the final log format
  void print_final_patterns (void);

  // Check whether the tow sequences are the same
  bool duplicate_pattern (CUTS_DMAC_UTILS::string_vector & v1,
                          CUTS_DMAC_UTILS::string_vector & v2);

  // Insert a log format to the final log format list
  void insert_to_final_list (CUTS_DMAC_UTILS::string_vector & final);

  // Print the set of qualified log formats
  void print_set (std::set <int> & values);

  // Count the {} strings in the sequence
  int count_empty_string (CUTS_DMAC_UTILS::string_vector & sequence);

  // Extract the relations among log formats
  int find_relations (void);

  // Generate the datagraph file as disjoint datagraph for
  // each execution context
  void generate_datagraph_file (void);

  // Print the coverage for each log format
  void print_coverage (void);

  // open the system execution trace database
  bool open_database (void);

  // The pattern
  ACE_CString pattern_file_;

  // The data file
  ACE_CString data_file_;

  // Name of the datagraph file
  ACE_CString name_;

  // Tota number of log messages in the trace
  long total_records_;

  // Intermediate list of possible sequences
  sequence_vector possible_patterns_;

  // The system execution trace database
  CUTS_Test_Database testdata_;

  // Set of sequences for same log format
  CUTS_DMAC_UTILS::intset_vector required_paterns_;

  // Final log formats
  std::vector <CUTS_Dmac_Log_Format *> final_patterns_;

  // Set of execution conexts
  std::vector <CUTS_Dmac_Execution *> executions_list_;

};

#endif  // !defined _CUTS_DMAC_APP_H_
