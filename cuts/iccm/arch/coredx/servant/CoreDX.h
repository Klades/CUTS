// -*- C++ -*-

//=============================================================================
/**
 *  @file         CoreDX.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_COREDX_H_
#define _ICCM_COREDX_H_

#include "cuts/iccm/arch/dds/servant/DDS_EventConsumer.h"
#include "cuts/iccm/arch/dds/servant/DDS_Publisher_Table.h"
#include "cuts/iccm/arch/dds/servant/DDS_Publisher.h"
#include "cuts/iccm/arch/dds/servant/DDS_Servant.h"
#include "cuts/iccm/arch/dds/servant/DDS_Traits_T.h"

#include "CoreDX_EventsS.h"

#include "CoreDX_svnt_export.h"

#include "dds/dds.hh"

// CoreDX uses pointers for data readers/writers
#define ICCM_DDS_USES_POINTERS

// CoreDX sequence types use size
#define ICCM_DDS_SEQ_USES_SIZE

// Workaround for DataReader QoS issues
//#define ICCM_DDS_LACKS_READER_QOS

// Workaround for Topic QoS issues on windows
#ifdef WIN32
  #define ICCM_DDS_LACKS_TOPIC_QOS
#endif

namespace iCCM
{
// Forward decl.
class CoreDX;

// Forward decl.
template <typename EVENT>
class CoreDX_Publisher_T;

template <typename EVENT>
class CoreDX_Publisher_Table_T;

template <typename SERVANT, typename EVENT>
class CoreDX_EventConsumer_T;

class CoreDX_Servant;

// Type definition.
typedef DDS_Publisher_Table <CoreDX> CoreDX_Publisher_Table;
typedef DDS_Publisher <CoreDX> CoreDX_Publisher;
typedef DDS_EventConsumer <CoreDX> CoreDX_EventConsumer;

/**
 * @class CoreDX
 */
