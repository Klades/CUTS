// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_RTIDDS_H_
#define _ICCM_RTIDDS_H_

// Non-standard DDS features supported by RTIDDS
#define ICCM_DDS_SUPPORTS_INITIAL_RESOURCE_LIMITS
#define ICCM_DDS_SUPPORTS_WRITER_PROTOCOL_QOS

#include "cuts/iccm/arch/dds/servant/DDS_EventConsumer.h"
#include "cuts/iccm/arch/dds/servant/DDS_Publisher_Table.h"
#include "cuts/iccm/arch/dds/servant/DDS_Publisher.h"
#include "cuts/iccm/arch/dds/servant/DDS_Servant.h"
#include "cuts/iccm/arch/dds/servant/DDS_Traits_T.h"

#include "RTIDDS_EventsS.h"
#include "RTIDDS_svnt_export.h"

#include "ndds/ndds_cpp.h"

namespace iCCM
{
// Forward decl.
class RTIDDS;

// Forward decl.
template <typename EVENT>
class RTIDDS_Publisher_T;

template <typename EVENT>
class RTIDDS_Publisher_Table_T;

template <typename SERVANT, typename EVENT>
class RTIDDS_EventConsumer_T;

class RTIDDS_Servant;

// Type definition.
typedef DDS_Publisher_Table <RTIDDS> RTIDDS_Publisher_Table;
typedef DDS_Publisher <RTIDDS> RTIDDS_Publisher;
typedef DDS_EventConsumer <RTIDDS> RTIDDS_EventConsumer;

/**
 * @class RTIDDS
 */
class ICCM_RTIDDS_SVNT_Export RTIDDS
{
public:
  template <typename EVENT>
  struct event_traits_type
  {
    typedef DDS_Traits_T <EVENT> result_type;
  };

  template <typename EVENT>
  struct typed_publisher_type
  {
    typedef RTIDDS_Publisher_T <EVENT> result_type;
  };

  template <typename EVENT>
  struct typed_publisher_table_type
  {
    typedef RTIDDS_Publisher_Table_T <EVENT> result_type;
  };

  template <typename SERVANT, typename EVENT>
  struct typed_eventconsumer_type
  {
    typedef RTIDDS_EventConsumer_T <SERVANT, EVENT> result_type;
  };

  template <typename T>
  struct nil
  {
    static const T * result_type;
  };

  typedef RTIDDS_EventConsumer eventconsumer_type;
  typedef RTIDDS_Publisher publisher_type;
  typedef RTIDDS_Publisher_Table publisher_table_type;
  typedef RTIDDS_Servant servant_type;

  typedef ::Components::RTIDDS::EventConsumer corba_eventconsumer_type;
  typedef ::Components::RTIDDS::EventConsumer_var corba_eventconsumer_var_type;
  typedef ::POA_Components::RTIDDS::EventConsumer corba_poa_eventconsumer_type;

  typedef ::DDSDomainParticipantFactory * domainparticipantfactory_var_type;
  typedef ::DDSDomainParticipantFactory * domainparticipantfactory_ptr_type;

  typedef ::DDSDomainParticipant * domainparticipant_var_type;
  typedef ::DDSDomainParticipant * domainparticipant_ptr_type;

  typedef ::DDS_TopicQos topicqos_type;
  typedef ::DDS_DomainParticipantQos domainparticipantqos_type;
  typedef ::DDS_DataReaderQos datareaderqos_type;
  typedef ::DDS_DataWriterQos datawriterqos_type;
  typedef ::DDS_PublisherQos publisherqos_type;
  typedef ::DDS_SubscriberQos subscriberqos_type;

  typedef ::DDSTopic * topic_ptr_type;
  typedef ::DDSTopic * topic_var_type;

  typedef ::DDSPublisher * publisher_ptr_type;
  typedef ::DDSPublisher * publisher_var_type;

  typedef ::DDSSubscriber * subscriber_ptr_type;
  typedef ::DDSSubscriber * subscriber_var_type;

  typedef ::DDSDataWriter * datawriter_ptr_type;
  typedef ::DDSDataWriter * datawriter_var_type;

