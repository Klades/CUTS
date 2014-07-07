// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Servant.inl"
#endif

namespace iCCM
{

//
// DDS_Servant
//
template <typename T>
DDS_Servant <T>::DDS_Servant (const char * name)
: Servant (name)
{
  // Create the participant for this servant.
  typedef typename T::domainparticipantfactory_var_type domainparticipantfactory_var_type;
  domainparticipantfactory_var_type factory = T::get_domainparticipantfactory_instance ();

  this->participant_ =
    factory->create_participant (0,
                                 T::domainparticipant_qos_default (),
                                 0,
                                 T::STATUS_MASK_NONE);
}


//
// do_default_configure
//
template <typename T>
void DDS_Servant <T>::do_default_configure (void)
{
  subscriber_var_type subscriber = 0;
  if (0 != this->subscribers_.find (ICCM_DDS_DEFAULT_SUBSCRIBER, subscriber))
  {
    // Create the default subscriber, and save it for later usage.
    subscriber =
      this->participant_->create_subscriber (T::subscriber_qos_default (),
                                             0,
                                             0);

    this->subscribers_.bind (ICCM_DDS_DEFAULT_SUBSCRIBER, subscriber);
  }

  publisher_var_type publisher = 0;

  if (0 != this->publishers_.find (ICCM_DDS_DEFAULT_PUBLISHER, publisher))
  {
    // Create the default publisher, and save it for later usage.
    publisher =
      this->participant_->create_publisher (T::publisher_qos_default (),
                                            0,
                                            0);

    this->publishers_.bind (ICCM_DDS_DEFAULT_PUBLISHER, publisher);
  }
}

//
// QoS Conversion Hooks
//
#ifdef ICCM_DDS_SUPPORTS_SCHEDULING_QOS
template <typename T>
void DDS_Servant <T>::apply (typename T::scheduling_class_kind_type & dst, const ::iccm::SchedulingClassQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_DEFAULT_l:
    dst = (typename T::scheduling_class_kind_type) T::SCHEDULE_DEFAULT;
    break;

  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_TIMESHARING_l:
    dst = (typename T::scheduling_class_kind_type) T::SCHEDULE_TIMESHARING;
    break;

  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_REALTIME_l:
    dst = (typename T::scheduling_class_kind_type) T::SCHEDULE_REALTIME;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::scheduling_class_type & dst, const ::iccm::SchedulingClassQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::scheduling_priority_kind_type & dst, const ::iccm::SchedulingPriorityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::SchedulingPriorityQosPolicyKind::PRIORITY_RELATIVE_l:
    dst = (typename T::scheduling_priority_kind_type) T::PRIORITY_RELATIVE;
    break;

  case ::iccm::SchedulingPriorityQosPolicyKind::PRIORITY_ABSOLUTE_l:
    dst = (typename T::scheduling_priority_kind_type) T::PRIORITY_ABSOLUTE;
    break;
  }
}


template <typename T>
void DDS_Servant <T>::apply (typename T::scheduling_priority_type & dst, const ::iccm::SchedulingPriorityQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::scheduling_type & dst, const ::iccm::SchedulingQosPolicy & src)
{
  if (src.scheduling_class_p ())
    DDS_Servant <T>::apply (dst.scheduling_class, src.scheduling_class ());

  if (src.scheduling_priority_kind_p ())
    DDS_Servant <T>::apply (dst.scheduling_priority_kind, src.scheduling_priority_kind ());

  if (src.scheduling_priority_p ())
    dst.scheduling_priority = static_cast <CORBA::Long> (src.scheduling_priority ());
}
#endif

