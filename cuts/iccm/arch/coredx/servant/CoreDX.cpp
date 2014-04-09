// $Id$

#include "CoreDX.h"

#if !defined (__CUTS_INLINE__)
#include "CoreDX.inl"
#endif

namespace iCCM
{
  const CoreDX::statusmask_type CoreDX::STATUS_MASK_NONE = 0;
  const CoreDX::statusmask_type CoreDX::STATUS_MASK_DATA_AVAILABLE = ::DDS::DATA_AVAILABLE_STATUS;
  const CoreDX::instancehandle_type CoreDX::HANDLE_NIL = ::DDS::HANDLE_NIL;
}

/**
 * QoS operators
 */
void operator <<= (::iCCM::CoreDX::datareaderqos_type & out, const ::iCCM::CoreDX::datareaderqos_type & in)
{
#ifndef WIN32
  out.durability.copy (&in.durability);
//  out.deadline.copy (&in.deadline);
  out.latency_budget.copy (&in.latency_budget);
//  out.liveliness.copy (&in.liveliness);
  out.reliability.copy (&in.reliability);
  out.destination_order.copy (&in.destination_order);
//  out.history.copy (&in.history);
//  out.resource_limits.copy (&in.resource_limits);
  out.user_data.copy (&in.user_data);
  out.ownership.copy (&in.ownership);
  out.time_based_filter.copy (&in.time_based_filter);
  out.reader_data_lifecycle.copy (&in.reader_data_lifecycle);
  out.entity_name = in.entity_name;
  out.logging = in.logging;
  out.rtps_reader = in.rtps_reader;
#endif
}

void operator <<= (::iCCM::CoreDX::topicqos_type & out, const ::iCCM::CoreDX::topicqos_type & in)
{
#ifndef WIN32
  out.topic_data.copy (&in.topic_data);
  out.durability.copy (&in.durability);
  out.durability_service.copy (&in.durability_service);
  out.deadline.copy (&in.deadline);
  out.latency_budget.copy (&in.latency_budget);
  out.liveliness.copy (&in.liveliness);
  out.reliability.copy (&in.reliability);
  out.destination_order.copy (&in.destination_order);
  out.history.copy (&in.history);
  out.resource_limits.copy (&in.resource_limits);
  out.transport_priority.copy (&in.transport_priority);
  out.lifespan.copy (&in.lifespan);
  out.ownership.copy (&in.ownership);
  out.entity_name = in.entity_name;
  out.logging = in.logging;
#endif
}
