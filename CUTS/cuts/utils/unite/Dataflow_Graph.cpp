// $Id$

#include "Dataflow_Graph.h"

#if !defined (__CUTS_INLINE__)
#include "Dataflow_Graph.inl"
#endif

#include "Log_Format.h"
#include "ace/SString.h"
#include "ace/CORBA_macros.h"
#include "boost/bind.hpp"
#include "boost/graph/topological_sort.hpp"
#include <algorithm>

//
// connect
//
bool CUTS_Dataflow_Graph::
connect (const ACE_CString & src_name, const ACE_CString & dst_name)
{
  vertex_descriptor src = 0, dst = 0;

  if (0 != this->vertices_.find (src_name, src))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to locate source [%s]\n"),
                       src_name.c_str ()),
                       false);

  if (0 != this->vertices_.find (dst_name, dst))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to locate destination [%s]\n"),
                       dst_name.c_str ()),
                       false);

  boost::add_edge (src, dst, this->graph_);
  return true;
}

//
// create_log_format
//
bool CUTS_Dataflow_Graph::
create_log_format (const ACE_CString & name, CUTS_Log_Format *& format)
{
  // First, let's see if we have already created this vertex. If
  // so, then we need to just return the existing one.
  vertex_descriptor vertex = 0;
  if (this->vertices_.find (name, vertex) == 0)
  {
    format = boost::get (CUTS_Unit_Test_Graph_Traits::log_format_t (),
                         this->graph_,
                         vertex);

    return true;
  }

  // Allocate a new log format.
  CUTS_Log_Format * temp = 0;
  ACE_NEW_THROW_EX (temp,
                    CUTS_Log_Format (name),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Log_Format> auto_clean (temp);

  // Insert the format into the graph.
  vertex = boost::add_vertex (this->graph_);
  int retval = this->vertices_.bind (name, vertex);

  if (retval != 0)
  {
    // We need to remove the vertex from the graph.

    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to cache log format\n")),
                       false);
  }

  format = auto_clean.release ();

  // Initialize the vertex's traits.
  boost::put (boost::vertex_name_t (), this->graph_, vertex, name);
  boost::put (CUTS_Unit_Test_Graph_Traits::log_format_t (),
              this->graph_,
              vertex,
              format);

  return true;
}

//
// get_process_order
//
void CUTS_Dataflow_Graph::
get_process_order (std::vector <vertex_descriptor> & list) const
{
  boost::topological_sort (this->graph_, std::back_inserter (list));
}

//
// normalize_name
//
void CUTS_Dataflow_Graph::normalize_name (void)
{
  std::replace (this->name_.begin (),
                this->name_.end (),
                '-',
                '_');

  this->name_ = "_" + this->name_;
}
