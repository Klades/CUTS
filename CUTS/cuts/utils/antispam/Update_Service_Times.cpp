// $Id$

#include "Update_Service_Times.h"

#if !defined (__CUTS_INLINE__)
#include "Update_Service_Times.inl"
#endif

#include "Component_Assembly.h"
#include "Component_Instance.h"
#include "Port_Instance.h"
#include "boost/bind.hpp"
#include <algorithm>

struct visit_entry
{
  typedef void result_type;

  visit_entry (CUTS_Update_Service_Times & visitor)
    : visitor_ (visitor)
  {

  }

  template <typename ENTRY>
  void operator () (ENTRY e)
  {
    e.int_id_->accept (this->visitor_);
  }

private:
  CUTS_Update_Service_Times & visitor_;
};

//
// visit_CUTS_Component_Assembly
//
void CUTS_Update_Service_Times::
visit_CUTS_Component_Assembly (CUTS_Component_Assembly & assembly)
{
  this->used_util_ = 0.0;

  std::for_each (assembly.instances ().begin (),
                 assembly.instances ().end (),
                 boost::bind (visit_entry (*this), _1));
}

//
// visit_CUTS_Component_Instance
//
void CUTS_Update_Service_Times::
visit_CUTS_Component_Instance (CUTS_Component_Instance & instance)
{
  // Save the utilization of the component. This can be used to determine
  // the remaining utilization for each port in the component.
  this->curr_util_ = instance.utilization ();

  std::for_each (instance.input_events ().begin (),
                 instance.input_events ().end (),
                 boost::bind (visit_entry (*this), _1));
}

//
// visit_CUTS_Input_Event_Port_Instance
//
void CUTS_Update_Service_Times::
visit_CUTS_Input_Event_Port_Instance (CUTS_Input_Event_Port_Instance & port)
{

  // Determine how much of the CPU is occurpied by other ports.
  double util = port.utilization ();
  double used_util = this->used_util_ + (this->curr_util_ - util);

  // Calculate the new service time for the port.
  double service_time = port.service_time () * (1.0 + used_util);

  // Update the service time.
  port.service_time (service_time);

  // Update the service times for each ouptut port.
  double saved_util = this->used_util_;
  this->used_util_ = used_util;

  std::for_each (port.outputs ().begin (),
                 port.outputs ().end (),
                 boost::bind (&CUTS_Output_Event_Port_Instance::accept,
                              _1,
                              boost::ref (*this)));

  // Restore the saved utilization.
  this->used_util_ = saved_util;
}

//
// CUTS_Output_Event_Port_Instance
//
void CUTS_Update_Service_Times::
visit_CUTS_Output_Event_Port_Instance (CUTS_Output_Event_Port_Instance & port)
{
  double service_time = port.service_time () * (1.0 + this->used_util_);
  port.service_time (service_time);
}