  typedef ::DDSDataReader * datareader_ptr_type;
  typedef ::DDSDataReader * datareader_var_type;

  typedef ::DDSDataReaderListener datareaderlistener_type;
  typedef ::DDS_SampleInfoSeq sampleinfoseq_type;

  typedef ::DDS_ReturnCode_t returncode_type;
  typedef ::DDS_InstanceHandle_t instancehandle_type;

  typedef ::DDS_RequestedDeadlineMissedStatus requesteddeadlinemissedstatus_type;
  typedef ::DDS_RequestedIncompatibleQosStatus requestedincompatibleqosstatus_type;
  typedef ::DDS_SampleRejectedStatus samplerejectedstatus_type;
  typedef ::DDS_LivelinessChangedStatus livelinesschangedstatus_type;
  typedef ::DDS_SubscriptionMatchedStatus subscriptionmatchedstatus_type;
  typedef ::DDS_SampleLostStatus sampleloststatus_type;

  // Qos typedefs
  typedef ::DDS_DataWriterProtocolQosPolicy writer_protocol_type;
  typedef ::DDS_RtpsReliableWriterProtocol_t rtps_reliable_writer_protocol_type;

  typedef ::DDS_Duration_t duration_type;

  enum HistoryQosPolicyKind
  {
    KEEP_ALL_HISTORY_QOS = ::DDS_KEEP_ALL_HISTORY_QOS,
    KEEP_LAST_HISTORY_QOS = ::DDS_KEEP_LAST_HISTORY_QOS
  };
  typedef ::DDS_HistoryQosPolicyKind history_kind_type;

  enum LivelinessQosPolicyKind
  {
    AUTOMATIC_LIVELINESS_QOS = ::DDS_AUTOMATIC_LIVELINESS_QOS,
    MANUAL_BY_PARTICIPANT_LIVELINESS_QOS = ::DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
    MANUAL_BY_TOPIC_LIVELINESS_QOS = ::DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS
  };
  typedef ::DDS_LivelinessQosPolicyKind liveliness_kind_type;

  enum DurabilityQosPolicyKind
  {
    PERSISTENT_DURABILITY_QOS = ::DDS_PERSISTENT_DURABILITY_QOS,
    TRANSIENT_DURABILITY_QOS = ::DDS_TRANSIENT_DURABILITY_QOS,
    TRANSIENT_LOCAL_DURABILITY_QOS = ::DDS_TRANSIENT_LOCAL_DURABILITY_QOS,
    VOLATILE_DURABILITY_QOS = ::DDS_VOLATILE_DURABILITY_QOS
  };
  typedef ::DDS_DurabilityQosPolicyKind durability_kind_type;

  enum ReliabilityQosPolicyKind
  {
    BEST_EFFORT_RELIABILITY_QOS = ::DDS_BEST_EFFORT_RELIABILITY_QOS,
    RELIABLE_RELIABILITY_QOS = ::DDS_RELIABLE_RELIABILITY_QOS
  };
  typedef ::DDS_ReliabilityQosPolicyKind reliability_kind_type;

  enum DestinationOrderQosPolicyKind
  {
    BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS = ::DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
    BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS = ::DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
  };
  typedef ::DDS_DestinationOrderQosPolicyKind destination_order_kind_type;

  enum OwnershipQosPolicyKind
  {
    EXCLUSIVE_OWNERSHIP_QOS = ::DDS_EXCLUSIVE_OWNERSHIP_QOS,
    SHARED_OWNERSHIP_QOS = ::DDS_SHARED_OWNERSHIP_QOS
  };
  typedef ::DDS_OwnershipQosPolicyKind ownership_kind_type;

  enum PresentationQosPolicyAccessScopeKind
  {
    GROUP_PRESENTATION_QOS = ::DDS_GROUP_PRESENTATION_QOS,
    INSTANCE_PRESENTATION_QOS = ::DDS_INSTANCE_PRESENTATION_QOS,
    TOPIC_PRESENTATION_QOS = ::DDS_TOPIC_PRESENTATION_QOS
  };
  typedef ::DDS_PresentationQosPolicyAccessScopeKind access_scope_type;

