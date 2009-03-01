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

/**
 * @struct response_time_t
 */
struct response_time_t
{
  response_time_t (const CUTS_Component_Instance & inst, double & util)
    : inst_ (inst),
      util_ (util)
  {

  }

  void operator () (CUTS_Behavior_Graph::vertex_descriptor port) const
  {
    // Get the port details.
    CUTS_Port_Details details;
    this->inst_.assembly ().get_port_details (port, details);

    // Elongate the ports service time.
    double baseline_util =
      details.arrival_rate_ * details.service_time_ / 1000.0;
    double host_util = this->util_ - baseline_util;

    double elongated = details.service_time_ / (1 - host_util);
    double rt = 1.0 / (1.0 / elongated - details.arrival_rate_ / 1000.0);

    std::cout << ". " << rt << " msec" << std::endl;
  }

private:
  const CUTS_Component_Instance & inst_;

  double & util_;
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

//
// response_time
//
void CUTS_Component_Instance::response_time (double util)
{
  std::for_each (this->ports_.begin (),
                 this->ports_.end (),
                 response_time_t (*this, util));
}

