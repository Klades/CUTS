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
#include "boost/graph/topological_sort.hpp"
#include <algorithm>

#define BELIEF_THRESHOLD  0.90

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
      this->extend_graph (log_formats [lf_pair.first - 1],
                          log_formats [lf_pair.second - 1]);
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
  size_t tp_count = 0;
  size_t fp_count = 0;
  size_t fn_count = 0;

  // Take log format pairs
  size_t size = log_formats.size ();

  // Check whether they are reachable with each other

  std::cout << "Finding Inter Ec Relations" << std::endl
            << "================================================="
            << std::endl;

  const char * file_name = "Dance.knowledge";
  CUTS_DMAC_UTILS::int_double_map knowledge_data;
  this->populate_domain (file_name, knowledge_data);

  for (size_t i = 0; i < size; i++)
  {
    for (size_t j = i + 1; j < size; j++)
    {
      if (i+1 == 98 && j+1 == 135)
        std::cout << "Brak" << std::endl;

      if (log_formats.at (i)->has_similar_execution (log_formats.at (j)))
        continue;

      if (this->is_reachable (log_formats.at (i), log_formats.at (j)))
        continue;

      if (this->is_reachable (log_formats.at (j), log_formats.at (i)))
        continue;

      CUTS_Dmac_Candidate_Relation cand_relation1 (log_formats.at (i),
                                                   log_formats.at (j));

      CUTS_Dmac_Candidate_Relation cand_relation2 (log_formats.at (j),
                                                   log_formats.at (i));

      cand_relation1.populate_cause_effect_vars ();
      cand_relation2.populate_cause_effect_vars ();

      cand_relation1.calculate_belief (knowledge_data);

      cand_relation2.var_evidence_val (cand_relation1.var_evidence_val ());
      cand_relation2.var_evidence_calculated (true);

      cand_relation2.calculate_belief (knowledge_data);

      //cand_relation.set_log_formats (log_formats.at (i), log_formats.at (j));
      //cand_relation.calculate_var_evidence ();
      //cand_relation.calculate_time_evidence ();
      //cand_relation.calculate_belief ();

      /*std::cout << "Trying to connect " << i+1 << " and " << j+1 << std::endl;

      std::cout << "Var Evidence = " << cand_relation1.var_evidence_val () << " , ";
      std::cout << "Time Evidence = " << cand_relation1.time_evidence_val () << "  , ";
      std::cout << "Domain Evidence = " << cand_relation1.domain_evidence_val () << " , ";
      std::cout << "Beleif = " << cand_relation1.belief () << std::endl;

      std::cout << "Trying to connect " << j+1 << " and " << i+1 << std::endl;

      std::cout << "Var Evidence = " << cand_relation2.var_evidence_val () << " , ";
      std::cout << "Time Evidence = " << cand_relation2.time_evidence_val () << "  , ";
      std::cout << "Domain Evidence = " << cand_relation2.domain_evidence_val () << " , ";
      std::cout << "Beleif = " << cand_relation2.belief () << std::endl;*/

      if (cand_relation1.belief () >= cand_relation2.belief ())
      {
        if (cand_relation1.belief () >= BELIEF_THRESHOLD)
        {
          this->extend_graph (cand_relation1.cause_lf (),
                              cand_relation1.effect_lf ());
          std::cout << "Var Evidence = " << cand_relation1.var_evidence_val () << " , ";
          std::cout << "Time Evidence = " << cand_relation1.time_evidence_val () << "  , ";
          std::cout << "Domain Evidence = " << cand_relation1.domain_evidence_val () << " , ";
          std::cout << "Beleif = " << cand_relation1.belief () << std::endl;

          CUTS_DMAC_UTILS::int_double_map::iterator it;
          bool found = false;
          for (it = knowledge_data.begin (); it != knowledge_data.end (); it++)
          {
            bool condition = ((it->first.first) == (cand_relation1.cause_lf ()->id ()))
              && ((it->first.second) == (cand_relation1.effect_lf ()->id ()));
            if (condition)
            {
              tp_count++;
              found = true;
              break;
            }
          }

          if (!found)
            fp_count++;
        }
      }
      else
      {
        if (cand_relation2.belief () >= BELIEF_THRESHOLD)
        {
          /*this->connect_inter_ec_log_formats (cand_relation.cause_lf (),
                                                cand_relation.effect_lf ());*/
          this->extend_graph (cand_relation2.cause_lf (),
                              cand_relation2.effect_lf ());

          std::cout << "Var Evidence = " << cand_relation2.var_evidence_val () << " , ";
          std::cout << "Time Evidence = " << cand_relation2.time_evidence_val () << "  , ";
          std::cout << "Domain Evidence = " << cand_relation2.domain_evidence_val () << " , ";
          std::cout << "Beleif = " << cand_relation2.belief () << std::endl;

          CUTS_DMAC_UTILS::int_double_map::iterator it;
          bool found = false;
          for (it = knowledge_data.begin (); it != knowledge_data.end (); it++)
          {
            bool condition = ((it->first.first) == (cand_relation2.cause_lf ()->id ()))
              && ((it->first.second) == (cand_relation2.effect_lf ()->id ()));
            if (condition)
            {
              tp_count++;
              found = true;
              break;
            }
          }

          if (!found)
            fp_count++;

        }
      }
      this->cand_relations_.push_back (cand_relation1);
      this->cand_relations_.push_back (cand_relation2);
    }
  }

  CUTS_DMAC_UTILS::int_double_map::iterator it;
  bool found = false;
  for (it = knowledge_data.begin (); it != knowledge_data.end (); it++)
  {
    if (!this->is_reachable (log_formats.at (it->first.first - 1),
                            log_formats.at (it->first.second - 1)))
    {
      fn_count++;
      std::cout << "Not Reachable : " << (it->first.first)
                << " and " << it->first.second
                << std::endl;
    }
  }

  std::cout << std::endl << std::endl;
  std::cout << "Statistics " << std::endl;
  std::cout << "============" << std::endl;
  std::cout << "Number of True positives : " << tp_count << std::endl;
  std::cout << "Number of False positives : " << fp_count << std::endl;
  std::cout << "Number of False Negatives :" << fn_count << std::endl;
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

