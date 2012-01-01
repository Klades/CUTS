// $Id: Dmac_Static_Part.h

#ifndef _CUTS_DMAC_STATIC_PART_H
#define _CUTS_DMAC_STATIC_PART_H


#include "ace/OS_Memory.h"
#include "cuts/config.h"
#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"
#include "cuts/utils/testing/Test_Database.h"

/**
 * @class CUTS_Dmac_Static_Part
 *
 * Represent a Static portion of a log format
 */

class CUTS_Dmac_Static_Part
{

public:

  // Default constructor
  CUTS_Dmac_Static_Part (void);

  // Destructor
  ~CUTS_Dmac_Static_Part (void);

  /**
   * Find the positions of words of the static parts
   * @param[in] message     the actual log message
   */
  void find_positions (CUTS_DMAC_UTILS::string_vector & message);

  /**
   * Populate static parts from a log messge
   * @param[in] items     The set of items
   */
  void populate_items (CUTS_DMAC_UTILS::string_vector & items);

  /**
   * Insert a log format with the size
   * @param[in] lf_list     The log format words
   * @param[in] current_size    The number of words in the static parts
   */
  void insert_log_format (std::vector <CUTS_Dmac_Log_Format *> & lf_list,
                          int current_size);


private:

  /// Actual items of a static part
  CUTS_DMAC_UTILS::string_vector items_;

  /// The staic part word positions
  std::vector <CUTS_DMAC_UTILS::int_vector> position_lists_;

  /// The log message instances sizes.
  CUTS_DMAC_UTILS::int_vector message_sizes_;

};



#endif /* _CUTS_DMAC_STATIC_PART_H */