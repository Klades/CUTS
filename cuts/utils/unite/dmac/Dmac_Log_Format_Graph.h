#ifndef _CUTS_DMAC_LOG_FORMAT_GRAPH_H_
#define _CUTS_DMAC_LOG_FORMAT_GRAPH_H_

#include "boost/graph/adjacency_list.hpp"
#include <string>
#include "Dmac_Log_Format.h"


/**
 * @class CUTS_Dmac_Log_Format_Graph_Traits
 *
 * Trait class for CUTS_Dmac_Log_Format_Graph
 */

class CUTS_Dmac_Log_Format_Graph_Traits
{
public:
  struct log_format_t
  {
    typedef boost::vertex_property_tag kind;
  };

  typedef boost::property<log_format_t, std::string> property_type;

};

  typedef boost::adjacency_list <boost::vecS,
                                 boost::vecS,
                                 boost::directedS,
                                 CUTS_Dmac_Log_Format_Graph_Traits::property_type>
                                 LF_Graph_Type;

  typedef boost::property_map <LF_Graph_Type,
                               CUTS_Dmac_Log_Format_Graph_Traits::log_format_t>::type vertex_list;

  typedef boost::property_map <LF_Graph_Type,
                               CUTS_Dmac_Log_Format_Graph_Traits::log_format_t>::const_type ro_vertex_list;


/**
 * @class CUTS_Dmac_Log_Format_Graph
 *
 * Represent the Dataflow model
 */

  class CUTS_Dmac_Log_Format_Graph
{
public:

  /// Type definition to the vertex descriptor
  typedef boost::graph_traits <LF_Graph_Type>::vertex_descriptor vertex_descriptor;

  /// Type definition to the vertex descriptor
  typedef boost::graph_traits <LF_Graph_Type>::vertex_iterator vertex_iterator;

  /// Type definition of the edge descriptor
  typedef boost::graph_traits <LF_Graph_Type>::edge_descriptor edge_descriptor;

  /**
   * Initializing constructor
   *
   * @param[in]     history       If of the log formats in the order of the trace
   * @param[in]     lf_list       Set of log formats
   */
  CUTS_Dmac_Log_Format_Graph (CUTS_DMAC_UTILS::int_vector & history,
                              std::vector <CUTS_Dmac_Log_Format *> & lf_list);

  /// Desturctor
  ~CUTS_Dmac_Log_Format_Graph (void);

  /**
   * Build the dataflow graph
   *
   * @param[in]     execution   execution for which we are building the graph
   */
  void build_graph (CUTS_Dmac_Execution * execution);


private:

  // The dataflow graph
  LF_Graph_Type graph_;

  // The history of the execution in terms of log format
  CUTS_DMAC_UTILS::int_vector & history_;

  // The identified log format list
  std::vector <CUTS_Dmac_Log_Format *> & lf_list_;

  // The relation set in the graph
  std::vector <CUTS_DMAC_UTILS::int_pair> edge_set_;

  // The vertices in the graph
  vertex_list VERTICES_;

  // Check whether this relation need to be added to the graph
  bool check_for_addition (CUTS_DMAC_UTILS::int_pair & pair);

  // Check whether this relation is already contained in the graph
  bool already_contained (CUTS_DMAC_UTILS::int_pair & pair);

  // Compare two graphs
  bool compare (CUTS_Dmac_Log_Format_Graph & graph);

};

#endif  // !defined _CUTS_DMAC_LOG_FORMAT_GRAPH_H_