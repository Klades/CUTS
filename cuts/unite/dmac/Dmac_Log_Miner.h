// $Id: Dmac_Log_Miner.h

#ifndef _CUTS_DMAC_LOG_MINER_H_
#define _CUTS_DMAC_LOG_MINER_H_

#include <iostream>
#include "ace/SString.h"
#include <algorithm>
#include <sstream>
#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Static_Part.h"

/**
 * @class CUTS_Dmac_Log_Miner
 *
 * Dmac Log_Miner class
 */

class CUTS_Dmac_Log_Miner
{
public:

  /// Default constructor
  CUTS_Dmac_Log_Miner (ACE_CString & pattern_file,
                       ACE_CString & data_file,
                       std::vector <CUTS_Dmac_Log_Format *> & found_items);

  /// Destructor
  ~CUTS_Dmac_Log_Miner (void);

  /**
   * Populate the candidate log formats
   */
  virtual void populate_candidates (void) = 0;

  /**
   * Create the next dataset
   * @param[in] the round number
   */
  virtual void create_next_dataset (int round) = 0;

  /**
   * Create the next dataset
   * @param[in] the delimitter
   */
  void delim (std::string delims);

  /**
   * Mine the dataset and find log formats
   *
   */
  virtual void mine (void);

  /**
   * Return the current set of log formats
   * @retval  int  number of {}
   */
  std::vector <CUTS_Dmac_Log_Format *> & current_items (void);

  /**
   * Return the total number of records in the dataset
   * @retval  long  number of records
   */
  long total_records (void);

  /**
   * Set the total number of records
   * @param[in] total number of records
   */
  void total_records (long total);

  /**
   * Find the maximal sequences from the frequent sequences
   */
  void refine (void);

  /**
   * Remove the reduntant sequences from the sequence list
   * @param[in] seq_list    The original sequence list
   * @param[in] selected_seq    The sequence list which does not contain redundant sequences
   */
  int remove_redundant (std::vector <CUTS_DMAC_UTILS::string_vector> & seq_list,
                        CUTS_DMAC_UTILS::string_vector & selected_seq);

  void print_refined_sequences (void);

  /**
   * Create a new log format list
   */
  void create_log_format_list (void);


protected:

  // The pattern
  ACE_CString & pattern_file_;

  // The data file
  ACE_CString & data_file_;

  // Delimitters
  std::string delims_;

  // Tota number of log messages in the trace
  long total_records_;

  // Final log formats
  std::vector <CUTS_Dmac_Log_Format *> current_items_;

  // The items found in previous iterations
  std::vector <CUTS_Dmac_Log_Format *> & found_items_;

  // The set of maximal sequences
  std::vector <CUTS_DMAC_UTILS::string_vector> refined_sequences_;

  // The list of static part lists
  std::vector <CUTS_Dmac_Static_Part *> static_parts_;

};

#endif  // !defined _CUTS_DMAC_LOG_MINER_H_
