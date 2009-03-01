// $Id$

#include "Component.h"

#if !defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

//
// associate
//
bool CUTS_Component::associate (const ACE_CString & input,
                                const ACE_CString & output,
                                bool create)
{
  // Locate, or create, a vertex for the input port.
  CUTS_Behavior_Graph::vertex_descriptor input_vertex;
  CUTS_Port_Details details;

  if (!this->find_port (input, input_vertex))
  {
    if (!create)
      return false;

    input_vertex = boost::add_vertex (this->graph_);
    boost::put (boost::vertex_name_t (), this->graph_, input_vertex, input);

    details.input_ = true;
    boost::put (CUTS_Port_Details_Tag (), this->graph_, input_vertex, details);
  }

  // Locate, or create, a vertex for the output port.
  CUTS_Behavior_Graph::vertex_descriptor output_vertex;

  if (!this->find_port (output, output_vertex))
  {
    if (!create)
      return false;

    output_vertex = boost::add_vertex (this->graph_);
    boost::put (boost::vertex_name_t (), this->graph_, output_vertex, output);

    details.input_ = false;
    boost::put (CUTS_Port_Details_Tag (), this->graph_, output_vertex, details);
  }

  // Create a new edge between the two ports.
  boost::add_edge (input_vertex, output_vertex, this->graph_);
  return true;
}

//
// get_port_details
//
bool CUTS_Component::
get_port_details (const ACE_CString & name, CUTS_Port_Details & details) const
{
  CUTS_Behavior_Graph::vertex_descriptor vertex;

  if (this->find_port (name, vertex))
    return this->get_port_details (vertex, details);

  return false;
}

//
// get_port_details
//
bool CUTS_Component::
get_port_details (CUTS_Behavior_Graph::vertex_descriptor port,
                  CUTS_Port_Details & details) const
{
  details = boost::get (CUTS_Port_Details_Tag (), this->graph_, port);
  return true;
}

//
// set_port_details
//
bool CUTS_Component::
set_port_details (const ACE_CString & name, const CUTS_Port_Details & details)
{
  CUTS_Behavior_Graph::vertex_descriptor vertex;

  if (this->find_port (name, vertex))
    return this->set_port_details (vertex, details);

  return false;
}

bool CUTS_Component::
set_port_details (CUTS_Behavior_Graph::vertex_descriptor vertex,
                  const CUTS_Port_Details & details)
{
  boost::put (CUTS_Port_Details_Tag (), this->graph_, vertex, details);
  return true;
}

//
// find_port
//
bool CUTS_Component::
find_port (const ACE_CString & name,
           CUTS_Behavior_Graph::vertex_descriptor & vertex) const
{
  boost::graph_traits <CUTS_Behavior_Graph>::vertex_iterator iter, iter_end;
  ACE_CString temp;

  // Locate the source vertex.
  for (boost::tie (iter, iter_end) = boost::vertices (this->graph_);
       iter != iter_end;
       ++ iter)
  {
    temp = boost::get (boost::vertex_name_t (), this->graph_, *iter);

    if (temp == name)
    {
      vertex = *iter;
      return true;
    }
  }

  return false;
}

