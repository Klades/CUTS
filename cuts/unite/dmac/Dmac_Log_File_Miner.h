// $Id: Dmac_Log_File_Miner.h

#ifndef _CUTS_DMAC_LOG_FILE_MINER_H_
#define _CUTS_DMAC_LOG_FILE_MINER_H_


#include "Dmac_Log_Miner.h"
#include "Dmac_export.h"


/**
 * @class CUTS_Dmac_Log_File_Miner
 *
 * Dmac Log_File_Miner class
 */

class CUTS_DMAC_Export CUTS_Dmac_Log_File_Miner : public CUTS_Dmac_Log_Miner
{
public:

 /**
  * Initializing constructor
  * @param [in]   pattern_file    The file containing the frequent sequences
  * @param [in]   data_file       The trace file
  * @param [in]   found_items     Set of log formats found
  */
  CUTS_Dmac_Log_File_Miner (ACE_CString & pattern_file,
                            ACE_CString & data_file,
                            std::vector <CUTS_Dmac_Log_Format *> & found_items);

  /// Destructor
  ~CUTS_Dmac_Log_File_Miner (void);

 /**
   * Extract the relations from log formats
   * @param [in] argc Number of command-line arguments
   */
  virtual void populate_candidates (void);

 /**
   * Create the next dataset
   * @param[in] the round number
   */
  virtual void create_next_dataset (int round);

};

#endif  // !defined _CUTS_DMAC_LOG_FILE_MINER_H_
