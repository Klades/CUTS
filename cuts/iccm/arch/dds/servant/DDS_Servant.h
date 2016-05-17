// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_SERVANT_H_
#define _ICCM_DDS_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"

#define ICCM_DDS_DEFAULT_PUBLISHER "@default"
#define ICCM_DDS_DEFAULT_SUBSCRIBER "@default"
#define ICCM_DDS_DEFAULT_TOPIC "@default"

#include "cuts/iccm/ddsxml/dds.h"

namespace iccm
{
  class DomainParticipantQos;
}

namespace iCCM
{

/**
 * @class DDS_Servant
 *
 * Base class for all DDS servant objects. This class enables the container
 * to send commands to the servant, such as configuration information for
 * each of its topics.
 */
template <typename T>
class DDS_Servant : public Servant
{
public:
  typedef typename T::corba_poa_eventconsumer_type corba_poa_eventconsumer_type;
  typedef typename T::eventconsumer_type eventconsumer_type;
  typedef typename T::publisher_type publisher_type;
  typedef typename T::publisher_table_type publisher_table_type;

  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::datawriter_ptr_type datawriter_ptr_type;
  typedef typename T::datareaderqos_type datareaderqos_type;
  typedef typename T::datawriterqos_type datawriterqos_type;
  typedef typename T::topicqos_type topicqos_type;
  typedef typename T::subscriber_ptr_type subscriber_ptr_type;
  typedef typename T::subscriber_var_type subscriber_var_type;
  typedef typename T::publisher_ptr_type publisher_ptr_type;
  typedef typename T::publisher_var_type publisher_var_type;

  /// Destructor.
  virtual ~DDS_Servant (void);

  /// Configuration hook from deployment plan
  virtual void handle_config (const ::Components::ConfigValues & values);

  /// Perform default configuration.
  virtual void configure (void);

  /**
   * Configure the servant with Qos properties. Each DDS implementation
   * must implement this method since (1) each has their on nomenclature
   * and (2) we want to hide all usage of XML and XSC, which is used by
   * the DDS configuration.
   *
   * @param[in]       qos         Qos configuration
   */
  virtual void configure (const ::iccm::DomainParticipantQos & qos) = 0;

  // {@ QoS Conversion Hooks
#ifdef ICCM_DDS_SUPPORTS_SCHEDULING_QOS
  static void apply (typename T::scheduling_class_kind_type & dst, const ::iccm::SchedulingClassQosPolicyKind & src);
  static void apply (typename T::scheduling_class_type & dst, const ::iccm::SchedulingClassQosPolicy & src);
  static void apply (typename T::scheduling_priority_kind_type & dst, const ::iccm::SchedulingPriorityQosPolicyKind & src);
  static void apply (typename T::scheduling_priority_type & dst, const ::iccm::SchedulingPriorityQosPolicy & src);
  static void apply (typename T::scheduling_type & dst, const ::iccm::SchedulingQosPolicy & src);
#endif

#ifdef ICCM_DDS_SUPPORTS_SHARE_QOS
  static void apply (typename T::share_type & dst, const ::iccm::ShareQosPolicy & src);
#endif

#ifdef ICCM_DDS_SUPPORTS_SUBSCRIPTION_KEY_QOS
  static void apply (typename T::subscription_key_type & dst, const ::iccm::SubscriptionKeyQosPolicy & src);
#endif

#ifdef ICCM_DDS_SUPPORTS_READER_LIFESPAN_QOS
  static void apply (typename T::reader_lifespan_type & dst, const ::iccm::ReaderLifespanQosPolicy & src);
#endif

#ifdef ICCM_DDS_SUPPORTS_WRITER_PROTOCOL_QOS
  static void apply (typename T::writer_protocol_type & dst, const ::iccm::DataWriterProtocolQosPolicy & src);
  static void apply (typename T::rtps_reliable_writer_protocol_type & dst, const ::iccm::RtpsReliableWriterProtocol & src);
#endif

  static void apply (typename T::duration_type & dst, const double & src);
  static void apply (typename T::stringseq_type & dst, const ::iccm::StringSeq & src);
  static void apply (typename T::history_kind_type & dst, const ::iccm::HistoryQosPolicyKind & src);
  static void apply (typename T::liveliness_kind_type & dst, const ::iccm::LivelinessQosPolicyKind & src);
  static void apply (typename T::durability_kind_type & dst, const ::iccm::DurabilityQosPolicyKind & src);
  static void apply (typename T::reliability_kind_type & dst, const ::iccm::ReliabilityQosPolicyKind & src);
  static void apply (typename T::destination_order_kind_type & dst, const ::iccm::DestinationOrderQosPolicyKind & src);
  static void apply (typename T::ownership_kind_type & dst, const ::iccm::OwnershipQosPolicyKind & src);
  static void apply (typename T::access_scope_type & dst, const ::iccm::PresentationQosPolicyAccessScopeKind & src);

