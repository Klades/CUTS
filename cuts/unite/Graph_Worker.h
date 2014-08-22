// $Id$
#ifndef _CUTS_GRAPH_WORKER_H_
#define _CUTS_GRAPH_WORKER_H_

#include "Dataflow_Graph.h"
#include "Dataflow_Graph_Analyzer.h"
#include "Dataset_Repo.h"
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Task.h"
#include "ace/SString.h"
#include <map>
#include <vector>

// Forward declerationd
class CUTS_Dataflow_Graph_Analyzer;

// Type definitions
typedef CUTS_Dataflow_Graph::vertex_descriptor vertex_descriptor;

typedef CUTS_Dataflow_Graph::vertex_iterator vertex_iterator;

// This class represents a graph worker thread, a new thread will be
// created for each new leaf node
class CUTS_UNITE_Export CUTS_Graph_Worker : public ACE_Task_Base
{
public:

  friend class CUTS_Dataset_Repo;

  // Initializing constructor
  CUTS_Graph_Worker (CUTS_Dataflow_Graph * g,
                     std::map <int, vertex_descriptor> & leaves,
                     CUTS_Dataflow_Graph_Analyzer::VERTEX_INFO & vertex_data,
                     CUTS_Test_Database & testdata,
                     ACE_CString & repo_location,
                     int leaf_id);

  // Destructor
  ~CUTS_Graph_Worker (void);

  // The svc method will be invoked in the new thread
  virtual int svc (void);

  // Prints the associated vertices with the leaf node
  void print_vertices (void);

  // Returns the asscoaited repo with the worker
  CUTS_Dataset_Repo & repo (void);

  // Return a reference to the list of subgraph nodes for
  // this leaf node
  std::vector <vertex_descriptor> & subgraph_nodes (void);

  // Return the unique leaf id
  int leaf_id (void);


private:

  // Get the descendent list for this leaf node
  void get_descendents (vertex_descriptor u,
                        std::set <vertex_descriptor> & descendents);

  // Check whether the given node has descendents
  bool descendents_test (vertex_descriptor cur_node);

  // Check whether to termonate the algorithm or not
  bool terminate (void);

  // Store the nodes in the subgraph in topologoical order
  void get_subgraph_process_order (void);

  // The original dataflow model
  CUTS_Dataflow_Graph  * g_;

  // The leaves map
  std::map <int, vertex_descriptor> & leaves_;

  // All the vertex and associated meta data
  CUTS_Dataflow_Graph_Analyzer::VERTEX_INFO & vertex_data_;

  // The system execution trace data
  CUTS_Test_Database & testdata_;

  // The vtable location
  ACE_CString & repo_location_;

  // The id of the leaf, associated to this worker
  int leaf_id_;

  // The associated subgraph nodes
  std::vector <vertex_descriptor> subgraph_nodes_;

  // The sub repo for this subgraph
  CUTS_Dataset_Repo repo_;

};

#endif  // !defined _CUTS_GRAPH_WORKER_H_