void CUTS_Dmac_Log_Format_Graph::print_candidate_relations (void)
{
  std::vector <CUTS_Dmac_Candidate_Relation>::iterator it;

  for (it = this->cand_relations_.begin ();
       it!= this->cand_relations_.end (); it++)
  {
    std::cout << it->cause_lf ()->id () << "-->" << it->effect_lf ()->id ()
      <<" evidence1 = " << it->var_evidence_val () << std::endl;
  }
}

bool CUTS_Dmac_Log_Format_Graph::
is_reachable (CUTS_Dmac_Log_Format * lf1,
              CUTS_Dmac_Log_Format * lf2)
{
  std::stringstream lf1_id;
  std::stringstream lf2_id;

  lf1_id << "LF" << lf1->id ();
  lf2_id << "LF" << lf2->id ();

  ACE_CString lf1_str (lf1_id.str ().c_str ());
  ACE_CString lf2_str (lf2_id.str ().c_str ());

  // First find the vertices of the two log formats.

  vertex_descriptor lf1_vertex = 0;
  vertex_descriptor lf2_vertex = 0;
  if (this->vertices_.find (lf1_str, lf1_vertex) != 0)
  {
    return false;
  }

  if (this->vertices_.find (lf2_str, lf2_vertex) != 0)
  {
    return false;
  }

  std::vector <bool> mark (boost::num_vertices (this->graph_), false);

  std::vector <vertex_descriptor> s;
  mark [lf1_vertex] = true;
  s.push_back (lf1_vertex);

  while (!s.empty ())
  {
    vertex_descriptor temp_vertex = s.back ();
    s.pop_back ();

    CUTS_Dmac_Log_Format_Graph_Type::adjacency_iterator ai, ai_end;
    boost::tie(ai, ai_end) = boost::adjacent_vertices (temp_vertex, this->graph_);

    for (; ai != ai_end; ++ai)
    {
      if (!mark [*ai])
      {
        mark [*ai] = true;
        s.push_back (*ai);
      }
    }
  }

  if (mark [lf2_vertex])
    return true;
  else
    return false;
}