  static void apply (typename T::entity_factory_type & dst, const ::iccm::EntityFactoryQosPolicy & src);
  static void apply (typename T::durability_type & dst, const ::iccm::DurabilityQosPolicy & src);
  static void apply (typename T::durability_service_type & dst, const ::iccm::DurabilityServiceQosPolicy & src);
  static void apply (typename T::deadline_type & dst, const ::iccm::DeadlineQosPolicy & src);
  static void apply (typename T::latency_budget_type & dst, const ::iccm::LatencyBudgetQosPolicy & src);
  static void apply (typename T::liveliness_type & dst, const ::iccm::LivelinessQosPolicy & src);
  static void apply (typename T::reliability_type & dst, const ::iccm::ReliabilityQosPolicy & src);
  static void apply (typename T::destination_order_type & dst, const ::iccm::DestinationOrderQosPolicy & src);
  static void apply (typename T::history_type & dst, const ::iccm::HistoryQosPolicy & src);
  static void apply (typename T::resource_limits_type & dst, const ::iccm::ResourceLimitsQosPolicy & src);
  static void apply (typename T::transport_priority_type & dst, const ::iccm::TransportPriorityQosPolicy & src);
  static void apply (typename T::lifespan_type & dst, const ::iccm::LifespanQosPolicy & src);
  static void apply (typename T::ownership_type & dst, const ::iccm::OwnershipQosPolicy & src);
  static void apply (typename T::presentation_type & dst, const ::iccm::PresentationQosPolicy & src);
  static void apply (typename T::partition_type & dst, const ::iccm::PartitionQosPolicy & src);
  static void apply (typename T::group_data_type & dst, const ::iccm::GroupDataQosPolicy & src);
  static void apply (typename T::user_data_type & dst, const ::iccm::UserDataQosPolicy & src);
  static void apply (typename T::time_based_filter_type & dst, const ::iccm::TimeBasedFilterQosPolicy & src);
  static void apply (typename T::reader_data_lifecycle_type & dst, const ::iccm::ReaderDataLifecycleQosPolicy & src);
  static void apply (typename T::ownership_strength_type & dst, const ::iccm::OwnershipStrengthQosPolicy & src);
  static void apply (typename T::writer_data_lifecycle_type & dst, const ::iccm::WriterDataLifecycleQosPolicy & src);
  static void apply (typename T::topicqos_type & dst, const ::iccm::TopicQos & src);
  static void apply (typename T::publisherqos_type & dst, const ::iccm::PublisherQos & src);
  static void apply (typename T::subscriberqos_type & dst, const ::iccm::SubscriberQos & src);
  static void apply (typename T::datareaderqos_type & dst, const ::iccm::DataReaderQos & src);
  static void apply (typename T::datawriterqos_type & dst, const ::iccm::DataWriterQos & src);
  // @}


protected:
  /// Default constructor.
  DDS_Servant (const char * name);

  /// Do the default configuration.
  void do_default_configure (void);

  /// Create a data writer object.
  virtual datawriter_ptr_type
    create_datawriter (const char * name,
                       const datawriterqos_type & datawriter_qos,
                       const char * topic_name,
                       const topicqos_type & topic_qos,
                       publisher_ptr_type publisher,
                       bool isprivate,
                       bool isinstance) = 0;

  /// Configure the event consumer for future data readers.
  virtual void
    configure_eventconsumer (const char * name,
                             const datareaderqos_type * qos,
                             const topicqos_type * topic_qos,
                             subscriber_ptr_type publisher,
                             bool is_global) = 0;

  /// The domain participant for the servant.
  domainparticipant_var_type participant_;

  /// Collection of non-default publishers for this servant.
  ACE_Hash_Map_Manager <ACE_CString,
                        publisher_var_type,
                        ACE_Null_Mutex> publishers_;

  /// Collection of non-default subscribers.
  ACE_Hash_Map_Manager <ACE_CString,
                        subscriber_var_type,
                        ACE_Null_Mutex> subscribers_;

  /// Collection of topic QoS entities.
  ACE_Hash_Map_Manager <ACE_CString,
                        topicqos_type *,
                        ACE_Null_Mutex> topic_qos_;

  /// Collection of datareader QoS entities
  ACE_Hash_Map_Manager <ACE_CString,
                        datareaderqos_type *,
                        ACE_Null_Mutex> datareader_qos_;

  /// Collection of datawriter QoS entities
  ACE_Hash_Map_Manager <ACE_CString,
                        datawriterqos_type *,
                        ACE_Null_Mutex> datawriter_qos_;
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Servant.inl"
#endif

#include "DDS_Servant.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_H_