class ICCM_COREDX_SVNT_Export CoreDX
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
    typedef CoreDX_Publisher_T <EVENT> result_type;
  };

  template <typename EVENT>
  struct typed_publisher_table_type
  {
    typedef CoreDX_Publisher_Table_T <EVENT> result_type;
  };

  template <typename SERVANT, typename EVENT>
  struct typed_eventconsumer_type
  {
    typedef CoreDX_EventConsumer_T <SERVANT, EVENT> result_type;
  };

  template <typename T>
  struct nil
  {
    static const T * result_type;
  };

  typedef CoreDX_EventConsumer eventconsumer_type;
  typedef CoreDX_Publisher publisher_type;
  typedef CoreDX_Publisher_Table publisher_table_type;
  typedef CoreDX_Servant servant_type;

  typedef ::Components::CoreDX::EventConsumer corba_eventconsumer_type;
  typedef ::Components::CoreDX::EventConsumer_var corba_eventconsumer_var_type;
  typedef ::POA_Components::CoreDX::EventConsumer corba_poa_eventconsumer_type;

  typedef ::DDS::DomainParticipantFactory * domainparticipantfactory_var_type;
  typedef ::DDS::DomainParticipantFactory * domainparticipantfactory_ptr_type;

  typedef ::DDS::DomainParticipant * domainparticipant_var_type;
  typedef ::DDS::DomainParticipant * domainparticipant_ptr_type;

  typedef ::DDS::TopicQos topicqos_type;
  typedef ::DDS::DomainParticipantQos domainparticipantqos_type;
  typedef ::DDS::DataReaderQos datareaderqos_type;
  typedef ::DDS::DataWriterQos datawriterqos_type;
  typedef ::DDS::PublisherQos publisherqos_type;
  typedef ::DDS::SubscriberQos subscriberqos_type;

  typedef ::DDS::Topic * topic_ptr_type;
  typedef ::DDS::Topic * topic_var_type;

  typedef ::DDS::Publisher * publisher_ptr_type;
  typedef ::DDS::Publisher * publisher_var_type;

  typedef ::DDS::Subscriber * subscriber_ptr_type;
  typedef ::DDS::Subscriber * subscriber_var_type;

  typedef ::DDS::DataWriter * datawriter_ptr_type;
  typedef ::DDS::DataWriter * datawriter_var_type;

  typedef ::DDS::DataReader * datareader_ptr_type;
  typedef ::DDS::DataReader * datareader_var_type;

  typedef ::DDS::DataReaderListener datareaderlistener_type;
  typedef ::DDS::SampleInfoSeq sampleinfoseq_type;

  typedef ::DDS::ReturnCode_t returncode_type;
  typedef ::DDS::InstanceHandle_t instancehandle_type;

  typedef ::DDS::RequestedDeadlineMissedStatus requesteddeadlinemissedstatus_type;
  typedef ::DDS::RequestedIncompatibleQosStatus requestedincompatibleqosstatus_type;
  typedef ::DDS::SampleRejectedStatus samplerejectedstatus_type;
  typedef ::DDS::LivelinessChangedStatus livelinesschangedstatus_type;
  typedef ::DDS::SubscriptionMatchedStatus subscriptionmatchedstatus_type;
  typedef ::DDS::SampleLostStatus sampleloststatus_type;

  // Qos typedefs
  typedef ::DDS::Duration_t duration_type;

  enum HistoryQosPolicyKind
  {
    KEEP_ALL_HISTORY_QOS = ::DDS::KEEP_ALL_HISTORY_QOS,
    KEEP_LAST_HISTORY_QOS = ::DDS::KEEP_LAST_HISTORY_QOS
  };
  typedef ::DDS::HistoryQosPolicyKind history_kind_type;

  enum LivelinessQosPolicyKind
  {
    AUTOMATIC_LIVELINESS_QOS = ::DDS::AUTOMATIC_LIVELINESS_QOS,
    MANUAL_BY_PARTICIPANT_LIVELINESS_QOS = ::DDS::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
    MANUAL_BY_TOPIC_LIVELINESS_QOS = ::DDS::MANUAL_BY_TOPIC_LIVELINESS_QOS
  };
  typedef ::DDS::LivelinessQosPolicyKind liveliness_kind_type;

  enum DurabilityQosPolicyKind
  {
    PERSISTENT_DURABILITY_QOS = ::DDS::PERSISTENT_DURABILITY_QOS,
    TRANSIENT_DURABILITY_QOS = ::DDS::TRANSIENT_DURABILITY_QOS,
    TRANSIENT_LOCAL_DURABILITY_QOS = ::DDS::TRANSIENT_LOCAL_DURABILITY_QOS,
    VOLATILE_DURABILITY_QOS = ::DDS::VOLATILE_DURABILITY_QOS
  };
  typedef ::DDS::DurabilityQosPolicyKind durability_kind_type;

  enum ReliabilityQosPolicyKind
  {
    BEST_EFFORT_RELIABILITY_QOS = ::DDS::BEST_EFFORT_RELIABILITY_QOS,
    RELIABLE_RELIABILITY_QOS = ::DDS::RELIABLE_RELIABILITY_QOS
  };
  typedef ::DDS::ReliabilityQosPolicyKind reliability_kind_type;

  enum DestinationOrderQosPolicyKind
  {
    BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS = ::DDS::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
    BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS = ::DDS::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
  };
  typedef ::DDS::DestinationOrderQosPolicyKind destination_order_kind_type;

  enum OwnershipQosPolicyKind
  {
    EXCLUSIVE_OWNERSHIP_QOS = ::DDS::EXCLUSIVE_OWNERSHIP_QOS,
    SHARED_OWNERSHIP_QOS = ::DDS::SHARED_OWNERSHIP_QOS
  };
  typedef ::DDS::OwnershipQosPolicyKind ownership_kind_type;

  enum PresentationQosPolicyAccessScopeKind
  {
    GROUP_PRESENTATION_QOS = ::DDS::GROUP_PRESENTATION_QOS,
    INSTANCE_PRESENTATION_QOS = ::DDS::INSTANCE_PRESENTATION_QOS,
    TOPIC_PRESENTATION_QOS = ::DDS::TOPIC_PRESENTATION_QOS
  };
  typedef ::DDS::PresentationQosPolicyAccessScopeKind access_scope_type;

  typedef ::DDS::DurabilityQosPolicy durability_type;
  typedef ::DDS::DurabilityServiceQosPolicy durability_service_type;
  typedef ::DDS::DeadlineQosPolicy deadline_type;
  typedef ::DDS::LatencyBudgetQosPolicy latency_budget_type;
  typedef ::DDS::LivelinessQosPolicy liveliness_type;
  typedef ::DDS::ReliabilityQosPolicy reliability_type;
  typedef ::DDS::DestinationOrderQosPolicy destination_order_type;
  typedef ::DDS::HistoryQosPolicy history_type;
  typedef ::DDS::ResourceLimitsQosPolicy resource_limits_type;
  typedef ::DDS::TransportPriorityQosPolicy transport_priority_type;
  typedef ::DDS::LifespanQosPolicy lifespan_type;
  typedef ::DDS::OwnershipQosPolicy ownership_type;
  typedef ::DDS::PresentationQosPolicy presentation_type;
  typedef ::DDS::StringSeq stringseq_type;
  static void copy_string (stringseq_type & dst, const ::iccm::StringSeq & src);
  typedef ::DDS::PartitionQosPolicy partition_type;
  typedef ::DDS::GroupDataQosPolicy group_data_type;
  typedef ::DDS::UserDataQosPolicy user_data_type;
  typedef ::DDS::TimeBasedFilterQosPolicy time_based_filter_type;
  typedef ::DDS::ReaderDataLifecycleQosPolicy reader_data_lifecycle_type;
  typedef ::DDS::OwnershipStrengthQosPolicy ownership_strength_type;
  typedef ::DDS::WriterDataLifecycleQosPolicy writer_data_lifecycle_type;
  typedef ::DDS::EntityFactoryQosPolicy entity_factory_type;

  typedef ::DDS::StatusKind statusmask_type;
  static const statusmask_type STATUS_MASK_NONE;
  static const statusmask_type STATUS_MASK_DATA_AVAILABLE;

  static const unsigned long ANY_SAMPLE_STATE = ::DDS::ANY_SAMPLE_STATE;
  static const unsigned long ANY_VIEW_STATE = ::DDS::ANY_VIEW_STATE;
  static const unsigned long ANY_INSTANCE_STATE = ::DDS::ANY_INSTANCE_STATE;

  static const instancehandle_type HANDLE_NIL;

  static const returncode_type RETCODE_OK = ::DDS::RETCODE_OK;
  static const returncode_type RETCODE_NO_DATA = ::DDS::RETCODE_NO_DATA;

  static const long LENGTH_UNLIMITED = ::DDS::LENGTH_UNLIMITED;

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
    return T1::narrow (val);
  }

  template <typename T1, typename T2>
  static T1 * _reader_cast (T2 val)
  {
    return T1::narrow (val);
  }

  template <typename T>
  static T _retn (T val)
  {
    return val;
  }
};

template <typename T>
const T * CoreDX::nil <T>::result_type = 0;

};

#if defined (__CUTS_INLINE__)
#include "CoreDX.inl"
#endif

#endif  // !define _ICCM_COREDX_H_
