// $Id$

#include "OpenSplice_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

#include "cuts/iccm/ddsxml/dds.h"

#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"

#define ICCM_DDS_DEFAULT_PUBLISHER "@default"
#define ICCM_DDS_DEFAULT_SUBSCRIBER "@default"
#define ICCM_DDS_DEFAULT_TOPIC "@default"

namespace boost
{
namespace detail
{
  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::TopicQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::TopicQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::PublisherQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::SubscriberQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::DataReaderQos type;
  };

  template < >
  struct smart_ptr_pointee < ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > >
  {
    typedef ::iccm::DataWriterQos type;
  };
}
}

///////////////////////////////////////////////////////////////////////////////
// Simple Type Definitions [*PolicyKind]
///////////////////////////////////////////////////////////////////////////////

void operator <<= (DDS::Duration_t & dst, const double & src)
{
  dst.sec = static_cast < ::CORBA::Long > (src);

  const double remainder = src - static_cast <double> (dst.sec);
  dst.nanosec = static_cast < ::CORBA::Long > (remainder) * ACE_ONE_SECOND_IN_NSECS;
}

void operator <<= (DDS::StringSeq & dst, const ::iccm::StringSeq & src)
{
  dst.length (src.count_item ());

  ::iccm::StringSeq::item_const_iterator
    iter = src.begin_item (), iter_end = src.end_item ();

  for (size_t i = 0; iter != iter_end; ++ iter, ++ i)
    dst[i] = (*iter)->c_str ();
}

void operator <<= (DDS::HistoryQosPolicyKind & dst, const ::iccm::HistoryQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS_l:
    dst = DDS::KEEP_ALL_HISTORY_QOS;
    break;

  case ::iccm::HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS_l:
    dst = DDS::KEEP_LAST_HISTORY_QOS;
    break;
  }
}

void operator <<= (DDS::SchedulingClassQosPolicyKind & dst, const ::iccm::SchedulingClassQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_DEFAULT_l:
    dst = DDS::SCHEDULE_DEFAULT;
    break;

  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_TIMESHARING_l:
    dst = DDS::SCHEDULE_TIMESHARING;
    break;

  case ::iccm::SchedulingClassQosPolicyKind::SCHEDULING_REALTIME_l:
    dst = DDS::SCHEDULE_REALTIME;
    break;
  }
}

void operator <<= (DDS::SchedulingPriorityQosPolicyKind & dst, const ::iccm::SchedulingPriorityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::SchedulingPriorityQosPolicyKind::PRIORITY_RELATIVE_l:
    dst = DDS::PRIORITY_RELATIVE;
    break;

  case ::iccm::SchedulingPriorityQosPolicyKind::PRIORITY_ABSOLUTE_l:
    dst = DDS::PRIORITY_ABSOLUTE;
    break;
  }
}

void operator <<= (DDS::LivelinessQosPolicyKind & dst, const ::iccm::LivelinessQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS_l:
    dst = DDS::AUTOMATIC_LIVELINESS_QOS;
    break;

  case ::iccm::LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l:
    dst = DDS::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
    break;

  case ::iccm::LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS_l:
    dst = DDS::MANUAL_BY_TOPIC_LIVELINESS_QOS;
    break;
  }
}

void operator <<= (DDS::DurabilityQosPolicyKind & dst, const ::iccm::DurabilityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS_l:
    dst = DDS::PERSISTENT_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS_l:
    dst = DDS::TRANSIENT_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS_l:
    dst = DDS::TRANSIENT_LOCAL_DURABILITY_QOS;
    break;

  case ::iccm::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS_l:
    dst = DDS::VOLATILE_DURABILITY_QOS;
    break;
  }
}

void operator <<= (DDS::ReliabilityQosPolicyKind & dst, const ::iccm::ReliabilityQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS_l:
    dst = DDS::BEST_EFFORT_RELIABILITY_QOS;
    break;

  case ::iccm::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS_l:
    dst = DDS::RELIABLE_RELIABILITY_QOS;
    break;
  }
}

void operator <<= (DDS::DestinationOrderQosPolicyKind & dst, const ::iccm::DestinationOrderQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l:
    dst = DDS::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
    break;

  case ::iccm::DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l:
    dst = DDS::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
    break;
  }
}

