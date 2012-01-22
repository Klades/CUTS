// $Id: Dmac_Vertical_Format.h

#ifndef _CUTS_DMAC_VERTICAL_FORMAT_H
#define _CUTS_DMAC_VERTICAL_FORMAT_H



#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "cuts/unite/dmac/Dmac_Utils.h"
#include <fstream>
#include <sstream>

/**
 * @class CUTS_Dmac_Vertical_Format
 *
 * Represent the vertical format of a log message
 */
class CUTS_Dmac_Vertical_Format
{

public:

  /// Default Constructor
  CUTS_Dmac_Vertical_Format (void);

  /// Destructor
  ~CUTS_Dmac_Vertical_Format (void);

  /**
   * Set the transaction id
   * @param[in]     tid    The transaction id
   */
  void tid (long tid);

  /**
   * Set the timestamp of the event
   * @param[in]     time_val    The timestamp
   */
  void time_val (long time_val);

  /**
   * Add a word to the word list
   * @param[in]     word    The word to be added
   */
  void insert_word (std::string word);

  /**
   * Get the data from the global table and set
   * @param[in]     word_index    the global table
   */
  void populate (CUTS_DMAC_UTILS::sequence_details & word_index);

  /// Print the set of words
  void print_row_words (std::ofstream & output);

private:

  /// Transaction id
  long tid_;

  /// Timestamp of the record
  long time_val_;

  /// indexes of the items
  CUTS_DMAC_UTILS::int_vector items_;

  /// Set of words
  CUTS_DMAC_UTILS::string_vector row_words_;

};

#endif /* _CUTS_DMAC_VERTICAL_FORMAT_H */