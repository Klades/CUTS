// $Id$

#define NOMINMAX
#include "Propogate_Arrival_Rates.h"

#if !defined (__CUTS_INLINE__)
#include "Propogate_Arrival_Rates.inl"
#endif

#include "Component_Assembly.h"
#include "Port_Instance.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// visit_CUTS_Component_Assembly
//
void CUTS_Propogate_Arrival_Rates::
visit_CUTS_Component_Assembly (CUTS_Component_Assembly & assembly)
{
  // Visit each of the start ports. We need to update the model
  // according to the arrival rate (lambda) of each input port.
  this->curr_lambda_ = 0.0;

  std::for_each (assembly.start ().begin (),
                 assembly.start ().end (),
                 boost::bind (&CUTS_Input_Event_Port_Instance::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_CUTS_Input_Event_Port_Instance
//
void CUTS_Propogate_Arrival_Rates::
visit_CUTS_Input_Event_Port_Instance (CUTS_Input_Event_Port_Instance & port)
{
  // Save the current lambda.
  double cached_lambda = this->curr_lambda_;

  // Update the current lambda base on the current port.
  this->curr_lambda_ += port.lambda ();
  port.lambda (this->curr_lambda_);

  // Visit each of the output ports for the input port.
  std::for_each (port.outputs ().begin (),
                 port.outputs ().end (),
                 boost::bind (&CUTS_Output_Event_Port_Instance::accept,
                              _1,
                              boost::ref (*this)));

  // Restore the cached lambda
  this->curr_lambda_ = cached_lambda;
}

//
// visit_CUTS_Output_Event_Port_Instance
//
void CUTS_Propogate_Arrival_Rates::
visit_CUTS_Output_Event_Port_Instance (CUTS_Output_Event_Port_Instance & port)
{
  double mu = 1.0 / port.service_time ();
  double tput = std::min (this->curr_lambda_, mu);
  this->curr_lambda_ = tput;

  std::for_each (port.connections ().begin (),
                 port.connections ().end (),
                 boost::bind (&CUTS_Input_Event_Port_Instance::accept,
                              _1,
                              boost::ref (*this)));
}
