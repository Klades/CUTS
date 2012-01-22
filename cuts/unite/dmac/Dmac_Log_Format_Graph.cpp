#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/graphviz.hpp>
#include "Dmac_Log_Format_Graph.h"


//
// which_causes_which
//
template <class EdgeIter, class LF_Graph_Type>
void which_causes_which (EdgeIter first, EdgeIter last, const LF_Graph_Type & graph)
{
  // Creat the graph and print it

  ro_vertex_list NameMap;
  NameMap = get (CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (), graph);

  typedef typename boost::property_traits <ro_vertex_list>
    ::value_type NameType;

  NameType src_name, targ_name;

  while (first != last)
  {
    std::cout << std::endl;
    src_name = boost::get (NameMap, source (*first, graph));
    targ_name = boost::get (NameMap, target (*first, graph));
      std::cout << src_name << "->"
        << targ_name << std::endl;
      ++first;
  }
  std::cout << std::endl;
}

//
// CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::CUTS_Dmac_Log_Format_Graph (
    CUTS_DMAC_UTILS::int_vector & history,
    std::vector <CUTS_Dmac_Log_Format *> & lf_list)
: history_ (history),
  lf_list_ (lf_list)
{

}

//
// ~CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::~CUTS_Dmac_Log_Format_Graph (void)
{

}

//
// build_graph
//
void CUTS_Dmac_Log_Format_Graph::build_graph (CUTS_Dmac_Execution * execution)
{
  this->VERTICES_ = get(CUTS_Dmac_Log_Format_Graph_Traits::log_format_t (),
                        this->graph_);

  // Take each adjacent pair in the order of log formats in the
  // system execution trace

  for (int i = 0; i < (int)(this->history_.size () - 1); i++)
  {
    CUTS_DMAC_UTILS::int_pair lf_pair (this->history_ [i],
                                       this->history_ [i+1]);

    if (this->check_for_addition (lf_pair))
    {
      // Relation is safe addition and it does not form cycles.
      boost::add_edge (lf_pair.first, lf_pair.second, this->graph_);

      this->lf_list_ [lf_pair.first - 1]->extract_variable_relations (
        this->lf_list_ [lf_pair.second - 1], execution);

      std::stringstream lfstring1;
      std::stringstream lfstring2;

      lfstring1 << "LF" << lf_pair.first;
      lfstring2 << "LF" << lf_pair.second;

      boost::put (this->VERTICES_, lf_pair.first, lfstring1.str ().c_str ());
      boost::put (this->VERTICES_, lf_pair.second, lfstring2.str ().c_str ());
    }
  }
  // Add the edge to the grph
  which_causes_which (edges (this->graph_).first,
                      edges (this->graph_).second,
                      this->graph_);

}

//
// check_for_addition
//
bool CUTS_Dmac_Log_Format_Graph::check_for_addition (CUTS_DMAC_UTILS::int_pair & pair)
{
  int first_index = -1;
  int second_index = -1;

  // If this relation is already added then no need
  // to add it.

  if (this->already_contained (pair))
    return false;

  for (int i = 0; i < (int)this->history_.size (); i++)
  {
    // Follwing two conditons make sure we are not forming
    // cycles.
    if ((first_index < 0) && (this->history_ [i] == pair.first))
      first_index = i;

    if ((second_index < 0) && (this->history_ [i] == pair.second))
      second_index = i;

    if ((first_index >= 0) && (second_index >= 0))
      return (first_index < second_index);
  }

  return false;
}

//
// already_contained
//
bool CUTS_Dmac_Log_Format_Graph::already_contained (CUTS_DMAC_UTILS::int_pair & pair)
{
  std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it;

  for (it = this->edge_set_.begin (); it != this->edge_set_.end (); it++)
  {
    if ((pair.first == it->first) && (pair.second == it->second))
      return true;
  }

  this->edge_set_.push_back (pair);
  return false;
}

//
// compare
//
bool CUTS_Dmac_Log_Format_Graph::compare (CUTS_Dmac_Log_Format_Graph & graph)
{
  // Compare two graphs and determine whether they contain the same
  // log formats and same set of relations

  if (this->edge_set_.size () !=
        graph.edge_set_.size ())
    return false;

  std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it1;
  std::vector <CUTS_DMAC_UTILS::int_pair>::iterator it2;

  for (it1 = graph.edge_set_.begin ();
        it1 != graph.edge_set_.end (); it1++)
  {
    for (it2 = this->edge_set_.begin ();
          it2 != this->edge_set_.end (); it2++)
    {
      if ((it1->first != it2->first) ||
            (it1->second != it2->second))
        return false;
    }
  }
  return true;
}