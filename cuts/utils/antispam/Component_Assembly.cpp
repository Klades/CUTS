// $Id$

#include "Component_Assembly.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Assembly.inl"
#endif

#include "Component.h"
#include "Component_Instance.h"
#include "ace/CORBA_macros.h"
#include "boost/bind.hpp"

//
// ~CUTS_Component_Assembly
//
CUTS_Component_Assembly::~CUTS_Component_Assembly (void)
{
  instances_type::ITERATOR iter (this->instances_);

  for ( ; !iter.done (); ++ iter)
    delete iter->item ();
}

//
// new_instance
//
int CUTS_Component_Assembly::new_instance (const ACE_CString & name,
                                           const CUTS_Component & type,
                                           CUTS_Component_Instance * & inst)
{
  if (this->instances_.find (name, inst) == 0)
    return 0;

  // We need to partition the ports for deployment. This is done
  // by creating a duplicate behavior graph of the component's
  // type in this graph (mangling names of course), while caching
  // instances vertices from the assembly graph.
  boost::graph_traits <CUTS_Behavior_Graph>::
    vertex_iterator iter, iter_end;

  // First, copy over the vertices.
  boost::tie (iter, iter_end) = boost::vertices (type.behavior ());

  ACE_CString temp;
  CUTS_Behavior_Graph::vertex_descriptor vertex;
  CUTS_Component_Instance::ports_type ports;
  CUTS_Port_Details details;

  for (; iter != iter_end; ++ iter)
  {
    // Get the port's details.
    details = boost::get (CUTS_Port_Details_Tag (), type.behavior (), *iter);

    // Insert the port into the assembly's graph.
    vertex = boost::add_vertex (this->graph_);

    // Set the port's details
    details.name_ = name + '.' + details.name_;
    boost::put (CUTS_Port_Details_Tag (), this->graph_, vertex, details);

    // Cache the vertex with its instance.
    ports.push_back (vertex);
  }

  // Next, copy the edges in the bahavior graph.
  boost::graph_traits <CUTS_Behavior_Graph>::
    edge_iterator edge_iter, edge_iter_end;

  boost::tie (edge_iter, edge_iter_end) = boost::edges (type.behavior ());

  ACE_CString src_name, dst_name;
  CUTS_Behavior_Graph::edge_descriptor edge;
  CUTS_Behavior_Graph::vertex_descriptor src, dst;

  for (; edge_iter != edge_iter_end; ++ edge_iter)
  {
    // Reset the base name of the dst/src strings.
    src_name = dst_name = name + '.';

    // Get the vertices of this edge.
    src = boost::source (*edge_iter, type.behavior ());
    dst = boost::target (*edge_iter, type.behavior ());

    // Construct the name of the vertices.
    src_name += boost::get (CUTS_Port_Details_Tag (), type.behavior (), src).name_;
    dst_name += boost::get (CUTS_Port_Details_Tag (), type.behavior (), dst).name_;

    // Connect the two vertices in the assembly graph.
    if (!this->associate (src_name, dst_name, false))
      return -1;
  }

  CUTS_Component_Instance * temp_inst = 0;

  ACE_NEW_THROW_EX (temp_inst,
                    CUTS_Component_Instance (*this, ports),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Component_Instance> auto_clean (temp_inst);

  // Save the instance.
  int retval = this->instances_.bind (name, temp_inst);

  if (retval == 0)
    inst = auto_clean.release ();

  return retval;
}

//
// get_port
//
bool CUTS_Component_Assembly::
get_port (const ACE_CString & name,
          CUTS_Behavior_Graph::vertex_descriptor & vertex)
{
  boost::graph_traits <CUTS_Behavior_Graph>::
    vertex_iterator iter, iter_end;

  CUTS_Port_Details details;

  for (boost::tie (iter, iter_end) = boost::vertices (this->graph_);
       iter != iter_end;  ++ iter)
  {
    // Get the port's details.
    details = boost::get (CUTS_Port_Details_Tag (), this->graph_, *iter);

    if (details.name_ == name)
    {
      vertex = *iter;
      return true;
    }
  }

  return false;
}

//
// set_start_port
//
bool CUTS_Component_Assembly::set_start_port (const ACE_CString & name)
{
  CUTS_Behavior_Graph::vertex_descriptor vertex;

  bool retval = this->get_port (name, vertex);

  if (retval)
    this->start_.push_back (vertex);

  return retval;
}
