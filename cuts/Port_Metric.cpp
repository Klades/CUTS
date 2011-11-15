// $Id$

#include "Port_Metric.h"

#if !defined (__CUTS_INLINE__)
#include "Port_Metric.inl"
#endif

#include "Metrics_Visitor.h"

//
// CUTS_Port_Metric
//
CUTS_Port_Metric::CUTS_Port_Metric (void)
: log_ (50)
{
  CUTS_TRACE ("CUTS_Port_Metric::CUTS_Port_Metric (void)");
}

//
// ~CUTS_Port_Metric
//
CUTS_Port_Metric::~CUTS_Port_Metric (void)
{
  CUTS_TRACE ("CUTS_Port_Metric::~CUTS_Port_Metric (void)");
}

//
// accept
//
void CUTS_Port_Metric::
accept (CUTS_Metrics_Visitor & visitor) const
{
  CUTS_TRACE ("CUTS_Port_Metric::accept (CUTS_Metrics_Visitor &) const");
  visitor.visit_port_metric (*this);
}