void operator <<= (DDS::OwnershipQosPolicyKind & dst, const ::iccm::OwnershipQosPolicyKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS_l:
    dst = DDS::EXCLUSIVE_OWNERSHIP_QOS;
    break;

  case ::iccm::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS_l:
    dst = DDS::SHARED_OWNERSHIP_QOS;
    break;
  }
}

void operator <<= (DDS::PresentationQosPolicyAccessScopeKind & dst, const ::iccm::PresentationQosPolicyAccessScopeKind & src)
{
  switch (src.integral ())
  {
  case ::iccm::PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS_l:
    dst = DDS::GROUP_PRESENTATION_QOS;
    break;

  case ::iccm::PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS_l:
    dst = DDS::INSTANCE_PRESENTATION_QOS;
    break;

  case ::iccm::PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS_l:
    dst = DDS::TOPIC_PRESENTATION_QOS;
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Complex Type Definitions [*Policy]
///////////////////////////////////////////////////////////////////////////////

void operator <<= (DDS::EntityFactoryQosPolicy & dst, const ::iccm::EntityFactoryQosPolicy & src)
{
  if (src.autoenable_created_entities_p ())
    dst.autoenable_created_entities = src.autoenable_created_entities ();
}

void operator <<= (DDS::SchedulingClassQosPolicy & dst, const ::iccm::SchedulingClassQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();
}

void operator <<= (DDS::SchedulingPriorityQosPolicy & dst, const ::iccm::SchedulingPriorityQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();
}

void operator <<= (DDS::SchedulingQosPolicy & dst, const ::iccm::SchedulingQosPolicy & src)
{
  if (src.scheduling_class_p ())
    dst.scheduling_class <<= src.scheduling_class ();

  if (src.scheduling_priority_kind_p ())
    dst.scheduling_priority_kind <<= src.scheduling_priority_kind ();

  if (src.scheduling_priority_p ())
    dst.scheduling_priority = static_cast <CORBA::Long> (src.scheduling_priority ());
}

void operator <<= (DDS::DurabilityQosPolicy & dst, const ::iccm::DurabilityQosPolicy & src)
{
  dst.kind <<= src.kind ();
}

void operator <<= (DDS::DurabilityServiceQosPolicy & dst, const ::iccm::DurabilityServiceQosPolicy & src)
{
  if (src.service_cleanup_delay_p ())
    dst.service_cleanup_delay <<= src.service_cleanup_delay ();

  if (src.history_kind_p ())
    dst.history_kind <<= src.history_kind ();

  if (src.history_depth_p ())
    dst.history_depth = static_cast <CORBA::Long> (src.history_depth ());

  if (src.max_samples_p ())
    dst.max_samples = static_cast <CORBA::Long> (src.max_samples ());

  if (src.max_instances_p ())
    dst.max_instances = static_cast <CORBA::Long> (src.max_instances ());

  if (src.max_samples_per_instance_p ())
    dst.max_samples_per_instance = static_cast <CORBA::Long> (src.max_samples_per_instance ());
}

void operator <<= (DDS::DeadlineQosPolicy & dst, const ::iccm::DeadlineQosPolicy & src)
{
  if (src.period_p ())
    dst.period <<= src.period ();
}

void operator <<= (DDS::LatencyBudgetQosPolicy & dst, const ::iccm::LatencyBudgetQosPolicy & src)
{
  if (src.duration_p ())
    dst.duration <<= src.duration ();
}

void operator <<= (DDS::LivelinessQosPolicy & dst, const ::iccm::LivelinessQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();

  if (src.lease_duration_p ())
    dst.lease_duration <<= src.lease_duration ();
}

void operator <<= (DDS::ReliabilityQosPolicy & dst, const ::iccm::ReliabilityQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();

  if (src.max_blocking_time_p ())
    dst.max_blocking_time <<= src.max_blocking_time ();

  if (src.synchronous ())
    dst.synchronous = src.synchronous ();
}

void operator <<= (DDS::DestinationOrderQosPolicy & dst, const ::iccm::DestinationOrderQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();
}

void operator <<= (DDS::HistoryQosPolicy & dst, const ::iccm::HistoryQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();

  if (src.depth_p ())
    dst.depth = static_cast <CORBA::Long> (src.depth ());
}

void operator <<= (DDS::ResourceLimitsQosPolicy & dst, const ::iccm::ResourceLimitsQosPolicy & src)
{
  if (src.max_samples_p ())
    dst.max_samples = static_cast <CORBA::Long> (src.max_samples ());

  if (src.max_instances_p ())
    dst.max_instances = static_cast <CORBA::Long> (src.max_instances ());

  if (src.max_samples_per_instance_p ())
    dst.max_samples_per_instance = static_cast <CORBA::Long> (src.max_samples_per_instance ());
}

void operator <<= (DDS::TransportPriorityQosPolicy & dst, const ::iccm::TransportPriorityQosPolicy & src)
{
  if (src.value_p ())
    dst.value = static_cast <CORBA::Long> (src.value ());
}

void operator <<= (DDS::LifespanQosPolicy & dst, const ::iccm::LifespanQosPolicy & src)
{
  if (src.duration_p ())
    dst.duration <<= src.duration ();
}

void operator <<= (DDS::OwnershipQosPolicy & dst, const ::iccm::OwnershipQosPolicy & src)
{
  if (src.kind_p ())
    dst.kind <<= src.kind ();
}

void operator <<= (DDS::PresentationQosPolicy & dst, const ::iccm::PresentationQosPolicy & src)
{
  if (src.access_scope_p ())
    dst.access_scope <<= src.access_scope ();

  if (src.coherent_access_p ())
    dst.coherent_access = src.coherent_access ();

  if (src.ordered_access_p ())
    dst.ordered_access = src.ordered_access ();
}

void operator <<= (DDS::PartitionQosPolicy & dst, const ::iccm::PartitionQosPolicy & src)
{
  dst.name <<= src.name ();
}

void operator <<= (DDS::GroupDataQosPolicy & dst, const ::iccm::GroupDataQosPolicy & src)
{
  // TODO add base64Binary support to XSC
}

void operator <<= (DDS::UserDataQosPolicy & dst, const ::iccm::UserDataQosPolicy & src)
{
  // TODO add base64Binary support to XSC
}

void operator <<= (DDS::ShareQosPolicy & dst, const ::iccm::ShareQosPolicy & src)
{
  if (src.name_p ())
    dst.name = src.name ().c_str ();

  if (src.enable_p ())
    dst.enable = src.enable ();
}

void operator <<= (DDS::TimeBasedFilterQosPolicy & dst, const ::iccm::TimeBasedFilterQosPolicy & src)
{
  if (src.minimum_separation_p ())
    dst.minimum_separation <<= src.minimum_separation ();
}

void operator <<= (DDS::ReaderDataLifecycleQosPolicy & dst, const ::iccm::ReaderDataLifecycleQosPolicy & src)
{
  if (src.autopurge_nowriter_samples_delay_p ())
    dst.autopurge_nowriter_samples_delay <<= src.autopurge_nowriter_samples_delay ();

  if (src.autopurge_disposed_samples_delay_p ())
    dst.autopurge_disposed_samples_delay <<= src.autopurge_disposed_samples_delay ();

  if (src.enable_invalid_samples_p ())
    dst.enable_invalid_samples = src.enable_invalid_samples ();
}

void operator <<= (DDS::SubscriptionKeyQosPolicy & dst, const ::iccm::SubscriptionKeyQosPolicy & src)
{
  if (src.use_key_list_p ())
    dst.use_key_list = src.use_key_list ();

  if (src.key_list_p ())
    dst.key_list <<= src.key_list ();
}

void operator <<= (DDS::ReaderLifespanQosPolicy & dst, const ::iccm::ReaderLifespanQosPolicy & src)
{
  if (src.use_lifespan_p ())
    dst.use_lifespan = src.use_lifespan ();

  if (src.duration_p ())
    dst.duration <<= src.duration ();
}

void operator <<= (DDS::OwnershipStrengthQosPolicy & dst, const ::iccm::OwnershipStrengthQosPolicy & src)
{
  if (src.value_p ())
    dst.value = static_cast <CORBA::Long> (src.value ());
}

void operator <<= (DDS::WriterDataLifecycleQosPolicy & dst, const ::iccm::WriterDataLifecycleQosPolicy & src)
{
  if (src.autodispose_unregistered_instances_p ())
    dst.autodispose_unregistered_instances = src.autodispose_unregistered_instances ();

  if (src.autopurge_suspended_samples_delay_p ())
    dst.autopurge_suspended_samples_delay <<= src.autopurge_suspended_samples_delay ();

  if (src.autounregister_instance_delay_p ())
    dst.autounregister_instance_delay <<= src.autounregister_instance_delay ();
}

///////////////////////////////////////////////////////////////////////////////
// Entity QoS Definitions [*Qos]
///////////////////////////////////////////////////////////////////////////////

void operator <<= (DDS::TopicQos & dst, const ::iccm::TopicQos & src)
{
  if (src.durability_p ())
    dst.durability <<= src.durability ();

  if (src.durability_service_p ())
    dst.durability_service <<= src.durability_service ();

  if (src.deadline_p ())
    dst.deadline <<= src.deadline ();

  if (src.latency_budget_p ())
    dst.latency_budget <<= src.latency_budget ();

  if (src.liveliness_p ())
    dst.liveliness <<= src.liveliness ();

  if (src.reliability_p ())
    dst.reliability <<= src.reliability ();

  if (src.destination_order_p ())
    dst.destination_order <<= src.destination_order ();

  if (src.history_p ())
    dst.history <<= src.history ();

  if (src.resource_limits_p ())
    dst.resource_limits <<= src.resource_limits ();

  if (src.transport_priority_p ())
    dst.transport_priority <<= src.transport_priority ();

  if (src.lifespan_p ())
    dst.lifespan <<= src.lifespan ();
}

void operator <<= (DDS::PublisherQos & dst, const ::iccm::PublisherQos & src)
{
  if (src.presentation_p ())
    dst.presentation <<= src.presentation ();

  if (src.partition_p ())
    dst.partition <<= src.partition ();

  if (src.group_data_p ())
    dst.group_data <<= src.group_data ();

  if (src.entity_factory_p ())
    dst.entity_factory <<= src.entity_factory ();
}

void operator <<= (DDS::SubscriberQos & dst, const ::iccm::SubscriberQos & src)
{
  if (src.presentation_p ())
    dst.presentation <<= src.presentation ();

  if (src.partition_p ())
    dst.partition <<= src.partition ();

  if (src.group_data_p ())
    dst.group_data <<= src.group_data ();

  if (src.entity_factory_p ())
    dst.entity_factory <<= src.entity_factory ();

  if (src.share_p ())
    dst.share <<= src.share ();
}

void operator <<= (DDS::DataReaderQos & dst, const ::iccm::DataReaderQos & src)
{
  if (src.durability_p ())
    dst.durability <<= src.durability ();

  if (src.deadline_p ())
    dst.deadline <<= src.deadline ();

  if (src.latency_budget_p ())
    dst.latency_budget <<= src.latency_budget ();

  if (src.liveliness_p ())
    dst.liveliness <<= src.liveliness ();

  if (src.reliability_p ())
    dst.reliability <<= src.reliability ();

  if (src.destination_order_p ())
    dst.destination_order <<= src.destination_order ();

  if (src.history_p ())
    dst.history <<= src.history ();

  if (src.resource_limits_p ())
    dst.resource_limits <<= src.resource_limits ();

  if (src.user_data_p ())
    dst.user_data <<= src.user_data ();

  if (src.ownership_p ())
    dst.ownership <<= src.ownership ();

  if (src.time_based_filter_p ())
    dst.time_based_filter <<= src.time_based_filter ();

  if (src.reader_data_lifecycle_p ())
    dst.reader_data_lifecycle <<= src.reader_data_lifecycle ();

  if (src.subscription_keys_p ())
    dst.subscription_keys <<= src.subscription_keys ();

  if (src.reader_lifespan_p ())
    dst.reader_lifespan <<= src.reader_lifespan ();

  if (src.share_p ())
    dst.share <<= src.share ();
}

void operator <<= (DDS::DataWriterQos & dst, const ::iccm::DataWriterQos & src)
{
  if (src.durability_p ())
    dst.durability <<= src.durability ();

  if (src.deadline_p ())
    dst.deadline <<= src.deadline ();

  if (src.latency_budget_p ())
    dst.latency_budget <<= src.latency_budget ();

  if (src.liveliness_p ())
    dst.liveliness <<= src.liveliness ();

  if (src.reliability_p ())
    dst.reliability <<= src.reliability ();

  if (src.destination_order_p ())
    dst.destination_order <<= src.destination_order ();

  if (src.history_p ())
    dst.history <<= src.history ();

  if (src.resource_limits_p ())
    dst.resource_limits <<= src.resource_limits ();

  if (src.transport_priorty_p ())
    dst.transport_priority <<= src.transport_priorty ();

  if (src.lifespan_p ())
    dst.lifespan <<= src.lifespan ();

  if (src.user_data_p ())
    dst.user_data <<= src.user_data ();

  if (src.ownership_p ())
    dst.ownership <<= src.ownership ();

  if (src.ownership_strength_p ())
    dst.ownership_strength <<= src.ownership_strength ();

  if (src.writer_data_lifecycle_p ())
    dst.writer_data_lifecycle <<= src.writer_data_lifecycle ();
}

namespace iCCM
{

//
// OpenSplice_Servant
//
OpenSplice_Servant::OpenSplice_Servant (const char * name)
: Servant (name)
{
  // Create the participant for this servant.
  ::DDS::DomainParticipantFactory_var factory =
    ::DDS::DomainParticipantFactory::get_instance ();

  this->participant_ =
    factory->create_participant (0,
                                 PARTICIPANT_QOS_DEFAULT,
                                 0,
                                 ::DDS::ANY_STATUS);
}

//
// configure
//
void OpenSplice_Servant::configure (const ::iccm::DomainParticipantQos & src)
{
  // Configure the domain participant QoS.
  ::DDS::DomainParticipantQos dst;
  this->participant_->get_qos (dst);

  if (src.entity_factory_p ())
    dst.entity_factory <<= src.entity_factory ();

  if (src.watchdog_scheduling_p ())
    dst.watchdog_scheduling <<= src.watchdog_scheduling ();

  if (src.listener_scheduling_p ())
    dst.listener_scheduling <<= src.listener_scheduling ();

  this->participant_->set_qos (dst);

  // Configure each of the entities in the using information found in
  // the configuration file.
  namespace lambda = boost::lambda;

  std::for_each (src.begin_topic (),
                 src.end_topic (),
                 lambda::bind (&OpenSplice_Servant::configure_topic, this, *lambda::_1));

  std::for_each (src.begin_publisher (),
                 src.end_publisher (),
                 lambda::bind (&OpenSplice_Servant::configure_publisher, this, *lambda::_1));

  std::for_each (src.begin_subscriber (),
                 src.end_subscriber (),
                 lambda::bind (&OpenSplice_Servant::configure_subscriber, this, *lambda::_1));

  std::for_each (src.begin_datareader (),
                 src.end_datareader (),
                 lambda::bind (&OpenSplice_Servant::configure_datareader, this, *lambda::_1));

  std::for_each (src.begin_datawriter (),
                 src.end_datawriter (),
                 lambda::bind (&OpenSplice_Servant::configure_datawriter, this, *lambda::_1));

  // Finally, configure all the remaining ports/entities.
  this->configure ();
}

//
// configure_topic
//
void OpenSplice_Servant::configure_topic (const ::iccm::TopicQos & value)
{
  ::DDS::TopicQos * qos = 0;
  ACE_NEW_THROW_EX (qos,
                    ::DDS::TopicQos (TOPIC_QOS_DEFAULT),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <::DDS::TopicQos> auto_clean (qos);

  *qos <<= value;

  if (0 == this->topic_qos_.bind (value.name ().c_str (), qos))
    auto_clean.release ();
}

//
// configure_publisher
//
void OpenSplice_Servant::
configure_publisher (const ::iccm::PublisherQos & value)
{
  // We are either setting the values for the default publisher, or we
  // are setting the values for new one.
  ::DDS::Publisher_var publisher;

  if (value.name () == ICCM_DDS_DEFAULT_PUBLISHER)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring default publisher\n")));

    publisher = ::DDS::Publisher::_duplicate (this->publisher_.in ());
  }
  else
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring publisher <%s>\n"),
                value.name ().c_str ()));

    // Create a new publisher, and save it for later usage.
    publisher =
      this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                            ::DDS::PublisherListener::_nil (),
                                            ::DDS::ANY_STATUS);

    this->publishers_.bind (value.name ().c_str (), publisher);
  }


  // Set the publisher's QoS properties.
  DDS::PublisherQos current;
  publisher->get_qos (current);

  current <<= value;

  publisher->set_qos (current);
}

