#ifndef _CUTS_DMAC_SEQUENCE_H
#define _CUTS_DMAC_SEQUENCE_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Utils.h"
#include "cuts/utils/testing/Test_Database.h"

/**
 * @class CUTS_Dmac_Sequence
 *
 * Represent a frequent sequence identified by the sequence mining tool
 */

class CUTS_Dmac_Sequence
{

public:

  // Default constructor
  CUTS_Dmac_Sequence ();

  // Destructor
  ~CUTS_Dmac_Sequence ();

  /**
   * Add the position details to a raw sequence
   *
   * @param[in]     raw_sequence    The set of words
   */
  void populate_items (CUTS_DMAC_UTILS::string_vector & raw_sequence);

  /**
   * Check whether the positions of the sequence are already updated in a
   * previous update
   *
   * @return true or false
   */
  bool position_already_updated ();

  /**
   * Check whether two sequences are contained in the same message set
   *
   * @param[in]     sequence     The sequence for the comparison
   * @return true or false
   */
  bool match_row_set (CUTS_Dmac_Sequence & sequence);

  /**
   * High level function to qualify a given sequence
   *
   * @param[in]      trace      The actual log message
   * @param[in]      row_id     The id of the log message
   * @return true or false
   */
  bool valid_pattern (CUTS_DMAC_UTILS::string_vector & trace,
                      int row_id);

  // Prints a sequence
  void print_pattern ();

  /**
   * Get the value of the add_row flag
   *
   * @return true or false
   */
  bool add_row (void);

  /**
   * Get the value of the slected flag
   *
   * @return true or false
   */
  bool selected (void);

  /**
   * Get the number of rows for this sequence
   *
   * @return the number of rows
   */
  int row_count (void);

  /**
   * Get the maximum number of words in a row
   *
   * @return the max number of words
   */
  int max_row_words (void);

  /**
   * Set the add_row flag
   *
   * @param[in]   add_row
   *              value which tells whether to set the flag
   */
  void add_row (bool add_row);

   /**
   * Set the selected flag
   *
   * @param[in]   add_row
   *              value which tells whether the sequence is selected or not
   */
  void selected (bool seelcted);

  /**
   * Set the number of rows containing this sequence
   *
   * @param[in]     row_count numnber of rows
   *
   */
  void row_count (int row_count);

  /**
   * Set the maximum number of words in selected rows
   *
   * @param[in]     max_row_words    number of words
   *
   */
  void max_row_words (int max_row_words);

  /**
   * Get the set of row_ids
   *
   * @return the max number of words
   */
  CUTS_DMAC_UTILS::int_vector & row_ids ();

  /**
   * Get the word and position table
   *
   * @return map containing the word and position
   */
  CUTS_DMAC_UTILS::sequence_details & key_position_table ();


private:

  // Add the id of a row containing the sequence
  void add_row_id (int id);

  //Check whether the sequence is a sunbset of a given trace
  bool check_subset (CUTS_DMAC_UTILS::string_vector & trace);

  // Check whether the sequence is contained in the same positions
  // in each message
  bool check_positions (CUTS_DMAC_UTILS::string_vector & trace);

  // A tempory flag to keep whether a row needs to be added
  bool add_row_;

  // Flag to tell whether thr sequence is selected
  bool selected_;

  // Number of rows in which this sequence is contained
  int row_count_;

  // The max number of words in a trace which this sequence is contained
  int max_row_words_;

  // Set of rows this sequence contained in,
  CUTS_DMAC_UTILS::int_vector row_ids_;

  // Table to contain the word of the sequence and their position
  CUTS_DMAC_UTILS::sequence_details key_position_table_;

};

#if defined (__CUTS_INLINE__)
#include "Dmac_Sequence.inl"
#endif

#endif /* _CUTS_DMAC_SEQUENCE_H */