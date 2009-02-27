// $Id$

#include "Unit_Test_Graph.h"
#include "Log_Format.h"
#include "ace/SString.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// CUTS_Unit_Test_Graph
//
CUTS_Unit_Test_Graph::CUTS_Unit_Test_Graph (void)
{

}

//
// ~CUTS_Unit_Test_Graph
//
CUTS_Unit_Test_Graph::~CUTS_Unit_Test_Graph (void)
{

}

//
// insert
//
bool CUTS_Unit_Test_Graph::insert (CUTS_Log_Format * format)
{
  graph_type::vertex_descriptor vertex = boost::add_vertex (this->graph_);
  boost::put (boost::vertex_name_t (), this->graph_, vertex, format->name ());
  boost::put (log_format_t (), this->graph_, vertex, format);

  return true;
}

//
// connect
//
bool CUTS_Unit_Test_Graph::
connect (const ACE_CString & src, const ACE_CString & dst)
{
  boost::graph_traits <graph_type>::vertex_iterator src_iter, dst_iter, end;

  // Locate the source vertex.
  for (boost::tie (src_iter, end) = boost::vertices (this->graph_);
       src_iter != end;
       ++ src_iter)
  {
    if (boost::get (boost::vertex_name_t (), this->graph_, *src_iter) == src)
      break;
  }

  if (src_iter == end)
    return false;

  // Locate the destination vertex.
  for (boost::tie (dst_iter, end) = boost::vertices (this->graph_);
       dst_iter != end;
       ++ dst_iter)
  {
    if (boost::get (boost::vertex_name_t (), this->graph_, *dst_iter) == dst)
      break;
  }

  if (dst_iter == end)
    return false;

  // Create a new edge between the two formats.
  boost::add_edge (*src_iter, *dst_iter, this->graph_);
  return true;
}

//
// graph
//
const CUTS_Unit_Test_Graph::graph_type
CUTS_Unit_Test_Graph::graph (void) const
{
  return this->graph_;
}
