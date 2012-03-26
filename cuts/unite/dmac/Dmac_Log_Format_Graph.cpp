#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/graphviz.hpp>
#include "Dmac_Log_Format_Graph.h"
#include "ace/OS_Memory.h"
#include "ace/CORBA_macros.h"

//
// CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::CUTS_Dmac_Log_Format_Graph ()
{

}

//
// ~CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::~CUTS_Dmac_Log_Format_Graph (void)
{

}

//
// extend_graph
//
void CUTS_Dmac_Log_Format_Graph::
extend_graph (std::vector <CUTS_Dmac_Log_Format *> & log_formats,
              CUTS_Dmac_Execution * execution)
{
  // Take each adjacent pair in the order of log formats in the
  // system execution trace

  for (int i = 0; i < (int)(execution->lf_order_list_.size () - 1); i++)
  {
    CUTS_DMAC_UTILS::int_pair lf_pair (execution->lf_order_list_ [i],
                                       execution->lf_order_list_ [i+1]);

    if (this->check_for_addition (lf_pair, execution->lf_order_list_))
    {
      CUTS_Dmac_Log_Format * cause_lf = 0;
      CUTS_Dmac_Log_Format * effect_lf = 0;
      std::stringstream cause_lf_id;
      std::stringstream effect_lf_id;

      cause_lf_id << "LF" << lf_pair.first;
      effect_lf_id << "LF" << lf_pair.second;

      ACE_CString src (cause_lf_id.str ().c_str ());
      ACE_CString des (effect_lf_id.str ().c_str ());

      // First check whether this log format is already added.

      vertex_descriptor cause_vertex = 0;
      if (this->vertices_.find (src, cause_vertex) == 0)
        cause_lf = boost::get (CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (),
                               this->graph_,
                               cause_vertex);
      else
      {
        // Create the vertex and add it to the graph

        cause_lf = log_formats [lf_pair.first - 1];
        cause_vertex = boost::add_vertex (this->graph_);
        this->vertices_.bind (src, cause_vertex);

        // Initialize the vertex's traits.
        boost::put (boost::vertex_name_t (), this->graph_, cause_vertex, src);
        boost::put (CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (),
                    this->graph_,
                    cause_vertex,
                    cause_lf);
      }

      // Do the same thing for Effect vertex.

      vertex_descriptor effect_vertex = 0;
      if (this->vertices_.find (des, effect_vertex) == 0)
        effect_lf = boost::get (CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (),
                                this->graph_,
                                effect_vertex);
      else
      {
        effect_lf = log_formats [lf_pair.second -1];
        effect_vertex = boost::add_vertex (this->graph_);
        this->vertices_.bind (des, effect_vertex);

        // Initialize the vertex's traits.
        boost::put (boost::vertex_name_t (), this->graph_, effect_vertex, des);
        boost::put (CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (),
                    this->graph_,
                    effect_vertex,
                    effect_lf);
      }

      // First check whether the edge is already in the graph

      edge_descriptor e;
      bool found;

      boost::tie (e, found) = boost::edge (cause_vertex, effect_vertex, this->graph_);

      if (!found)
      {
        // Creates a new edge add to the graph and extract the variable
        // relations also.
        boost::add_edge (cause_vertex, effect_vertex, this->graph_);
        cause_lf->extract_variable_relations (effect_lf);
      }
    }
  }
}

//
// check_for_addition
//
bool CUTS_Dmac_Log_Format_Graph::
check_for_addition (CUTS_DMAC_UTILS::int_pair & pair,
                    CUTS_DMAC_UTILS::int_vector & lf_order_list)
{
  int first_index = -1;
  int second_index = -1;

  for (int i = 0; i < (int)lf_order_list.size (); i++)
  {
    // Follwing two conditons make sure we are not forming
    // cycles.
    if ((first_index < 0) && (lf_order_list [i] == pair.first))
      first_index = i;

    if ((second_index < 0) && (lf_order_list [i] == pair.second))
      second_index = i;

    if ((first_index >= 0) && (second_index >= 0))
      return (first_index < second_index);
  }

  return false;
}