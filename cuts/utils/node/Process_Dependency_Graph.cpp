// $Id$

#include "Process_Dependency_Graph.h"

#if !defined (__CUTS_INLINE__)
#include "Process_Dependency_Graph.inl"
#endif

#include "boost/graph/topological_sort.hpp"

//
// insert
//
int CUTS_Process_Dependency_Graph::
insert (const ACE_CString & name, CUTS_Process_Options * opts)
{
  // Make sure the name does not already exist in the graph.
  if (0 == this->vertices_.find (name))
    return 1;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - inserting %s into graph\n"),
              name.c_str ()));

  graph_type::vertex_descriptor vertex = boost::add_vertex (*this);
  boost::put (boost::vertex_name_t (), *this, vertex, name);
  boost::put (CUTS_Process_Dependency_Graph_Traits::process_opts_t (), *this, vertex, opts);

  // Finally, cache the vertex.
  return this->vertices_.bind (name, vertex);
}

//
// connect
//
int CUTS_Process_Dependency_Graph::
connect (const ACE_CString & src_name, const ACE_CString & dst_name)
{
  vertex_descriptor src, dst;

  if (0 != this->vertices_.find (src_name, src))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to located %s vertex descriptor\n"),
                       src_name.c_str ()),
                       -1);

  if (0 != this->vertices_.find (dst_name, dst))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to located %s vertex descriptor\n"),
                       dst_name.c_str ()),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - creating edge %s (%d) -> %s (%d)\n"),
              src_name.c_str (),
              src,
              dst_name.c_str (),
              dst));

  // Create a link between to the two processes.
  std::pair <edge_descriptor, bool>
    result = boost::add_edge (src, dst, *this);

  return result.second ? 0 : -1;
}

//
// get_execution_order
//
void CUTS_Process_Dependency_Graph::
get_execution_order (std::vector <vertex_descriptor> & sorted_list)
{
  boost::topological_sort (*this, std::back_inserter (sorted_list));
}

