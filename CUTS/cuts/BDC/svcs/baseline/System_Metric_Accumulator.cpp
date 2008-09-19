// $Id$

#include "System_Metric_Accumulator.h"
#include "cuts/System_Metric.h"
#include "cuts/Component_Metric.h"
#include "cuts/Port_Metric.h"
#include "cuts/Port_Measurement.h"

//
// CUTS_System_Metric_Accumulator
//
CUTS_System_Metric_Accumulator::
CUTS_System_Metric_Accumulator (CUTS_System_Metric & dest)
: dest_ (dest)
{

}

//
// ~CUTS_System_Metric_Accumulator
//
CUTS_System_Metric_Accumulator::~CUTS_System_Metric_Accumulator (void)
{

}

//
// visit_system_metric
//
void CUTS_System_Metric_Accumulator::
visit_system_metric (const CUTS_System_Metric & metric)
{
  CUTS_Component_Metric_Map::
    CONST_ITERATOR iter (metric.component_metrics ());

  for (; !iter.done (); iter.advance ())
  {
    // We need to locate the target component metric in the
    // <dest_> system metric object.
    if (this->dest_.component_metric (iter->key (), this->component_) == 0)
    {
      if (this->component_ != 0)
        iter->item ()->accept (*this);
      else
        ACE_ERROR ((LM_ERROR,
                    "*** error (baseline): failed to locate "
                    "component metric\n"));
    }
  }
}

//
// visit_component_metric
//
void CUTS_System_Metric_Accumulator::
visit_component_metric (const CUTS_Component_Metric & metric)
{
  CUTS_Port_Metric_Map::CONST_ITERATOR iter (metric.port_metrics ());

  for (; !iter.done (); iter.advance ())
  {
    // Locate the port metric in the target collection. If it
    // does not exist, we need to create it.
    if (this->component_->port_metric (iter->key (), this->port_metric_) == 0)
    {
      if (this->port_metric_ != 0)
        iter->item ()->accept (*this);
      else
        ACE_ERROR ((LM_ERROR,
                    "*** error (baseline): failed to locate "
                    "port metric\n"));
    }
  }
}

//
// visit_port_metric
//
void CUTS_System_Metric_Accumulator::
visit_port_metric (const CUTS_Port_Metric & port)
{
  this->port_summary_ = &this->port_metric_->summary ();
  port.summary ().accept (*this);
}

//
// visit_port_measurement
//
void CUTS_System_Metric_Accumulator::
visit_port_summary (const CUTS_Port_Summary & summary)
{
  //*this->port_summary_ += summary;
}
