// $Id: Dmac_Execution.h

#ifndef _CUTS_DMAC_EXECUTION_H_
#define _CUTS_DMAC_EXECUTION_H_

#include <string>
#include "cuts/utils/testing/Test_Database.h"
#include "adbc/SQLite/Connection.h"
#include "Dmac_Log_Format.h"
#include "Dmac_Utils.h"
#include "Dmac_export.h"

/**
 * @class CUTS_Dmac_Execution
 *
 * Represents and execution context.
 */

class CUTS_Dmac_Log_Format_Graph;

class CUTS_DMAC_Export CUTS_Dmac_Execution
{
public:

  /**
   * Initializing constructor
   *
   * @param[in]   host_name         Name of the machine the trace was gnerated
   * @param[in]   thread_id         The execution thread id
   * @parma[in]   test_data         The system excution trace
   * @param[in]   final_patterns_   list identified log formats
   */

  CUTS_Dmac_Execution (ACE_CString host_name,
                       int thread_id,
                       CUTS_Test_Database & test_data,
                       std::vector <CUTS_Dmac_Log_Format *> & final_patterns_);

  // Destructor
  ~CUTS_Dmac_Execution (void);

  /**
   * Get thread_id
   *
   * @return   the thread_id of the execution
   */
  int thread_id (void);

  /**
   * Get host_name
   *
   * @return    the host_name of the execution
   */
  ACE_CString host_name (void);

  /**
   * Create the execution order in terms of log formats
   *
   */
  void create_order_list (void);

  /**
   * Double equal operator
   *
   * @param[in]   execution
   * @return      Flag, whether the execution are the same
   *
   */
  bool operator == (CUTS_Dmac_Execution & execution);

  /**
   * Set the delimitters
   * @param[in]   delims
   *
   */
  void delims (std::string delims);

  friend class CUTS_Dmac_Log_Format_Graph;


private:

  // The name of the host generated the trace
  ACE_CString host_name_;

  // The id of the thread generating the trace
  int thread_id_;

  // The central database stroring the data
  CUTS_Test_Database & test_data_;

  // Delimitters to seperate the words
  std::string delims_;

  // The set of identified log formats
  std::vector <CUTS_Dmac_Log_Format *> & final_patterns_;

  // Execution history in the order of log formats
  CUTS_DMAC_UTILS::int_vector lf_order_list_;

};

#endif  // !defined _CUTS_DMAC_EXECUTION_H_