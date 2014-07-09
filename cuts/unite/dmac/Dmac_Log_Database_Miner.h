// $Id: Dmac_Log_Database_Miner.h

#ifndef _CUTS_DMAC_LOG_DATABASE_MINER_H_
#define _CUTS_DMAC_LOG_DATABASE_MINER_H_


#include "Dmac_Log_Miner.h"
#include "cuts/utils/testing/Test_Database.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Log_Database_Miner
 *
 * Dmac Log_Database_Miner class
 */

class CUTS_DMAC_Export CUTS_Dmac_Log_Database_Miner : public CUTS_Dmac_Log_Miner
{
public:

  /// Default constructor
  CUTS_Dmac_Log_Database_Miner (ACE_CString & pattern_file,
                                ACE_CString & data_file,
                                std::vector <CUTS_Dmac_Log_Format *> & found_items,
                                CUTS_Test_Database & testdata);

  /// Destructor
  ~CUTS_Dmac_Log_Database_Miner (void);

 /**
   * Mine the dataset and find log formats
   *
   * @retval          1       If the mining process is successfull.
   * @retval          -1      If it fails.
   */

 /**
   * Populate the candidate log formats
   */
  virtual void populate_candidates (void);

  /**
   * Create the next dataset
   * @param[in] the round number
   */
  virtual void create_next_dataset (int round);


private:

  // The system execution trace database
  CUTS_Test_Database & testdata_;


};

#endif  // !defined _CUTS_DMAC_LOG_DATABASE_MINER_H_