#ifdef ICCM_DDS_SUPPORTS_WRITER_PROTOCOL_QOS
template <typename T>
void DDS_Servant <T>::apply (typename T::rtps_reliable_writer_protocol_type & dst, const ::iccm::RtpsReliableWriterProtocol & src)
{
  if (src.heartbeats_per_max_samples_p ())
    dst.heartbeats_per_max_samples = static_cast <CORBA::Long> (src.heartbeats_per_max_samples ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::writer_protocol_type & dst, const ::iccm::DataWriterProtocolQosPolicy & src)
{
  if (src.rtps_reliable_writer_p ())
    DDS_Servant <T>::apply (dst.rtps_reliable_writer, src.rtps_reliable_writer ());
}
#endif

template <typename T>
void DDS_Servant <T>::apply (typename T::access_scope_type & dst, const ::iccm::PresentationQosPolicyAccessScopeKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS_l:
    dst = (typename T::access_scope_type) T::GROUP_PRESENTATION_QOS;
    break;

  case ::iccm::PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS_l:
    dst = (typename T::access_scope_type) T::INSTANCE_PRESENTATION_QOS;
    break;

  case ::iccm::PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS_l:
    dst = (typename T::access_scope_type) T::TOPIC_PRESENTATION_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::history_kind_type & dst, const ::iccm::HistoryQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS_l:
    dst = (typename T::history_kind_type) T::KEEP_ALL_HISTORY_QOS;
    break;

  case ::iccm::HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS_l:
    dst = (typename T::history_kind_type) T::KEEP_LAST_HISTORY_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::liveliness_kind_type & dst, const ::iccm::LivelinessQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS_l:
    dst = (typename T::liveliness_kind_type) T::AUTOMATIC_LIVELINESS_QOS;
    break;

  case ::iccm::LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l:
    dst = (typename T::liveliness_kind_type) T::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
    break;

  case ::iccm::LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS_l:
    dst = (typename T::liveliness_kind_type) T::MANUAL_BY_TOPIC_LIVELINESS_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::durability_kind_type & dst, const ::iccm::DurabilityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS_l:
    dst = (typename T::durability_kind_type) T::PERSISTENT_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS_l:
    dst = (typename T::durability_kind_type) T::TRANSIENT_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS_l:
    dst = (typename T::durability_kind_type) T::TRANSIENT_LOCAL_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS_l:
    dst = (typename T::durability_kind_type) T::VOLATILE_DURABILITY_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::reliability_kind_type & dst, const ::iccm::ReliabilityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS_l:
    dst = (typename T::reliability_kind_type) T::BEST_EFFORT_RELIABILITY_QOS;
    break;

  case ::iccm::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS_l:
    dst = (typename T::reliability_kind_type) T::RELIABLE_RELIABILITY_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::destination_order_kind_type & dst, const ::iccm::DestinationOrderQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l:
    dst = (typename T::destination_order_kind_type) T::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
    break;

  case ::iccm::DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l:
    dst = (typename T::destination_order_kind_type) T::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::ownership_kind_type & dst, const ::iccm::OwnershipQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS_l:
    dst = (typename T::ownership_kind_type) T::EXCLUSIVE_OWNERSHIP_QOS;
    break;

  case ::iccm::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS_l:
    dst = (typename T::ownership_kind_type) T::SHARED_OWNERSHIP_QOS;
    break;
  }
}