  typedef ::DDS_DurabilityQosPolicy durability_type;
  typedef ::DDS_DurabilityServiceQosPolicy durability_service_type;
  typedef ::DDS_DeadlineQosPolicy deadline_type;
  typedef ::DDS_LatencyBudgetQosPolicy latency_budget_type;
  typedef ::DDS_LivelinessQosPolicy liveliness_type;
  typedef ::DDS_ReliabilityQosPolicy reliability_type;
  typedef ::DDS_DestinationOrderQosPolicy destination_order_type;
  typedef ::DDS_HistoryQosPolicy history_type;
  typedef ::DDS_ResourceLimitsQosPolicy resource_limits_type;
  typedef ::DDS_TransportPriorityQosPolicy transport_priority_type;
  typedef ::DDS_LifespanQosPolicy lifespan_type;
  typedef ::DDS_OwnershipQosPolicy ownership_type;
  typedef ::DDS_PresentationQosPolicy presentation_type;
  typedef ::DDS_StringSeq stringseq_type;
  static void copy_string (stringseq_type & dst, const ::iccm::StringSeq & src);
  typedef ::DDS_PartitionQosPolicy partition_type;
  typedef ::DDS_GroupDataQosPolicy group_data_type;
  typedef ::DDS_UserDataQosPolicy user_data_type;
  typedef ::DDS_TimeBasedFilterQosPolicy time_based_filter_type;
  typedef ::DDS_ReaderDataLifecycleQosPolicy reader_data_lifecycle_type;
  typedef ::DDS_OwnershipStrengthQosPolicy ownership_strength_type;
  typedef ::DDS_WriterDataLifecycleQosPolicy writer_data_lifecycle_type;
  typedef ::DDS_EntityFactoryQosPolicy entity_factory_type;

  typedef ::DDS_StatusMask statusmask_type;
  static const statusmask_type STATUS_MASK_NONE = DDS_STATUS_MASK_NONE;
  static const statusmask_type STATUS_MASK_DATA_AVAILABLE = DDS_DATA_AVAILABLE_STATUS;

  static const unsigned long ANY_SAMPLE_STATE;
  static const unsigned long ANY_VIEW_STATE;
  static const unsigned long ANY_INSTANCE_STATE;

  static const instancehandle_type HANDLE_NIL;

  static const returncode_type RETCODE_OK = ::DDS_RETCODE_OK;
  static const returncode_type RETCODE_NO_DATA = ::DDS_RETCODE_NO_DATA;

  static const long LENGTH_UNLIMITED;

  static domainparticipantfactory_ptr_type get_domainparticipantfactory_instance (void);

  static const topicqos_type * topic_qos_default (void);
  static const domainparticipantqos_type & domainparticipant_qos_default (void);
  static const subscriberqos_type & subscriber_qos_default (void);
  static const publisherqos_type & publisher_qos_default (void);
  static const datawriterqos_type & datawriter_qos_default (void);
  static const datareaderqos_type * datareader_qos_default (void);

  template <typename TYPE_SUPPORT>
  static returncode_type register_type (domainparticipant_ptr_type p, ACE_CString & type_name)
  {
    type_name = TYPE_SUPPORT::get_type_name ();
    return TYPE_SUPPORT::register_type (p, type_name.c_str ());
  }

  template <typename T>
  static bool _is_nil (T val)
  {
    return val == 0;
  }

  template <typename T>
  static void _add_ref (T val)
  {

  }

  template <typename T>
  static T _duplicate (T val)
  {
    return val;
  }

  template <typename T1, typename T2>
  static T1 * _writer_cast (T2 val)
  {
    return dynamic_cast <T1 *> (val);
  }

  template <typename T1, typename T2>
  static T1 * _reader_cast (T2 val)
  {
    return dynamic_cast <T1 *> (val);
  }

  template <typename T>
  static T _retn (T val)
  {
    return val;
  }
};

template <typename T>
const T * RTIDDS::nil <T>::result_type = 0;

};

#if defined (__CUTS_INLINE__)
#include "RTIDDS.inl"
#endif

#endif  // !define _ICCM_RTIDDS_H_