//
// configure_subscriber
//
void OpenSplice_Servant::
configure_subscriber (const ::iccm::SubscriberQos & value)
{
  // We are either setting the values for the default subscriber, or we
  // are setting the values for new one.
  ::DDS::Subscriber_var subscriber;

  if (value.name () == ICCM_DDS_DEFAULT_SUBSCRIBER)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring default subscriber\n")));

    subscriber = ::DDS::Subscriber::_duplicate (this->subscriber_.in ());
  }
  else
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring subscriber <%s>\n"),
                value.name ().c_str ()));

    // Create a new subscriber, and save it for later usage.
    subscriber =
      this->participant_->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                             ::DDS::SubscriberListener::_nil (),
                                             ::DDS::ANY_STATUS);

    this->subscribers_.bind (value.name ().c_str (), subscriber);
  }

  // Set the subscriber's QoS properties.
  ::DDS::SubscriberQos current;
  subscriber->get_qos (current);

  current <<= value;

  subscriber->set_qos (current);
}

//
// configure_datareader
//
void OpenSplice_Servant::
configure_datareader (const ::iccm::DataReaderQos & value)
{
  // Locate the data reader's subscriber. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  ::DDS::Subscriber_var subscriber;

  if (value.subscriber () == ICCM_DDS_DEFAULT_SUBSCRIBER)
  {
    subscriber = ::DDS::Subscriber::_duplicate (this->subscriber_.in ());
  }
  else if (0 != this->subscribers_.find (value.subscriber ().c_str (), subscriber))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate subscriber <%s> ")
                ACE_TEXT ("in <%s>; using default subscriber\n"),
                value.subscriber ().c_str (),
                this->name_.c_str ()));

    subscriber = ::DDS::Subscriber::_duplicate (this->subscriber_.in ());
  }

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (topic == ICCM_DDS_DEFAULT_TOPIC)
    topic_qos = ::DDS::DomainParticipantFactory::topic_qos_default ();
  else if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
    throw ::CORBA::INTERNAL ();

  // The way we configure the data reader's QoS parameters is different
  // from the data writer. This is because the a data reader is not
  // created until a connection is made between an input/output port.
  // We therefore need to initialize the data reader's QoS parameters
  // and the consumer will use it when instantiating the data readers.
  ::DDS::DataReaderQos current (DATAREADER_QOS_DEFAULT);
  current <<= value;

  this->configure_eventconsumer (value.name ().c_str (),
                                 current,
                                 topic_qos,
                                 subscriber.in ());
}

