// $Id$

#include "IO_System_Metric_Visitor.h"
#include "cuts/Component_Info.h"
#include "cuts/Component_Type.h"
#include "cuts/System_Metric.h"
#include "cuts/Component_Metric.h"
#include "cuts/Port_Metric.h"
#include "cuts/Testing_Service.h"
#include "cuts/Time.h"
#include <iostream>

//
// CUTS_IO_System_Metric_Visitor
//
CUTS_IO_System_Metric_Visitor::
CUTS_IO_System_Metric_Visitor (const CUTS_Testing_Service * tsvc)
: tsvc_ (tsvc)
{

}

//
// ~CUTS_IO_System_Metric_Visitor
//
CUTS_IO_System_Metric_Visitor::~CUTS_IO_System_Metric_Visitor (void)
{

}

//
// visit_system_metrics
//
void CUTS_IO_System_Metric_Visitor::
visit_system_metric (const CUTS_System_Metric & metrics)
{
  std::cout
    << "*** Collection Time: "
    << CUTS_string_time (metrics.get_timestamp (), "%m-%d-%Y %H:%M:%S")
    << " ***" << std::endl;

  CUTS_Component_Metric_Map::CONST_ITERATOR iter (metrics.component_metrics ());

  for (iter; !iter.done (); iter ++)
  {
    // Get the information about this component and print its
    // instance name.
    std::cout << "instance : ";

    if (this->tsvc_->registry ().
        get_component_info (iter->key (), &this->myinfo_) == 0)
    {
      std::cout << this->myinfo_->inst_.c_str () << std::endl;
    }
    else
    {
      std::cout << "<Unknown>" << std::endl;
    }

    // Visit the component metrics.
    iter->item ()->accept (*this);
  }
}

//
// visit_component_metrics
//
void CUTS_IO_System_Metric_Visitor::
visit_component_metric (const CUTS_Component_Metric & metrics)
{
  ACE_CString portname;
  CUTS_Port_Metric_Map::CONST_ITERATOR iter (metrics.port_metrics ());

  for (iter; !iter.done (); iter ++)
  {
    // Print the name of the port.
    this->myinfo_->type_->sinks_.find (iter->key (), portname);
    std::cout << "  input port : " << portname.c_str () << std::endl;

    // Visit the CUTS_Port_Metric object.
    iter->item ()->accept (*this);
  }
}

//
// visit_port_metrics
//
void CUTS_IO_System_Metric_Visitor::
visit_port_metric (const CUTS_Port_Metric & metrics)
{
  metrics.summary ().accept (*this);
}

//
// visit_port_summary
//
void CUTS_IO_System_Metric_Visitor::
visit_port_summary (const CUTS_Port_Summary & summary)
{
  // Write the queuing and service time metrics.
  std::cout << "    queuing time ";
  summary.queuing_time ().accept (*this);

  std::cout << "    service time ";
  summary.service_time ().accept (*this);

  // Visit the endpoints for the summary.
  summary.endpoints ().accept (*this);
}

//
// visit_port_summary_base
//
void CUTS_IO_System_Metric_Visitor::
visit_endpoint_log_summary (const CUTS_Endpoint_Log_Summary & summary)
{
  CUTS_Endpoint_Data_Logs::const_iterator log_iter (summary.logs ());

  ACE_CString name;
  CUTS_Endpoint_Data data_avg;

  for (; !log_iter.done (); log_iter ++)
  {
    // Get iterator to the endpoint log data.
    CUTS_Endpoint_Data_Log::iterator
      ep_iter = log_iter->item ()->begin (),
      ep_iter_end = log_iter->item ()->used_end ();

    for ( ; ep_iter != ep_iter_end; ep_iter ++)
    {
      if (this->myinfo_->type_->sources_.find (log_iter->key (), name) == 0)
        std::cout << "      " << name.c_str ();
      else
        std::cout << "      <unknown port>";

      ep_iter->avg_value (data_avg);

      std::cout
        << " : "
        << ep_iter->min_value ().time_of_completion ().msec () << "/"
        << data_avg.time_of_completion ().msec () << "/"
        << ep_iter->max_value ().time_of_completion ().msec () << std::endl;
    }
  }
}

//
// visit_time_measurement
//
void CUTS_IO_System_Metric_Visitor::
visit_time_measurement (const CUTS_Time_Measurement & tm)
{
  ACE_Time_Value avg_time;
  tm.avg_value (avg_time);

  std::cout
    << "(best/avg/worst msec) : "
    << tm.min_value ().msec () << "/"
    << avg_time.msec () << "/" << tm.max_value ().msec () << std::endl;
}