template <typename T>
void DDS_Servant <T>::apply (typename T::durability_type & dst, const ::iccm::DurabilityQosPolicy & src)
{
  DDS_Servant <T>::apply (dst.kind, src.kind ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::durability_service_type & dst, const ::iccm::DurabilityServiceQosPolicy & src)
{
  if (src.service_cleanup_delay_p ())
    DDS_Servant <T>::apply (dst.service_cleanup_delay, src.service_cleanup_delay ());

  if (src.history_kind_p ())
    DDS_Servant <T>::apply (dst.history_kind, src.history_kind ());

  if (src.history_depth_p ())
    dst.history_depth = static_cast <CORBA::Long> (src.history_depth ());

  if (src.max_samples_p ())
    dst.max_samples = static_cast <CORBA::Long> (src.max_samples ());

  if (src.max_instances_p ())
    dst.max_instances = static_cast <CORBA::Long> (src.max_instances ());

  if (src.max_samples_per_instance_p ())
    dst.max_samples_per_instance = static_cast <CORBA::Long> (src.max_samples_per_instance ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::deadline_type & dst, const ::iccm::DeadlineQosPolicy & src)
{
  if (src.period_p ())
    DDS_Servant <T>::apply (dst.period, src.period ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::latency_budget_type & dst, const ::iccm::LatencyBudgetQosPolicy & src)
{
  if (src.duration_p ())
    DDS_Servant <T>::apply (dst.duration, src.duration ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::liveliness_type & dst, const ::iccm::LivelinessQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());

  if (src.lease_duration_p ())
    DDS_Servant <T>::apply (dst.lease_duration, src.lease_duration ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::reliability_type & dst, const ::iccm::ReliabilityQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());

  if (src.max_blocking_time_p ())
    DDS_Servant <T>::apply (dst.max_blocking_time, src.max_blocking_time ());

  #ifdef ICCM_DDS_SUPPORTS_SYNCHRONOUS_RELIABILITY_QOS
  if (src.synchronous ())
    dst.synchronous = src.synchronous ();
  #endif
}

template <typename T>
void DDS_Servant <T>::apply (typename T::destination_order_type & dst, const ::iccm::DestinationOrderQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::history_type & dst, const ::iccm::HistoryQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());

  if (src.depth_p ())
    dst.depth = static_cast <CORBA::Long> (src.depth ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::resource_limits_type & dst, const ::iccm::ResourceLimitsQosPolicy & src)
{
  if (src.max_samples_p ())
    dst.max_samples = static_cast <CORBA::Long> (src.max_samples ());

  if (src.max_instances_p ())
    dst.max_instances = static_cast <CORBA::Long> (src.max_instances ());

  if (src.max_samples_per_instance_p ())
    dst.max_samples_per_instance = static_cast <CORBA::Long> (src.max_samples_per_instance ());

#ifdef ICCM_DDS_SUPPORTS_INITIAL_RESOURCE_LIMITS
  if (src.initial_samples_p ())
    dst.initial_samples = static_cast <CORBA::Long> (src.initial_samples ());

  if (src.initial_instances_p ())
    dst.initial_instances = static_cast <CORBA::Long> (src.initial_instances ());
#endif
}

template <typename T>
void DDS_Servant <T>::apply (typename T::transport_priority_type & dst, const ::iccm::TransportPriorityQosPolicy & src)
{
  if (src.value_p ())
    dst.value = static_cast <CORBA::Long> (src.value ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::lifespan_type & dst, const ::iccm::LifespanQosPolicy & src)
{
  if (src.duration_p ())
    DDS_Servant <T>::apply (dst.duration, src.duration ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::ownership_type & dst, const ::iccm::OwnershipQosPolicy & src)
{
  if (src.kind_p ())
    DDS_Servant <T>::apply (dst.kind, src.kind ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::presentation_type & dst, const ::iccm::PresentationQosPolicy & src)
{
  if (src.access_scope_p ())
    DDS_Servant <T>::apply (dst.access_scope, src.access_scope ());

  if (src.coherent_access_p ())
    dst.coherent_access = src.coherent_access ();

  if (src.ordered_access_p ())
    dst.ordered_access = src.ordered_access ();
}

template <typename T>
void DDS_Servant <T>::apply (typename T::stringseq_type & dst, const ::iccm::StringSeq & src)
{
  T::copy_string (dst, src);
}

template <typename T>
void DDS_Servant <T>::apply (typename T::partition_type & dst, const ::iccm::PartitionQosPolicy & src)
{
  DDS_Servant <T>::apply (dst.name, src.name ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::group_data_type & dst, const ::iccm::GroupDataQosPolicy & src)
{
  // TODO add base64Binary support to XSC
}

template <typename T>
void DDS_Servant <T>::apply (typename T::user_data_type & dst, const ::iccm::UserDataQosPolicy & src)
{
  // TODO add base64Binary support to XSC
}

#ifdef ICCM_DDS_SUPPORTS_SHARE_QOS
template <typename T>
void DDS_Servant <T>::apply (typename T::share_type & dst, const ::iccm::ShareQosPolicy & src)
{
  if (src.name_p ())
    dst.name = src.name ().c_str ();

  if (src.enable_p ())
    dst.enable = src.enable ();
}
#endif

template <typename T>
void DDS_Servant <T>::apply (typename T::time_based_filter_type & dst, const ::iccm::TimeBasedFilterQosPolicy & src)
{
  if (src.minimum_separation_p ())
    DDS_Servant <T>::apply (dst.minimum_separation, src.minimum_separation ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::reader_data_lifecycle_type & dst, const ::iccm::ReaderDataLifecycleQosPolicy & src)
{
  if (src.autopurge_nowriter_samples_delay_p ())
    DDS_Servant <T>::apply (dst.autopurge_nowriter_samples_delay,
                            src.autopurge_nowriter_samples_delay ());

  if (src.autopurge_disposed_samples_delay_p ())
    DDS_Servant <T>::apply (dst.autopurge_disposed_samples_delay,
                            src.autopurge_disposed_samples_delay ());

  #ifdef ICCM_DDS_SUPPORTS_READER_INVALID_SAMPLES
  if (src.enable_invalid_samples_p ())
    dst.enable_invalid_samples = src.enable_invalid_samples ();
  #endif
}

#ifdef ICCM_DDS_SUPPORTS_SUBSCRIPTION_KEY_QOS
template <typename T>
void DDS_Servant <T>::apply (typename T::subscription_key_type & dst, const ::iccm::SubscriptionKeyQosPolicy & src)
{
  if (src.use_key_list_p ())
    dst.use_key_list = src.use_key_list ();

  if (src.key_list_p ())
    DDS_Servant <T>::apply (dst.key_list, src.key_list ());
}
#endif

#ifdef ICCM_DDS_SUPPORTS_READER_LIFESPAN_QOS
template <typename T>
void DDS_Servant <T>::apply (typename T::reader_lifespan_type & dst, const ::iccm::ReaderLifespanQosPolicy & src)
{
  if (src.use_lifespan_p ())
    dst.use_lifespan = src.use_lifespan ();

  if (src.duration_p ())
    DDS_Servant <T>::apply (dst.duration, src.duration ());
}
#endif

template <typename T>
void DDS_Servant <T>::apply (typename T::ownership_strength_type & dst, const ::iccm::OwnershipStrengthQosPolicy & src)
{
  if (src.value_p ())
    dst.value = static_cast <CORBA::Long> (src.value ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::writer_data_lifecycle_type & dst, const ::iccm::WriterDataLifecycleQosPolicy & src)
{
  if (src.autodispose_unregistered_instances_p ())
    dst.autodispose_unregistered_instances = src.autodispose_unregistered_instances ();

#ifdef ICCM_DDS_SUPPORTS_WRITER_AUTOPURGE_SUSPENDED_SAMPLES
  if (src.autopurge_suspended_samples_delay_p ())
    DDS_Servant <T>::apply (dst.autopurge_suspended_samples_delay, src.autopurge_suspended_samples_delay ());
#endif

#ifdef ICCM_DDS_SUPPORTS_WRITER_AUTOUNREGISTER
  if (src.autounregister_instance_delay_p ())
    DDS_Servant <T>::apply (dst.autounregister_instance_delay, src.autounregister_instance_delay ());
#endif
}

template <typename T>
void DDS_Servant <T>::apply (typename T::entity_factory_type & dst, const ::iccm::EntityFactoryQosPolicy & src)
{
  if (src.autoenable_created_entities_p ())
    dst.autoenable_created_entities = src.autoenable_created_entities ();
}

template <typename T>
void DDS_Servant <T>::apply (typename T::topicqos_type & dst, const ::iccm::TopicQos & src)
{
  if (src.durability_p ())
    DDS_Servant <T>::apply (dst.durability, src.durability ());

  if (src.durability_service_p ())
    DDS_Servant <T>::apply (dst.durability_service, src.durability_service ());

  if (src.deadline_p ())
    DDS_Servant <T>::apply (dst.deadline, src.deadline ());

  if (src.latency_budget_p ())
    DDS_Servant <T>::apply (dst.latency_budget, src.latency_budget ());

  if (src.liveliness_p ())
    DDS_Servant <T>::apply (dst.liveliness, src.liveliness ());

  if (src.reliability_p ())
    DDS_Servant <T>::apply (dst.reliability, src.reliability ());

  if (src.destination_order_p ())
    DDS_Servant <T>::apply (dst.destination_order, src.destination_order ());

  if (src.history_p ())
    DDS_Servant <T>::apply (dst.history, src.history ());

  if (src.resource_limits_p ())
    DDS_Servant <T>::apply (dst.resource_limits, src.resource_limits ());

  if (src.transport_priority_p ())
    DDS_Servant <T>::apply (dst.transport_priority, src.transport_priority ());

  if (src.lifespan_p ())
    DDS_Servant <T>::apply (dst.lifespan, src.lifespan ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::publisherqos_type & dst, const ::iccm::PublisherQos & src)
{
  if (src.presentation_p ())
    DDS_Servant <T>::apply (dst.presentation, src.presentation ());

  if (src.partition_p ())
    DDS_Servant <T>::apply (dst.partition, src.partition ());

  if (src.group_data_p ())
    DDS_Servant <T>::apply (dst.group_data, src.group_data ());

  if (src.entity_factory_p ())
    DDS_Servant <T>::apply (dst.entity_factory, src.entity_factory ());
}

template <typename T>
void DDS_Servant <T>::apply (typename T::subscriberqos_type & dst, const ::iccm::SubscriberQos & src)
{
  if (src.presentation_p ())
    DDS_Servant <T>::apply (dst.presentation, src.presentation ());

  if (src.partition_p ())
    DDS_Servant <T>::apply (dst.partition, src.partition ());

  if (src.group_data_p ())
    DDS_Servant <T>::apply (dst.group_data, src.group_data ());

  if (src.entity_factory_p ())
    DDS_Servant <T>::apply (dst.entity_factory, src.entity_factory ());

#ifdef ICCM_DDS_SUPPORTS_SHARE_QOS
  if (src.share_p ())
    DDS_Servant <T>::apply (dst.share, src.share ());
#endif
}

template <typename T>
void DDS_Servant <T>::apply (typename T::datareaderqos_type & dst, const ::iccm::DataReaderQos & src)
{
  if (src.durability_p ())
    DDS_Servant <T>::apply (dst.durability, src.durability ());

  if (src.deadline_p ())
    DDS_Servant <T>::apply (dst.deadline, src.deadline ());

  if (src.latency_budget_p ())
    DDS_Servant <T>::apply (dst.latency_budget, src.latency_budget ());

  if (src.liveliness_p ())
    DDS_Servant <T>::apply (dst.liveliness, src.liveliness ());

  if (src.reliability_p ())
    DDS_Servant <T>::apply (dst.reliability, src.reliability ());

  if (src.destination_order_p ())
    DDS_Servant <T>::apply (dst.destination_order, src.destination_order ());

  if (src.history_p ())
    DDS_Servant <T>::apply (dst.history, src.history ());

  if (src.resource_limits_p ())
    DDS_Servant <T>::apply (dst.resource_limits, src.resource_limits ());

  if (src.user_data_p ())
    DDS_Servant <T>::apply (dst.user_data, src.user_data ());

  if (src.ownership_p ())
    DDS_Servant <T>::apply (dst.ownership, src.ownership ());

  if (src.time_based_filter_p ())
    DDS_Servant <T>::apply (dst.time_based_filter, src.time_based_filter ());

  if (src.reader_data_lifecycle_p ())
    DDS_Servant <T>::apply (dst.reader_data_lifecycle, src.reader_data_lifecycle ());

#ifdef ICCM_DDS_SUPPORTS_SUBSCRIPTION_KEY_QOS
  if (src.subscription_keys_p ())
    DDS_Servant <T>::apply (dst.subscription_keys, src.subscription_keys ());
#endif

#ifdef ICCM_DDS_SUPPORTS_READER_LIFESPAN_QOS
  if (src.reader_lifespan_p ())
    DDS_Servant <T>::apply (dst.reader_lifespan, src.reader_lifespan ());
#endif

#ifdef ICCM_DDS_SUPPORTS_SHARE_QOS
  if (src.share_p ())
    DDS_Servant <T>::apply (dst.share, src.share ());
#endif
}

template <typename T>
void DDS_Servant <T>::apply (typename T::datawriterqos_type & dst, const ::iccm::DataWriterQos & src)
{
  if (src.durability_p ())
    DDS_Servant <T>::apply (dst.durability, src.durability ());

  if (src.deadline_p ())
    DDS_Servant <T>::apply (dst.deadline, src.deadline ());

  if (src.latency_budget_p ())
    DDS_Servant <T>::apply (dst.latency_budget, src.latency_budget ());

  if (src.liveliness_p ())
    DDS_Servant <T>::apply (dst.liveliness, src.liveliness ());

  if (src.reliability_p ())
    DDS_Servant <T>::apply (dst.reliability, src.reliability ());

  if (src.destination_order_p ())
    DDS_Servant <T>::apply (dst.destination_order, src.destination_order ());

  if (src.history_p ())
    DDS_Servant <T>::apply (dst.history, src.history ());

  if (src.resource_limits_p ())
    DDS_Servant <T>::apply (dst.resource_limits, src.resource_limits ());

  if (src.transport_priority_p ())
    DDS_Servant <T>::apply (dst.transport_priority, src.transport_priority ());

  if (src.lifespan_p ())
    DDS_Servant <T>::apply (dst.lifespan, src.lifespan ());

  if (src.user_data_p ())
    DDS_Servant <T>::apply (dst.user_data, src.user_data ());

  if (src.ownership_p ())
    DDS_Servant <T>::apply (dst.ownership, src.ownership ());

  if (src.ownership_strength_p ())
    DDS_Servant <T>::apply (dst.ownership_strength, src.ownership_strength ());

  if (src.writer_data_lifecycle_p ())
    DDS_Servant <T>::apply (dst.writer_data_lifecycle, src.writer_data_lifecycle ());

#ifdef ICCM_DDS_SUPPORTS_WRITER_PROTOCOL_QOS
  if (src.protocol_p ())
    DDS_Servant <T>::apply (dst.protocol, src.protocol ());
#endif

}

template <typename T>
void DDS_Servant <T>::apply (typename T::duration_type & dst, const double & src)
{
  dst.sec = static_cast < ::CORBA::Long > (src);

  const double remainder = src - static_cast <double> (dst.sec);
  dst.nanosec = static_cast < ::CORBA::Long > (remainder) * ACE_ONE_SECOND_IN_NSECS;
}
}
