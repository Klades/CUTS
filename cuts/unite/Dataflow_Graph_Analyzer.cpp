// $Id$

#include "Dataflow_Graph_Analyzer.h"
#include "Graph_Worker.h"
#include <algorithm>
#include <iostream>
#include <sstream>

//
// CUTS_Dataflow_Graph_Analyzer
//
CUTS_Dataflow_Graph_Analyzer::
CUTS_Dataflow_Graph_Analyzer (CUTS_Dataflow_Graph * g)
: g_ (g),
  repo_ (0)
{
  ACE_NEW_THROW_EX (this->repo_,
                    CUTS_Dataset_Repo (),
                    ACE_bad_alloc ());
}

//
// ~CUTS_Dataflow_Graph_Analyzer
//
CUTS_Dataflow_Graph_Analyzer::
~CUTS_Dataflow_Graph_Analyzer (void)
{

}

//
// get_descendents
//
void CUTS_Dataflow_Graph_Analyzer::get_descendents (
    vertex_descriptor u,
    std::set <vertex_descriptor> & descendents)
{
  // Fill the descendents list for a particular vertex
  CUTS_Unit_Test_Graph_Type::adjacency_iterator ai, ai_end;
  boost::tie (ai, ai_end) = boost::adjacent_vertices (u, g_->graph ());

  for (; ai != ai_end; ++ai)
  {
    descendents.insert (*ai);
    this->get_descendents (*ai, descendents);
  }
}

//
// search_leaf
//
bool CUTS_Dataflow_Graph_Analyzer::search_leaf (vertex_descriptor u)
{
  std::map <int, vertex_descriptor>::iterator it;

  for (it = this->leaves_.begin (); it != this->leaves_.end (); it++)
  {
    if (it->second == u)
      return true;
  }
  return false;
}

//
// eligibility_test
//
bool CUTS_Dataflow_Graph_Analyzer::eligibility_test (
    std::set <vertex_descriptor> & descendents,
    vertex_descriptor candidate,
    vertex_descriptor current_leaf_node)
{
  // The current leaf node is always included
  if (candidate == current_leaf_node)
    return true;

  // If this is a different leaf it should be excluded
  if (this->search_leaf(candidate))
    return false;

  // If it is in the descendent list, we need to include it.
  if (descendents.find (current_leaf_node) != descendents.end ())
    return true;

  return false;
}

//
// initialize
//
void CUTS_Dataflow_Graph_Analyzer::initialize (void)
{
  // Initialize the data structure to keep the colored data graph with
  // all the vertex descriptos
  vertex_iterator iter, iter_end;
  boost::tie(iter, iter_end) = boost::vertices (g_->graph ());

  int i = 0;
  for (; iter != iter_end; iter++)
  {
    std::vector <Node_Status> node_status;
    this->vertex_data_.insert (std::pair <vertex_descriptor, std::vector <Node_Status> > (*iter, node_status));
    if(boost::out_degree (*iter, g_->graph ()) == 0)
    {
      this->leaves_.insert (std::pair <int, vertex_descriptor> (i, *iter));
      i++;
    }
  }

  // Set the labels to not visited state only for the eligible
  // nodes.
  VERTEX_INFO::iterator v_iter;
  for (v_iter = this->vertex_data_.begin ();
       v_iter != this->vertex_data_.end (); v_iter++)
  {
    v_iter->second.assign (i, Init);
    std::map <int, vertex_descriptor>::iterator leaf_iter;
    for (leaf_iter = this->leaves_.begin ();
         leaf_iter != this->leaves_.end (); leaf_iter++)
    {
      std::set <vertex_descriptor> descendents;
      this->get_descendents (v_iter->first, descendents);

      if (this->eligibility_test (descendents, v_iter->first, leaf_iter->second))
      {
        v_iter->second.at(leaf_iter->first) = Not_Visited;
      }
    }
  }
}

//
// analyze
//
void CUTS_Dataflow_Graph_Analyzer::analyze (CUTS_Test_Database & testdata,
                                            ACE_CString & repo_location)
{
  this->initialize ();

  std::map <int, vertex_descriptor>::iterator leaves_iter;

  // For each leaf in the graph create a new graph worker thread and
  // each thread will process the graph independently
  for (leaves_iter = this->leaves_.begin ();
       leaves_iter != this->leaves_.end (); leaves_iter++)
  {
    CUTS_Graph_Worker * worker = 0;
    ACE_NEW_THROW_EX (worker,
                      CUTS_Graph_Worker (this->g_,
                                         this->leaves_,
                                         this->vertex_data_,
                                         testdata,
                                         repo_location,
                                         leaves_iter->first),
                      ACE_bad_alloc ());

    worker->activate ();
    this->workers_.push_back (worker);
  }

  std::vector <CUTS_Graph_Worker *>::iterator it;

  // Wait for all the workers to finish
  for (it = this->workers_.begin (); it != this->workers_.end (); it++)
  {
    (*it)->wait ();
  }
}

//
// join
//
CUTS_Dataset_Repo * CUTS_Dataflow_Graph_Analyzer::join (CUTS_Test_Database & testdata,
                                                        ACE_CString & repo_location)
{
  vertex_descriptor common_vertex;

  // Workers are done, join the dataset repos only if
  // there is a common vertex.
  if (this->find_common_vertex (&common_vertex))
  {
    // Open the repository for the test data.
    if (!this->repo_->open (repo_location, testdata))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to open variable table repo\n")));

    std::vector <CUTS_Graph_Worker *>::iterator it;

    // Attacj each database of each worker to the final joined repo
    for (it = this->workers_.begin ();
         it != this->workers_.end (); it++)
    {
      std::ostringstream temp_str;
      temp_str << "aux_"
               << (*it)->leaf_id ();

      this->repo_->attach_database ((*it)->repo ().repo_name ().c_str (),
                                    temp_str.str ().c_str ());
    }

    // Invoke the join
    this->repo_->join (this->workers_, *(this->g_));

  }
  return this->repo_;
}

//
// find_common_vertex
//
bool CUTS_Dataflow_Graph_Analyzer::
find_common_vertex (vertex_descriptor * common_vertex)
{
  size_t num_workers = this->workers_.size ();

  // In case of one leaf no need to find a common vertex, every vertex is common
  if(num_workers == 1)
    return true;

  // The common vertex should be a member of the sub graph with
  // least number of nodes
  size_t min_size = this->workers_[0]->subgraph_nodes ().size ();;
  size_t min_index = 0;
  for (size_t i = 0; i < num_workers; i++)
  {
    size_t cur_size = this->workers_[i]->subgraph_nodes ().size ();
    if (cur_size <= min_size)
    {
      min_size = cur_size;
      min_index = i;
    }
  }

  // So we compare each vertex in the min sungraph with other
  // different subbraph nodes
  bool found_all = false;
  for (size_t j = 0; j < min_size; j++)
  {
    vertex_descriptor cur_vertex = this->workers_[min_index]->subgraph_nodes ()[j];
    for (size_t k = 0; k < num_workers; k++)
    {
      if (k != min_index)
      {
        std::vector <vertex_descriptor>::iterator it =
          std::find (this->workers_[k]->subgraph_nodes ().begin (),
                     this->workers_[k]->subgraph_nodes ().end (),
                     cur_vertex);

        if (it == this->workers_[k]->subgraph_nodes ().end ())
        {
          found_all = false;
          break;
        }
        else
          found_all = true;
      }
    }

    if (found_all)
    {
      *common_vertex = cur_vertex;
      break;
    }
  }
  return found_all;
}