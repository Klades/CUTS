// ReaderLifespanQosPolicy.cpp 3548 2014-04-08 15:20:43Z dfeiock $

#include "CoreDX_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "CoreDX_Servant.inl"
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
  dst.resize (src.count_item ());

  ::iccm::StringSeq::item_const_iterator
    iter = src.begin_item (), iter_end = src.end_item ();

  for (size_t i = 0; iter != iter_end; ++ iter, ++ i)
    dst[i] = ACE_OS::strdup ((*iter)->c_str ());
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
}

void operator <<= (DDS::DataWriterQos & dst, const ::iccm::DataWriterQos & src)
{
//  if (src.durability_p ())
//    dst.durability <<= src.durability ();

  if (src.deadline_p ())
    dst.deadline <<= src.deadline ();

  if (src.latency_budget_p ())
    dst.latency_budget <<= src.latency_budget ();

//  if (src.liveliness_p ())
//    dst.liveliness <<= src.liveliness ();

//  if (src.reliability_p ())
//    dst.reliability <<= src.reliability ();

//  if (src.destination_order_p ())
//    dst.destination_order <<= src.destination_order ();

//  if (src.history_p ())
//    dst.history <<= src.history ();

//  if (src.resource_limits_p ())
//    dst.resource_limits <<= src.resource_limits ();

  if (src.transport_priority_p ())
    dst.transport_priority <<= src.transport_priority ();

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
// configure
//
void CoreDX_Servant::configure (const ::iccm::DomainParticipantQos & value)
{

  // Perform the default configuration.
  this->do_default_configure ();

  // Configure the domain participant QoS.
  ::DDS::DomainParticipantQos qos;
  this->participant_->get_qos (&qos);

  if (value.entity_factory_p ())
    qos.entity_factory <<= value.entity_factory ();

//  Temporarily commenting these QoS parameters.  They are immutable after
//  the participant is created, causing warnings in the ospl logs.
//  if (value.watchdog_scheduling_p ())
//    qos.watchdog_scheduling <<= value.watchdog_scheduling ();
//
//  if (value.listener_scheduling_p ())
//    qos.listener_scheduling <<= value.listener_scheduling ();

  this->participant_->set_qos (qos);

  // Configure each of the entities in the using information found in
  // the configuration file.
  namespace lambda = boost::lambda;

  std::for_each (value.begin_topic (),
                 value.end_topic (),
                 lambda::bind (&CoreDX_Servant::configure_topic, this, *lambda::_1));

  std::for_each (value.begin_publisher (),
                 value.end_publisher (),
                 lambda::bind (&CoreDX_Servant::configure_publisher, this, *lambda::_1));

  std::for_each (value.begin_subscriber (),
                 value.end_subscriber (),
                 lambda::bind (&CoreDX_Servant::configure_subscriber, this, *lambda::_1));

  std::for_each (value.begin_datareader (),
                 value.end_datareader (),
                 lambda::bind (&CoreDX_Servant::configure_datareader, this, *lambda::_1));

  std::for_each (value.begin_datawriter (),
                 value.end_datawriter (),
                 lambda::bind (&CoreDX_Servant::configure_datawriter, this, *lambda::_1));

  // Finally, configure all the remaining ports/entities.
  this->configure ();
}

//
// configure_topic
//
void CoreDX_Servant::configure_topic (const ::iccm::TopicQos & value)
{
  ::DDS::TopicQos * qos = 0;
  ACE_NEW_THROW_EX (qos,
                    ::DDS::TopicQos (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < ::DDS::TopicQos > auto_clean (qos);

  *qos <<= value;

  if (0 == this->topic_qos_.bind (value.name ().c_str (), qos))
    auto_clean.release ();
}

//
// configure_publisher
//
void CoreDX_Servant::
configure_publisher (const ::iccm::PublisherQos & value)
{
  // We are either setting the values for the default publisher, or we
  // are setting the values for new one.
  ::DDS::Publisher * publisher = 0;

  if (value.name () == ICCM_DDS_DEFAULT_PUBLISHER)
    publisher = this->publisher_;
  else
  {
    // Create a new publisher, and save it for later usage.
    publisher =
      this->participant_->create_publisher (::DDS::PUBLISHER_QOS_DEFAULT,
                                            NULL,
                                            0);

    this->publishers_.bind (value.name ().c_str (), publisher);
  }

  // Set the publisher's QoS properties.
  DDS::PublisherQos qos;

  qos <<= value;

  publisher->set_qos (qos);
}

//
// configure_subscriber
//
void CoreDX_Servant::
configure_subscriber (const ::iccm::SubscriberQos & value)
{
  // We are either setting the values for the default subscriber, or we
  // are setting the values for new one.
  ::DDS::Subscriber * subscriber = 0;

  if (value.name () == ICCM_DDS_DEFAULT_SUBSCRIBER)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring default subscriber\n")));

    subscriber = this->subscriber_;
  }
  else
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring subscriber <%s>\n"),
                value.name ().c_str ()));

    // Create a new subscriber, and save it for later usage.
    subscriber =
      this->participant_->create_subscriber (::DDS::SUBSCRIBER_QOS_DEFAULT,
                                             NULL,
                                             0);

    this->subscribers_.bind (value.name ().c_str (), subscriber);
  }

  // Set the subscriber's QoS properties.
  ::DDS::SubscriberQos qos;

  qos <<= value;

  subscriber->set_qos (qos);
}

