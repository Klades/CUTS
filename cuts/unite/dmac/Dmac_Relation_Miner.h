// $Id: Dmac_Relation_Miner.h

#ifndef _CUTS_DMAC_RELATION_MINER_H_
#define _CUTS_DMAC_RELATION_MINER_H_

#include <iostream>
#include "ace/SString.h"
#include <algorithm>
#include <sstream>
#include "Dmac_Utils.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Log_Format_Graph_Builder.h"
#include "cuts/utils/testing/Test_Database.h"
#include "Dmac_export.h"


/**
 * @class CUTS_Dmac_Relation_Miner
 *
 * Dmac Relation Miner class
 */

class CUTS_DMAC_Export CUTS_Dmac_Relation_Miner
{
public:

  /// Initializing constructor
  CUTS_Dmac_Relation_Miner (ACE_CString & name,
                            CUTS_Test_Database & testdata,
                            std::vector <CUTS_Dmac_Log_Format *> & log_formats);

  /// Destructor
  ~CUTS_Dmac_Relation_Miner (void);

  /**
   * Mine the relations using the found log formats
   */
  void mine_relations (void);

  /**
   *  Set the delimitters
   *  @param[in]    Set of delimitters
   */
  void delims (std::string delims);


private:

  // Extract the relations among log formats
  void find_relations (void);

  // Generate the datagraph file as disjoint datagraph for
  // each execution context
  void generate_datagraph_file (void);

  // Name of the datagraph file
  ACE_CString & name_;

  CUTS_Test_Database & testdata_;

  // Tota number of log messages in the trace
  long total_records_;

  // Final log formats
  std::vector <CUTS_Dmac_Log_Format *> & final_log_formats_;

  CUTS_Dmac_Log_Format_Graph graph_;

  // Delimitters
  std::string delims_;

};

#endif  // !defined _CUTS_DMAC_RELATION_MINER_H_