//
// extend_graph
//
void CUTS_Dmac_Log_Format_Graph::
extend_graph (CUTS_Dmac_Log_Format * cause_lf,
              CUTS_Dmac_Log_Format * effect_lf)
{
  std::stringstream cause_lf_id;
  std::stringstream effect_lf_id;

  cause_lf_id << "LF" << cause_lf->id ();
  effect_lf_id << "LF" << effect_lf->id ();

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
  // in either direction

  edge_descriptor e;
  bool found1;
  bool found2;

  boost::tie (e, found1) = boost::edge (cause_vertex, effect_vertex, this->graph_);
  boost::tie (e, found2) = boost::edge (effect_vertex, cause_vertex, this->graph_);

  if ((!found1) && (!found2))
  {
    // Creates a new edge add to the graph and extract the variable
    // relations also.
    boost::add_edge (cause_vertex, effect_vertex, this->graph_);
    cause_lf->extract_variable_relations (effect_lf);
    std::cout << cause_lf->id () << "-->" << effect_lf->id ()
              << std::endl;
  }
}


void CUTS_Dmac_Log_Format_Graph::
connect_inter_ec_log_formats (CUTS_Dmac_Log_Format * cause_lf,
                              CUTS_Dmac_Log_Format * effect_lf)
{
  std::stringstream cause_lf_id;
  std::stringstream effect_lf_id;

  cause_lf_id << "LF" << cause_lf->id ();
  effect_lf_id << "LF" << effect_lf->id ();

  ACE_CString src (cause_lf_id.str ().c_str ());
  ACE_CString des (effect_lf_id.str ().c_str ());

  // First check whether this log format is already added.
  vertex_descriptor cause_vertex = 0;
  vertex_descriptor effect_vertex = 0;

  if ((this->vertices_.find (src, cause_vertex) == 0) &&
      (this->vertices_.find (des, effect_vertex) == 0))
  {
    boost::add_edge (cause_vertex, effect_vertex, this->graph_);
    cause_lf->extract_variable_relations (effect_lf);
  }
  else
  {
    std::cout << "Cannot find the vertices, something went wrong"
              << std::endl;
  }
}


void CUTS_Dmac_Log_Format_Graph::
populate_domain (const char * file_name,
                 CUTS_DMAC_UTILS::int_double_map & knowledge)
{
  std::ifstream knowledge_stream (file_name);
  if (knowledge_stream.is_open ())
  {
    while (knowledge_stream.good ())
    {
      std::string line;
      std::getline (knowledge_stream, line);

      std::string delimiters (" ");
      std::vector <std::string> tokens;
      std::string::size_type lastPos = line.find_first_not_of (delimiters, 0);
      std::string::size_type pos = line.find_first_of (delimiters, lastPos);

      while (std::string::npos != pos || std::string::npos != lastPos)
      {
        std::string item = line.substr (lastPos, pos - lastPos);
        tokens.push_back (item);
        lastPos = line.find_first_not_of (delimiters, pos);
        pos = line.find_first_of (delimiters, lastPos);
      }

      std::pair <int, int> lf_ids;

      lf_ids.first = ACE_OS::atoi (tokens.at (0).c_str ());
      lf_ids.second = ACE_OS::atoi (tokens.at (1).c_str ());
      double evi = ACE_OS::atof (tokens.at (2).c_str ());

      knowledge.insert (std::pair < std::pair <int, int>, double> (lf_ids, evi));

    }
  }
  knowledge_stream.close ();
}