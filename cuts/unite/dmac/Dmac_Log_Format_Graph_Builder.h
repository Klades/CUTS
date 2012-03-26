// $Id:

#ifndef _CUTS_DMAC_LOG_FORMAT_GRAPH_BUILDER_H_
#define _CUTS_DMAC_LOG_FORMAT_GRAPH_BUILDER_H_

#include "Dmac_Log_Format_Graph.h"
#include "cuts/utils/testing/Test_Database.h"


class CUTS_Dmac_Log_Format_Graph_Builder
{
public:
  /// Default Constructor
  CUTS_Dmac_Log_Format_Graph_Builder (void);

  /// Destructor
  ~CUTS_Dmac_Log_Format_Graph_Builder (void);

  /**
   * build
   *
   * @param[in]     graph         The log format graph
   * @param[in]     testdata      The system execution trace.
   * @param[in]     log_formats   The final log formats
   * @return      Whther the construction succeed or not.
   */
  bool build (CUTS_Dmac_Log_Format_Graph & graph,
              CUTS_Test_Database & testdata,
              std::vector <CUTS_Dmac_Log_Format *> & log_formats);

};

#endif