//
// configure_datawriter
//
void OpenSplice_Servant::
configure_datawriter (const ::iccm::DataWriterQos & value)
{
  // Locate the data writer's publisher. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  ::DDS::Publisher_var publisher;

  if (value.publisher () == ICCM_DDS_DEFAULT_PUBLISHER)
  {
    publisher = ::DDS::Publisher::_duplicate (this->publisher_.in ());
  }
  else if (0 != this->publishers_.find (value.publisher ().c_str (), publisher))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate publisher <%s> ")
                ACE_TEXT ("in <%s>; using default publisher\n"),
                value.publisher ().c_str (),
                this->name_.c_str ()));

    publisher = ::DDS::Publisher::_duplicate (this->publisher_.in ());
  }

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (topic == ICCM_DDS_DEFAULT_TOPIC)
    topic_qos = ::DDS::DomainParticipantFactory::topic_qos_default ();
  else if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
    throw ::CORBA::INTERNAL ();

  // Create the DDS writer entity.
  ::DDS::DataWriter_var writer =
    this->create_datawriter (value.name ().c_str (),
                             *topic_qos,
                             publisher.in ());

  if (!CORBA::is_nil (writer.in ()))
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring data writer ")
                ACE_TEXT ("<%s> of <%s>\n"),
                value.name ().c_str (),
                this->name_.c_str ()));

    // Configure the data writer's QoS properties.
    ::DDS::DataWriterQos current;
    writer->get_qos (current);

    current <<= value;

    writer->set_qos (current);
  }
  else
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to create data writer ")
                ACE_TEXT ("for <%s> port\n"),
                value.name ().c_str ()));
  }
}

}
