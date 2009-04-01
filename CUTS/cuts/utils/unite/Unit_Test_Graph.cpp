// $Id$

#include "Unit_Test_Graph.h"

#if !defined (__CUTS_INLINE__)
#include "Unit_Test_Graph.inl"
#endif

#include "Log_Format.h"
#include "ace/SString.h"
#include "boost/bind.hpp"
#include <algorithm>


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
// create_log_format
//
bool CUTS_Unit_Test_Graph::
create_log_format (const ACE_CString & name)
{
  CUTS_Log_Format * format = 0;
  return this->create_log_format (name, format);
}

//
// create_log_format
//
bool CUTS_Unit_Test_Graph::
create_log_format (const ACE_CString & name, CUTS_Log_Format *& format)
{
  if (this->formats_.find (name, format) == 0)
    return true;

  // Allocate a new log format.
  CUTS_Log_Format * temp = 0;
  ACE_NEW_RETURN (temp, CUTS_Log_Format (name), false);
  ACE_Auto_Ptr <CUTS_Log_Format> auto_clean (temp);

  // Store the log format in the hash map.
  int retval = this->formats_.bind (name, temp);

  if (retval != 0)
    return false;

  format = auto_clean.release ();

  // Insert the format into the graph.
  graph_type::vertex_descriptor vertex = boost::add_vertex (this->graph_);
  boost::put (boost::vertex_name_t (), this->graph_, vertex, format->name ());
  boost::put (log_format_t (), this->graph_, vertex, format);
  return true;
}