//
// configure_datareader
//
void CoreDX_Servant::
configure_datareader (const ::iccm::DataReaderQos & value)
{
  // Locate the data reader's subscriber. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  ::DDS::Subscriber * subscriber = 0;

  if (value.subscriber () == ICCM_DDS_DEFAULT_SUBSCRIBER)
  {
    subscriber = this->subscriber_;
  }
  else if (0 != this->subscribers_.find (value.subscriber ().c_str (), subscriber))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate subscriber <%s> ")
                ACE_TEXT ("in <%s>; using default subscriber\n"),
                value.subscriber ().c_str (),
                this->name_.c_str ()));

    subscriber = this->subscriber_;
  }

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (topic == ICCM_DDS_DEFAULT_TOPIC)
  {
    this->participant_->get_default_topic_qos (temp);
    topic_qos = temp;
  }
  else if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
    throw ::CORBA::INTERNAL ();

  // The way we configure the data reader's QoS parameters is different
  // from the data writer. This is because the a data reader is not
  // created until a connection is made between an input/output port.
  // We therefore need to initialize the data reader's QoS parameters
  // and the consumer will use it when instantiating the data readers.
  ::DDS::DataReaderQos * qos = 0;
  ACE_NEW_THROW_EX (qos,
                    ::DDS::DataReaderQos (),
                    ::CORBA::NO_MEMORY ());

  ACE_Auto_Ptr < ::DDS::DataReaderQos > auto_clean (qos);

  *qos <<= value;

  if (0 == this->datareader_qos_.bind (value.name ().c_str (), qos))
    this->configure_eventconsumer (value.name ().c_str (),
                                   qos,
                                   topic_qos,
                                   subscriber,
                                   value.isprivate ());
}

//
// configure_datawriter
//
void CoreDX_Servant::
configure_datawriter (const ::iccm::DataWriterQos & value)
{
  // Locate the data writer's publisher. If we cannnot locate the
  // target publisher, then we are going to fall back to the default
  // publisher and its QoS. Of course, we are going to print a warning
  // message to the user so he/she can correct it! ;-)
  ::DDS::Publisher * publisher = 0;

  if (value.publisher () == ICCM_DDS_DEFAULT_PUBLISHER)
  {
    publisher = this->publisher_;
  }
  else if (0 != this->publishers_.find (value.publisher ().c_str (), publisher))
  {
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to locate publisher <%s> ")
                ACE_TEXT ("in <%s>; using default publisher\n"),
                value.publisher ().c_str (),
                this->name_.c_str ()));

    publisher = this->publisher_;
  }

  // Next, we need to locate the TopicQos object for this data writer.
  // If we cannot find the TopicQos object, we fallback to the default
  // data writer. Of course, we are going to notify the user via an exception.
  ::DDS::TopicQos * temp = 0;
  const ::DDS::TopicQos * topic_qos = 0;
  const std::string & topic = value.topic ();

  if (topic == ICCM_DDS_DEFAULT_TOPIC)
  {
    ACE_NEW_THROW_EX (temp,
                      ::DDS::TopicQos (),
                      ::CORBA::NO_MEMORY ());
    this->participant_->get_default_topic_qos (temp);
    topic_qos = temp;
  }
  else if (0 == this->topic_qos_.find (topic.c_str (), temp))
    topic_qos = temp;
  else
    throw ::CORBA::INTERNAL ();

  /// If topic_name is specified, use it.  Otherwise use the writer's name.
  std::string topic_name = value.name ();
  if (value.topic_name_p ())
    topic_name = value.topic_name ();

  // Create the DDS writer entity.
  ::DDS::DataWriter * writer =
    this->create_datawriter (value.name ().c_str (),
                             topic_name.c_str (),
                             *topic_qos,
                             publisher,
                             value.isprivate (),
                             value.isinstance ());

  if (!CORBA::is_nil (writer))
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - configuring data writer ")
                ACE_TEXT ("<%s> of <%s>\n"),
                value.name ().c_str (),
                this->name_.c_str ()));

    // Configure the data writer's QoS properties.
    ::DDS::DataWriterQos current;

    current <<= value;

    writer->set_qos (current);
  }
  else
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - failed to create data writer ")
                ACE_TEXT ("for <%s> port\n"),
                value.name ().c_str ()));
}

}