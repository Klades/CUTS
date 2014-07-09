// $Id$
#ifndef _CUTS_DATAFLOW_GRAPH_ANALYZER_H_
#define _CUTS_DATAFLOW_GRAPH_ANALYZER_H_

#include "Dataflow_Graph.h"
#include "ace/CORBA_macros.h"
#include "cuts/utils/testing/Test_Database.h"
#include "Dataset_Repo.h"
#include <map>
#include <vector>

// Forwrd decelrations
class CUTS_Graph_Worker;

/**
 * @class CUTS_Dataflow_Graph_Analyzer
 *
 * Implements the functionality for working on dataflow graph
 */
class CUTS_UNITE_Export CUTS_Dataflow_Graph_Analyzer
{
public:

  // Different coloring for graph nodes
  enum Node_Status {Init, Not_Visited, Visited};

  /// Type definitions
  typedef CUTS_Dataflow_Graph::vertex_descriptor vertex_descriptor;

  typedef CUTS_Dataflow_Graph::vertex_iterator vertex_iterator;

  typedef std::map <vertex_descriptor, std::vector <Node_Status> > VERTEX_INFO;

   /**
   * Initializing constructor
   *
   * @param[in]     g    The dataflow graph
   */
  CUTS_Dataflow_Graph_Analyzer (CUTS_Dataflow_Graph & g);

  // Destructor
  ~CUTS_Dataflow_Graph_Analyzer (void);

  /**
   * analyze method
   *
   * @param[in]   testdata    The database containing the trace data
   * @param[in]   repo_location   The location of the data file
   */
  void analyze (CUTS_Test_Database & testdata,
                ACE_CString & repo_location);

  /**
   * join method
   *
   * @param[in]   testdata    The database containing the trace data
   * @param[in]   repo_location   The location of the data file
   */
  CUTS_Dataset_Repo * join (CUTS_Test_Database & testdata,
                            ACE_CString & repo_location);

private:

  // Get the descendents nodes for any given node
  void get_descendents (vertex_descriptor u,
                        std::set <vertex_descriptor> & descendents);

  // Check whether a particular node is associated with the given leaf node
  bool eligibility_test (std::set <vertex_descriptor> & descendents,
                         vertex_descriptor candidate,
                         vertex_descriptor current_leaf_node);

  // Initialize the algorithm
  void initialize (void);

  // Check whether the node is in the leaves list
  bool search_leaf (vertex_descriptor u);

  // Finds the first common vertex for all the single leaf trees
  bool find_common_vertex (vertex_descriptor * common_vertex);

  // Reference to the main dataflow model
  CUTS_Dataflow_Graph & g_;

  // The list of leaves
  std::map <int, vertex_descriptor> leaves_;

  // The the data structure on which algorithm works
  VERTEX_INFO vertex_data_;

  // Different worker threds to work on the graph
  std::vector <CUTS_Graph_Worker *> workers_;

  // The final joined dataset repo
  CUTS_Dataset_Repo * repo_;

};

#endif  // !defined _CUTS_DATAFLOW_GRAPH_ANALYZER_H_