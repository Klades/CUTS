#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/connected_components.hpp>
#include "Dmac_Log_Format_Graph.h"
#include "ace/OS_Memory.h"
#include "ace/CORBA_macros.h"
#include "cuts/Auto_Functor_T.h"

//
// CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::
CUTS_Dmac_Log_Format_Graph ()
{

}

//
// ~CUTS_Dmac_Log_Format_Graph
//
CUTS_Dmac_Log_Format_Graph::
~CUTS_Dmac_Log_Format_Graph (void)
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

//
// find_inter_ec_relations
//
void CUTS_Dmac_Log_Format_Graph::
find_inter_ec_relations (std::vector<CUTS_Dmac_Log_Format*> & log_formats,
                         CUTS_Test_Database & testdata)
{
  // Take log format pairs
  size_t size = log_formats.size ();

  // Check whether they are reachable with each other

  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = i + 1; j < size; j++)
    {
      //std::cout << "Comparing " << i << " and " << j << std::endl;
      if (log_formats.at (i)->is_reachable (log_formats.at (j)))
        continue;

      //std::cout << "Comparing " << j << " and " << i << std::endl;
      if (log_formats.at (j)->is_reachable (log_formats.at (i)))
        continue;

      corelation_result result;
      this->check_corelation (log_formats [i], log_formats [j], testdata, result);

      if (result.corelated)
      {
        std::cout << i+1 << " and " << j+1 << " are related." << std::endl;
        if (result.prob1 >= result.prob2)
        {
          log_formats [i]->extract_variable_relations (log_formats [j]);
          std::cout << i+1 << " Cause " << j+1 << std::endl;
        }
        else
        {
          log_formats [j]->extract_variable_relations (log_formats [i]);
          std::cout << j+1 << " Cause " << i+1 << std::endl;
        }
      }
    }
  }
}

//
// check_corelation
//
void CUTS_Dmac_Log_Format_Graph::
check_corelation (CUTS_Dmac_Log_Format * lf1,
                  CUTS_Dmac_Log_Format * lf2,
                  CUTS_Test_Database & testdata,
                  corelation_result & result)
{
  // First find all the time values of all the
  // instances of lf1 and lf2.

  ADBC::SQLite::Query * query = testdata.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  std::ostringstream sqlstr;

  sqlstr << "SELECT lid, timeofday, message FROM cuts_logging ORDER BY lid";

  ADBC::SQLite::Record * record =
    &query->execute (sqlstr.str ().c_str ());

  char message[10000];
  std::string delims (" \t\n");

  std::vector <double> lf1_time_records;
  std::vector <double> lf2_time_records;

  for ( ; !record->done (); record->advance ())
  {
    CUTS_DMAC_UTILS::string_vector trace_items;
    record->get_data (2, message, sizeof (message));
    std::string message_str (message);
    CUTS_DMAC_UTILS::tokenize (message_str,
                               trace_items,
                               delims);

    if (CUTS_DMAC_UTILS::match_log_format (trace_items, lf1->log_format_items ()))
    {
      ACE_Date_Time date_time;
      record->get_data (1, date_time);
      double timeval = CUTS_DMAC_UTILS::get_seconds_since_1970 (date_time);
      lf1_time_records.push_back (timeval);
    }
    else if (CUTS_DMAC_UTILS::match_log_format (trace_items, lf2->log_format_items ()))
    {
      ACE_Date_Time date_time;
      record->get_data (1, date_time);
      double timeval = CUTS_DMAC_UTILS::get_seconds_since_1970 (date_time);
      lf2_time_records.push_back (timeval);
    }
  }

  record->reset ();

  // Now calculate the cooccurence probabilities. This logic is based
  // on the paper written by Jian-Guang LOU et al on "Mining Dependency in
  // Distributed Systems through Unstructured Logs Analysis"

  result.prob1 = this->calculate_probability (lf1_time_records, lf2_time_records);
  result.prob2 = this->calculate_probability (lf2_time_records, lf1_time_records);

  if (result.prob1 >= 0.5 || result.prob2 >= 0.5)
    result.corelated = true;
  else
    result.corelated = false;
}

//
// calculate_probability
//
double CUTS_Dmac_Log_Format_Graph::
calculate_probability (std::vector <double> & lf1_time_records,
                       std::vector <double> & lf2_time_records)
{
  std::vector <double>::iterator it1;
  std::vector <double>::iterator it2;
  std::vector <double>::iterator begin1 = lf1_time_records.begin ();
  std::vector <double>::iterator end1 = lf1_time_records.end ();
  std::vector <double>::iterator begin2 = lf2_time_records.begin ();
  std::vector <double>::iterator end2 = lf2_time_records.end ();
  size_t count = 0;
  size_t total = lf1_time_records.size ();

  for (it1 = begin1; it1 != end1; it1++)
  {
    for (it2 = begin2; it2 != end2; it2++)
    {
      if (std::abs ((*it1) - (*it2)) < 0.1)
      {
        count++;
        break;
      }
    }
  }

  return (double)((double)count/(double)total);
}