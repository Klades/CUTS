// $Id$

#include "Component_Instance.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Instance.inl"
#endif

#include "Component_Assembly.h"
#include "Deployment.h"
#include <iostream>
#include <numeric>

/**
 * @struct add_utilization
 */
struct add_utilization
{
  add_utilization (const CUTS_Component_Instance & inst)
    : inst_ (inst)
  {

  }

  double operator () (double util, CUTS_Behavior_Graph::vertex_descriptor port)
  {
    CUTS_Port_Details details;

    if (this->inst_.assembly ().get_port_details (port, details))
      util += (details.arrival_rate_ * details.service_time_) / 1000.0;

    return util;
  }

private:
  const CUTS_Component_Instance & inst_;
};

//
// utilization
//
double CUTS_Component_Instance::utilization (void) const
{
  double util = std::accumulate (this->ports_.begin (),
                                 this->ports_.end (),
                                 0.0,
                                 add_utilization (*this));

  return util;
}
