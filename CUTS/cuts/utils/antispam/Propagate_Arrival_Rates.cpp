// $Id$

#define NOMINMAX
#include "Propagate_Arrival_Rates.h"

#if !defined (__CUTS_INLINE__)
#include "Propagate_Arrival_Rates.inl"
#endif

#include "Component_Assembly.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// propogate
//
void CUTS_Propagate_Arrival_Rates::
propogate (CUTS_Component_Assembly & assembly)
{
  this->incr_lambda_ = 0.0;
  this->assembly_ = &assembly;

  std::for_each (assembly.start ().begin (),
                 assembly.start ().end (),
                 boost::bind (&CUTS_Propagate_Arrival_Rates::propogate_input,
                              this,
                              _1));
}

//
// propogate_input
//
void CUTS_Propagate_Arrival_Rates::
propogate_input (CUTS_Behavior_Graph::vertex_descriptor port)
{
  // Save the current increment lamda value.
  double saved_lambda = this->incr_lambda_;

  // Get the details about the port.
  CUTS_Port_Details details;
  this->assembly_->get_port_details (port, details);

  if (this->incr_lambda_ > 0.0)
  {
    // Middle of the behavior model.
    details.arrival_rate_ += this->incr_lambda_;

    // Update the port details.
    this->assembly_->set_port_details (port, details);
  }
  else
    // Start of the behavior model.
    this->incr_lambda_ = details.arrival_rate_;

  // Calculate the service rate for the port (in secs)
  double mu = (1000.0 / details.service_time_);

  if (details.arrival_rate_ > mu)
    // We are over utilized. We can't push through more than we
    // can handle. So, adjust the arrival rate.
    this->incr_lambda_ -= (details.arrival_rate_ - mu);

  // Visit all the output ports this port is connected.
  CUTS_Behavior_Graph::out_edge_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::out_edges (port, this->assembly_->behavior ());

  std::for_each (iter,
                 iter_end,
                 boost::bind (&CUTS_Propagate_Arrival_Rates::visit_input_to_output,
                              this,
                              _1));

  // Restore the saved lambda.
  this->incr_lambda_ = saved_lambda;
}

//
// visit_input_to_output
//
void CUTS_Propagate_Arrival_Rates::
visit_input_to_output (CUTS_Behavior_Graph::edge_descriptor edge)
{
  // Get the output port for this edge.
  CUTS_Behavior_Graph::vertex_descriptor output =
    boost::target (edge, this->assembly_->behavior ());

  // Visit all the input ports for this output port.
  CUTS_Behavior_Graph::out_edge_iterator iter, iter_end;
  boost::tie (iter, iter_end) = boost::out_edges (output, this->assembly_->behavior ());

  std::for_each (iter,
                 iter_end,
                 boost::bind (&CUTS_Propagate_Arrival_Rates::visit_output_to_input,
                              this,
                              _1));
}

//
// visit_input_to_output
//
void CUTS_Propagate_Arrival_Rates::
visit_output_to_input (CUTS_Behavior_Graph::edge_descriptor edge)
{
  // Get the output port for this edge.
  CUTS_Behavior_Graph::vertex_descriptor input =
    boost::target (edge, this->assembly_->behavior ());

  this->propogate_input (input);
}
