#include "Graph_Worker.h"
#include <sstream>
#include <iostream>

//
// CUTS_Graph_Worker
//
CUTS_Graph_Worker::CUTS_Graph_Worker (
    CUTS_Dataflow_Graph * g,
    std::map <int, vertex_descriptor> & leaves,
    CUTS_Dataflow_Graph_Analyzer::VERTEX_INFO & vertex_data,
    CUTS_Test_Database & testdata,
    ACE_CString & repo_location,
    int leaf_id)
: g_ (g),
  leaves_ (leaves),
  vertex_data_ (vertex_data),
  testdata_ (testdata),
  repo_location_ (repo_location),
  leaf_id_ (leaf_id)
{

}

//
// ~CUTS_Graph_Worker
//
CUTS_Graph_Worker::~CUTS_Graph_Worker (void)
{
}

//
// get_descendents
//
void CUTS_Graph_Worker::get_descendents (
    vertex_descriptor u,
    std::set <vertex_descriptor> & descendents)
{
  CUTS_Unit_Test_Graph_Type::adjacency_iterator ai, ai_end;
  boost::tie (ai, ai_end) = boost::adjacent_vertices (u, g_->graph ());

  for (; ai != ai_end; ++ai)
  {
    descendents.insert (*ai);
    this->get_descendents (*ai, descendents);
  }
}

//
// descendents_test
//
bool CUTS_Graph_Worker::descendents_test (vertex_descriptor cur_node)
{
  if (this->vertex_data_ [cur_node].at (this->leaf_id_) !=
    CUTS_Dataflow_Graph_Analyzer::Not_Visited)
    return false;

  std::set <vertex_descriptor> descendents;
  this->get_descendents (cur_node, descendents);

  std::set <vertex_descriptor>::iterator it;

  for (it = descendents.begin (); it != descendents.end (); it++)
  {
    if(this->vertex_data_[*it].at(this->leaf_id_) ==
      CUTS_Dataflow_Graph_Analyzer::Not_Visited)
      return false;
  }
  return true;
}

//
// terminate
//
bool CUTS_Graph_Worker::terminate (void)
{
  CUTS_Dataflow_Graph_Analyzer::VERTEX_INFO::iterator it;

  for (it = this->vertex_data_.begin (); it != this->vertex_data_.end (); it++)
  {
    if (it->second [this->leaf_id_] ==
      CUTS_Dataflow_Graph_Analyzer::Not_Visited)
    {
      return false;
    }
  }
  return true;
}

//
// get_subgraph_process_order
//
void CUTS_Graph_Worker::get_subgraph_process_order (void)
{
  if (this->terminate ())
    return;

  CUTS_Dataflow_Graph_Analyzer::VERTEX_INFO::iterator it;

  for (it = this->vertex_data_.begin (); it != this->vertex_data_.end (); it++)
  {
    if (this->descendents_test (it->first))
    {
      this->subgraph_nodes_.push_back (it->first);
      it->second [this->leaf_id_] = CUTS_Dataflow_Graph_Analyzer::Visited;
      this->get_subgraph_process_order ();
      break;
    }
  }
}

//
// print_vertices
//
void CUTS_Graph_Worker::print_vertices (void)
{
  std::vector <vertex_descriptor>::iterator it;

  for (it = this->subgraph_nodes_.begin ();
       it != this->subgraph_nodes_.end (); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

//
// svc
//
int CUTS_Graph_Worker::svc (void)
{
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) - Graph worker running \n")));

  this->get_subgraph_process_order ();

  this->repo_.graph_worker (this);

  // Open the repository for the test data.
  if (!this->repo_.open (this->repo_location_, this->testdata_, this->leaf_id_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open variable table repo\n")),
                       -1);
  // Time the evaluation operation.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - constructing variable table; please wait...\n")));

  // Construct the variable table for the log format subgraph.
  if (!this->repo_.insert (this->g_, this->subgraph_nodes_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to construct variable table\n")),
                         -1);

  this->repo_.close ();

  return 0;
}

//
// repo
//
CUTS_Dataset_Repo & CUTS_Graph_Worker::repo (void)
{
  return this->repo_;
}

//
// subgraph_nodes
//
std::vector <vertex_descriptor> &
CUTS_Graph_Worker::subgraph_nodes (void)
{
  return this->subgraph_nodes_;
}

//
// leaf_id
//
int CUTS_Graph_Worker::leaf_id (void)
{
  return this->leaf_id_;
}