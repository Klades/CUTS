#ifndef DDS_H
#define DDS_H

#include "DDS_Xml_export.h"
// Forward declarations.
//
namespace iccm
{
  class HistoryQosPolicyKind;
  class DurabilityQosPolicyKind;
  class DestinationOrderQosPolicyKind;
  class PresentationQosPolicyAccessScopeKind;
  class LivelinessQosPolicyKind;
  class OwnershipQosPolicyKind;
  class ReliabilityQosPolicyKind;
  class SchedulingPriorityQosPolicyKind;
  class SchedulingClassQosPolicyKind;
  class TopicDataQosPolicy;
  class GroupDataQosPolicy;
  class UserDataQosPolicy;
  class Duration_t;
  class TransportPriorityQosPolicy;
  class PartitionQosPolicy;
  class LifespanQosPolicy;
  class DurabilityServiceQosPolicy;
  class DurabilityQosPolicy;
  class PresentationQosPolicy;
  class DeadlineQosPolicy;
  class LatencyBudgetQosPolicy;
  class OwnershipQosPolicy;
  class OwnershipStrengthQosPolicy;
  class LivelinessQosPolicy;
  class TimeBasedFilterQosPolicy;
  class ReliabilityQosPolicy;
  class DestinationOrderQosPolicy;
  class HistoryQosPolicy;
  class ResourceLimitsQosPolicy;
  class EntityFactoryQosPolicy;
  class WriterDataLifecycleQosPolicy;
  class ReaderDataLifecycleQosPolicy;
  class SchedulingClassQosPolicy;
  class SchedulingPriorityQosPolicy;
  class SchedulingQosPolicy;
  class TopicQos;
  class DomainParticipantFactoryQos;
  class DataReaderQos;
  class DataWriterQos;
  class PublisherQos;
  class SubscriberQos;
  class DomainParticipantQos;
}

#include <memory>
#include <string>
#include <list>
#include "XMLSchema/Types.hpp"
#include "XMLSchema/id_map.hpp"
#include "ace/Refcounted_Auto_Ptr.h"
#include "ace/Null_Mutex.h"
#include "ace/TSS_T.h"
#include "ace/ace_wchar.h"
#include "ace/Singleton.h"

namespace iccm
{
  class ICCM_DDS_XML_Export HistoryQosPolicyKind : public ::XSCRT::Type
  {
    public:
    HistoryQosPolicyKind (::XSCRT::XML::Element< char > const&);
    HistoryQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static HistoryQosPolicyKind const KEEP_LAST_HISTORY_QOS;
    static HistoryQosPolicyKind const KEEP_ALL_HISTORY_QOS;

    enum Value
    {
      KEEP_LAST_HISTORY_QOS_l, KEEP_ALL_HISTORY_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (HistoryQosPolicyKind const& a, HistoryQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (HistoryQosPolicyKind const& a, HistoryQosPolicyKind const& b);

    private:
    HistoryQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (HistoryQosPolicyKind const &a, HistoryQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (HistoryQosPolicyKind const &a, HistoryQosPolicyKind const &b);


  class ICCM_DDS_XML_Export DurabilityQosPolicyKind : public ::XSCRT::Type
  {
    public:
    DurabilityQosPolicyKind (::XSCRT::XML::Element< char > const&);
    DurabilityQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static DurabilityQosPolicyKind const VOLATILE_DURABILITY_QOS;
    static DurabilityQosPolicyKind const TRANSIENT_LOCAL_DURABILITY_QOS;
    static DurabilityQosPolicyKind const TRANSIENT_DURABILITY_QOS;
    static DurabilityQosPolicyKind const PERSISTENT_DURABILITY_QOS;

    enum Value
    {
      VOLATILE_DURABILITY_QOS_l, TRANSIENT_LOCAL_DURABILITY_QOS_l, TRANSIENT_DURABILITY_QOS_l, PERSISTENT_DURABILITY_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (DurabilityQosPolicyKind const& a, DurabilityQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (DurabilityQosPolicyKind const& a, DurabilityQosPolicyKind const& b);

    private:
    DurabilityQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (DurabilityQosPolicyKind const &a, DurabilityQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (DurabilityQosPolicyKind const &a, DurabilityQosPolicyKind const &b);


  class ICCM_DDS_XML_Export DestinationOrderQosPolicyKind : public ::XSCRT::Type
  {
    public:
    DestinationOrderQosPolicyKind (::XSCRT::XML::Element< char > const&);
    DestinationOrderQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static DestinationOrderQosPolicyKind const BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
    static DestinationOrderQosPolicyKind const BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;

    enum Value
    {
      BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (DestinationOrderQosPolicyKind const& a, DestinationOrderQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (DestinationOrderQosPolicyKind const& a, DestinationOrderQosPolicyKind const& b);

    private:
    DestinationOrderQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (DestinationOrderQosPolicyKind const &a, DestinationOrderQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (DestinationOrderQosPolicyKind const &a, DestinationOrderQosPolicyKind const &b);


  class ICCM_DDS_XML_Export PresentationQosPolicyAccessScopeKind : public ::XSCRT::Type
  {
    public:
    PresentationQosPolicyAccessScopeKind (::XSCRT::XML::Element< char > const&);
    PresentationQosPolicyAccessScopeKind (::XSCRT::XML::Attribute< char > const&);

    static PresentationQosPolicyAccessScopeKind const INSTANCE_PRESENTATION_QOS;
    static PresentationQosPolicyAccessScopeKind const TOPIC_PRESENTATION_QOS;
    static PresentationQosPolicyAccessScopeKind const GROUP_PRESENTATION_QOS;

    enum Value
    {
      INSTANCE_PRESENTATION_QOS_l, TOPIC_PRESENTATION_QOS_l, GROUP_PRESENTATION_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (PresentationQosPolicyAccessScopeKind const& a, PresentationQosPolicyAccessScopeKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (PresentationQosPolicyAccessScopeKind const& a, PresentationQosPolicyAccessScopeKind const& b);

    private:
    PresentationQosPolicyAccessScopeKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (PresentationQosPolicyAccessScopeKind const &a, PresentationQosPolicyAccessScopeKind const &b);

  bool ICCM_DDS_XML_Export operator!= (PresentationQosPolicyAccessScopeKind const &a, PresentationQosPolicyAccessScopeKind const &b);


  class ICCM_DDS_XML_Export LivelinessQosPolicyKind : public ::XSCRT::Type
  {
    public:
    LivelinessQosPolicyKind (::XSCRT::XML::Element< char > const&);
    LivelinessQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static LivelinessQosPolicyKind const AUTOMATIC_LIVELINESS_QOS;
    static LivelinessQosPolicyKind const MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
    static LivelinessQosPolicyKind const MANUAL_BY_TOPIC_LIVELINESS_QOS;

    enum Value
    {
      AUTOMATIC_LIVELINESS_QOS_l, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l, MANUAL_BY_TOPIC_LIVELINESS_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (LivelinessQosPolicyKind const& a, LivelinessQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (LivelinessQosPolicyKind const& a, LivelinessQosPolicyKind const& b);

    private:
    LivelinessQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (LivelinessQosPolicyKind const &a, LivelinessQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (LivelinessQosPolicyKind const &a, LivelinessQosPolicyKind const &b);


  class ICCM_DDS_XML_Export OwnershipQosPolicyKind : public ::XSCRT::Type
  {
    public:
    OwnershipQosPolicyKind (::XSCRT::XML::Element< char > const&);
    OwnershipQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static OwnershipQosPolicyKind const SHARED_OWNERSHIP_QOS;
    static OwnershipQosPolicyKind const EXCLUSIVE_OWNERSHIP_QOS;

    enum Value
    {
      SHARED_OWNERSHIP_QOS_l, EXCLUSIVE_OWNERSHIP_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (OwnershipQosPolicyKind const& a, OwnershipQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (OwnershipQosPolicyKind const& a, OwnershipQosPolicyKind const& b);

    private:
    OwnershipQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (OwnershipQosPolicyKind const &a, OwnershipQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (OwnershipQosPolicyKind const &a, OwnershipQosPolicyKind const &b);


  class ICCM_DDS_XML_Export ReliabilityQosPolicyKind : public ::XSCRT::Type
  {
    public:
    ReliabilityQosPolicyKind (::XSCRT::XML::Element< char > const&);
    ReliabilityQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static ReliabilityQosPolicyKind const BEST_EFFORT_RELIABILITY_QOS;
    static ReliabilityQosPolicyKind const RELIABLE_RELIABILITY_QOS;

    enum Value
    {
      BEST_EFFORT_RELIABILITY_QOS_l, RELIABLE_RELIABILITY_QOS_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (ReliabilityQosPolicyKind const& a, ReliabilityQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (ReliabilityQosPolicyKind const& a, ReliabilityQosPolicyKind const& b);

    private:
    ReliabilityQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (ReliabilityQosPolicyKind const &a, ReliabilityQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (ReliabilityQosPolicyKind const &a, ReliabilityQosPolicyKind const &b);


  class ICCM_DDS_XML_Export SchedulingPriorityQosPolicyKind : public ::XSCRT::Type
  {
    public:
    SchedulingPriorityQosPolicyKind (::XSCRT::XML::Element< char > const&);
    SchedulingPriorityQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static SchedulingPriorityQosPolicyKind const PRIORITY_RELATIVE;
    static SchedulingPriorityQosPolicyKind const PRIORITY_ABSOLUTE;

    enum Value
    {
      PRIORITY_RELATIVE_l, PRIORITY_ABSOLUTE_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (SchedulingPriorityQosPolicyKind const& a, SchedulingPriorityQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (SchedulingPriorityQosPolicyKind const& a, SchedulingPriorityQosPolicyKind const& b);

    private:
    SchedulingPriorityQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (SchedulingPriorityQosPolicyKind const &a, SchedulingPriorityQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (SchedulingPriorityQosPolicyKind const &a, SchedulingPriorityQosPolicyKind const &b);


  class ICCM_DDS_XML_Export SchedulingClassQosPolicyKind : public ::XSCRT::Type
  {
    public:
    SchedulingClassQosPolicyKind (::XSCRT::XML::Element< char > const&);
    SchedulingClassQosPolicyKind (::XSCRT::XML::Attribute< char > const&);

    static SchedulingClassQosPolicyKind const SCHEDULING_DEFUALT;
    static SchedulingClassQosPolicyKind const SCHEDULING_TIMESHARING;
    static SchedulingClassQosPolicyKind const SCHEDULING_REALTIME;

    enum Value
    {
      SCHEDULING_DEFUALT_l, SCHEDULING_TIMESHARING_l, SCHEDULING_REALTIME_l
    };


    Value
    integral () const;

    friend bool ICCM_DDS_XML_Export
    operator== (SchedulingClassQosPolicyKind const& a, SchedulingClassQosPolicyKind const& b);

    friend bool ICCM_DDS_XML_Export
    operator!= (SchedulingClassQosPolicyKind const& a, SchedulingClassQosPolicyKind const& b);

    private:
    SchedulingClassQosPolicyKind (Value v);

    Value v_;
  };

  bool ICCM_DDS_XML_Export operator== (SchedulingClassQosPolicyKind const &a, SchedulingClassQosPolicyKind const &b);

  bool ICCM_DDS_XML_Export operator!= (SchedulingClassQosPolicyKind const &a, SchedulingClassQosPolicyKind const &b);


  class ICCM_DDS_XML_Export TopicDataQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < TopicDataQosPolicy, ACE_Null_Mutex > _ptr;

    public:
    TopicDataQosPolicy ();

    TopicDataQosPolicy (::XSCRT::XML::Element< char > const&);
    TopicDataQosPolicy (::XSCRT::XML::Attribute< char > const&);
    TopicDataQosPolicy (TopicDataQosPolicy const& s);

    TopicDataQosPolicy&
    operator= (TopicDataQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export GroupDataQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < GroupDataQosPolicy, ACE_Null_Mutex > _ptr;

    public:
    GroupDataQosPolicy ();

    GroupDataQosPolicy (::XSCRT::XML::Element< char > const&);
    GroupDataQosPolicy (::XSCRT::XML::Attribute< char > const&);
    GroupDataQosPolicy (GroupDataQosPolicy const& s);

    GroupDataQosPolicy&
    operator= (GroupDataQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export UserDataQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < UserDataQosPolicy, ACE_Null_Mutex > _ptr;

    public:
    UserDataQosPolicy ();

    UserDataQosPolicy (::XSCRT::XML::Element< char > const&);
    UserDataQosPolicy (::XSCRT::XML::Attribute< char > const&);
    UserDataQosPolicy (UserDataQosPolicy const& s);

    UserDataQosPolicy&
    operator= (UserDataQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export Duration_t : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < Duration_t, ACE_Null_Mutex > _ptr;

    // sec
    //
    public:
    bool sec_p () const;
    ::XMLSchema::long_ const& sec () const;
    ::XMLSchema::long_& sec ();
    void sec (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > sec_;

    // nanosec
    //
    public:
    bool nanosec_p () const;
    ::XMLSchema::unsignedLong const& nanosec () const;
    ::XMLSchema::unsignedLong& nanosec ();
    void nanosec (::XMLSchema::unsignedLong const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::unsignedLong > nanosec_;

    public:
    Duration_t ();

    Duration_t (::XSCRT::XML::Element< char > const&);
    Duration_t (Duration_t const& s);

    Duration_t&
    operator= (Duration_t const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export TransportPriorityQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < TransportPriorityQosPolicy, ACE_Null_Mutex > _ptr;

    // value
    //
    public:
    bool value_p () const;
    ::XMLSchema::long_ const& value () const;
    void value (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > value_;

    public:
    TransportPriorityQosPolicy ();

    TransportPriorityQosPolicy (::XSCRT::XML::Element< char > const&);
    TransportPriorityQosPolicy (TransportPriorityQosPolicy const& s);

    TransportPriorityQosPolicy&
    operator= (TransportPriorityQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export PartitionQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < PartitionQosPolicy, ACE_Null_Mutex > _ptr;

    // name
    //
    public:
    bool name_p () const;
    ::XMLSchema::string< char > const& name () const;
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    PartitionQosPolicy ();

    PartitionQosPolicy (::XSCRT::XML::Element< char > const&);
    PartitionQosPolicy (PartitionQosPolicy const& s);

    PartitionQosPolicy&
    operator= (PartitionQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export LifespanQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < LifespanQosPolicy, ACE_Null_Mutex > _ptr;

    // period
    //
    public:
    bool period_p () const;
    ::iccm::Duration_t const& period () const;
    void period (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > period_;

    public:
    LifespanQosPolicy ();

    LifespanQosPolicy (::XSCRT::XML::Element< char > const&);
    LifespanQosPolicy (LifespanQosPolicy const& s);

    LifespanQosPolicy&
    operator= (LifespanQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DurabilityServiceQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DurabilityServiceQosPolicy, ACE_Null_Mutex > _ptr;

    // service_cleanup_delay
    //
    public:
    bool service_cleanup_delay_p () const;
    ::iccm::Duration_t const& service_cleanup_delay () const;
    void service_cleanup_delay (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > service_cleanup_delay_;

    // history_kind
    //
    public:
    bool history_kind_p () const;
    ::iccm::HistoryQosPolicyKind const& history_kind () const;
    void history_kind (::iccm::HistoryQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::HistoryQosPolicyKind > history_kind_;

    // history_depth
    //
    public:
    bool history_depth_p () const;
    ::XMLSchema::long_ const& history_depth () const;
    void history_depth (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > history_depth_;

    // max_samples
    //
    public:
    bool max_samples_p () const;
    ::XMLSchema::long_ const& max_samples () const;
    void max_samples (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_samples_;

    // max_instances
    //
    public:
    bool max_instances_p () const;
    ::XMLSchema::long_ const& max_instances () const;
    void max_instances (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_instances_;

    // max_samples_per_instance
    //
    public:
    bool max_samples_per_instance_p () const;
    ::XMLSchema::long_ const& max_samples_per_instance () const;
    void max_samples_per_instance (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_samples_per_instance_;

    public:
    DurabilityServiceQosPolicy ();

    DurabilityServiceQosPolicy (::XSCRT::XML::Element< char > const&);
    DurabilityServiceQosPolicy (DurabilityServiceQosPolicy const& s);

    DurabilityServiceQosPolicy&
    operator= (DurabilityServiceQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DurabilityQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DurabilityQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::DurabilityQosPolicyKind const& kind () const;
    void kind (::iccm::DurabilityQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::DurabilityQosPolicyKind > kind_;

    public:
    DurabilityQosPolicy (::iccm::DurabilityQosPolicyKind const& kind__);

    DurabilityQosPolicy (::XSCRT::XML::Element< char > const&);
    DurabilityQosPolicy (DurabilityQosPolicy const& s);

    DurabilityQosPolicy&
    operator= (DurabilityQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export PresentationQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < PresentationQosPolicy, ACE_Null_Mutex > _ptr;

    // access_scope
    //
    public:
    ::iccm::PresentationQosPolicyAccessScopeKind const& access_scope () const;
    void access_scope (::iccm::PresentationQosPolicyAccessScopeKind const& );

    protected:
    ::std::auto_ptr< ::iccm::PresentationQosPolicyAccessScopeKind > access_scope_;

    // coherent_access
    //
    public:
    ::XMLSchema::boolean const& coherent_access () const;
    void coherent_access (::XMLSchema::boolean const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::boolean > coherent_access_;

    // ordered_access
    //
    public:
    ::XMLSchema::boolean const& ordered_access () const;
    void ordered_access (::XMLSchema::boolean const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::boolean > ordered_access_;

    public:
    PresentationQosPolicy (::iccm::PresentationQosPolicyAccessScopeKind const& access_scope__,
                           ::XMLSchema::boolean const& coherent_access__,
                           ::XMLSchema::boolean const& ordered_access__);

    PresentationQosPolicy (::XSCRT::XML::Element< char > const&);
    PresentationQosPolicy (PresentationQosPolicy const& s);

    PresentationQosPolicy&
    operator= (PresentationQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DeadlineQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DeadlineQosPolicy, ACE_Null_Mutex > _ptr;

    // period
    //
    public:
    ::iccm::Duration_t const& period () const;
    void period (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > period_;

    public:
    DeadlineQosPolicy (::iccm::Duration_t const& period__);

    DeadlineQosPolicy (::XSCRT::XML::Element< char > const&);
    DeadlineQosPolicy (DeadlineQosPolicy const& s);

    DeadlineQosPolicy&
    operator= (DeadlineQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export LatencyBudgetQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < LatencyBudgetQosPolicy, ACE_Null_Mutex > _ptr;

    // duration
    //
    public:
    ::iccm::Duration_t const& duration () const;
    void duration (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > duration_;

    public:
    LatencyBudgetQosPolicy (::iccm::Duration_t const& duration__);

    LatencyBudgetQosPolicy (::XSCRT::XML::Element< char > const&);
    LatencyBudgetQosPolicy (LatencyBudgetQosPolicy const& s);

    LatencyBudgetQosPolicy&
    operator= (LatencyBudgetQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export OwnershipQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < OwnershipQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::OwnershipQosPolicyKind const& kind () const;
    void kind (::iccm::OwnershipQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::OwnershipQosPolicyKind > kind_;

    public:
    OwnershipQosPolicy (::iccm::OwnershipQosPolicyKind const& kind__);

    OwnershipQosPolicy (::XSCRT::XML::Element< char > const&);
    OwnershipQosPolicy (OwnershipQosPolicy const& s);

    OwnershipQosPolicy&
    operator= (OwnershipQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export OwnershipStrengthQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < OwnershipStrengthQosPolicy, ACE_Null_Mutex > _ptr;

    // value
    //
    public:
    ::XMLSchema::long_ const& value () const;
    void value (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > value_;

    public:
    OwnershipStrengthQosPolicy (::XMLSchema::long_ const& value__);

    OwnershipStrengthQosPolicy (::XSCRT::XML::Element< char > const&);
    OwnershipStrengthQosPolicy (OwnershipStrengthQosPolicy const& s);

    OwnershipStrengthQosPolicy&
    operator= (OwnershipStrengthQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export LivelinessQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < LivelinessQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::LivelinessQosPolicyKind const& kind () const;
    void kind (::iccm::LivelinessQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::LivelinessQosPolicyKind > kind_;

    // lease_duration
    //
    public:
    ::iccm::Duration_t const& lease_duration () const;
    void lease_duration (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > lease_duration_;

    public:
    LivelinessQosPolicy (::iccm::LivelinessQosPolicyKind const& kind__,
                         ::iccm::Duration_t const& lease_duration__);

    LivelinessQosPolicy (::XSCRT::XML::Element< char > const&);
    LivelinessQosPolicy (LivelinessQosPolicy const& s);

    LivelinessQosPolicy&
    operator= (LivelinessQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export TimeBasedFilterQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < TimeBasedFilterQosPolicy, ACE_Null_Mutex > _ptr;

    // minimum_separation
    //
    public:
    ::iccm::Duration_t const& minimum_separation () const;
    void minimum_separation (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > minimum_separation_;

    public:
    TimeBasedFilterQosPolicy (::iccm::Duration_t const& minimum_separation__);

    TimeBasedFilterQosPolicy (::XSCRT::XML::Element< char > const&);
    TimeBasedFilterQosPolicy (TimeBasedFilterQosPolicy const& s);

    TimeBasedFilterQosPolicy&
    operator= (TimeBasedFilterQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export ReliabilityQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < ReliabilityQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::ReliabilityQosPolicyKind const& kind () const;
    void kind (::iccm::ReliabilityQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::ReliabilityQosPolicyKind > kind_;

    // max_blocking_time
    //
    public:
    ::iccm::Duration_t const& max_blocking_time () const;
    void max_blocking_time (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > max_blocking_time_;

    public:
    ReliabilityQosPolicy (::iccm::ReliabilityQosPolicyKind const& kind__,
                          ::iccm::Duration_t const& max_blocking_time__);

    ReliabilityQosPolicy (::XSCRT::XML::Element< char > const&);
    ReliabilityQosPolicy (ReliabilityQosPolicy const& s);

    ReliabilityQosPolicy&
    operator= (ReliabilityQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DestinationOrderQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DestinationOrderQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::DestinationOrderQosPolicyKind const& kind () const;
    void kind (::iccm::DestinationOrderQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::DestinationOrderQosPolicyKind > kind_;

    public:
    DestinationOrderQosPolicy (::iccm::DestinationOrderQosPolicyKind const& kind__);

    DestinationOrderQosPolicy (::XSCRT::XML::Element< char > const&);
    DestinationOrderQosPolicy (DestinationOrderQosPolicy const& s);

    DestinationOrderQosPolicy&
    operator= (DestinationOrderQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export HistoryQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < HistoryQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::HistoryQosPolicyKind const& kind () const;
    void kind (::iccm::HistoryQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::HistoryQosPolicyKind > kind_;

    // depth
    //
    public:
    ::XMLSchema::long_ const& depth () const;
    void depth (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > depth_;

    public:
    HistoryQosPolicy (::iccm::HistoryQosPolicyKind const& kind__,
                      ::XMLSchema::long_ const& depth__);

    HistoryQosPolicy (::XSCRT::XML::Element< char > const&);
    HistoryQosPolicy (HistoryQosPolicy const& s);

    HistoryQosPolicy&
    operator= (HistoryQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export ResourceLimitsQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < ResourceLimitsQosPolicy, ACE_Null_Mutex > _ptr;

    // max_samples
    //
    public:
    ::XMLSchema::long_ const& max_samples () const;
    void max_samples (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_samples_;

    // max_instances
    //
    public:
    ::XMLSchema::long_ const& max_instances () const;
    void max_instances (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_instances_;

    // max_samples_per_instance
    //
    public:
    ::XMLSchema::long_ const& max_samples_per_instance () const;
    void max_samples_per_instance (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > max_samples_per_instance_;

    public:
    ResourceLimitsQosPolicy (::XMLSchema::long_ const& max_samples__,
                             ::XMLSchema::long_ const& max_instances__,
                             ::XMLSchema::long_ const& max_samples_per_instance__);

    ResourceLimitsQosPolicy (::XSCRT::XML::Element< char > const&);
    ResourceLimitsQosPolicy (ResourceLimitsQosPolicy const& s);

    ResourceLimitsQosPolicy&
    operator= (ResourceLimitsQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export EntityFactoryQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < EntityFactoryQosPolicy, ACE_Null_Mutex > _ptr;

    // autoenable_created_entities
    //
    public:
    ::XMLSchema::boolean const& autoenable_created_entities () const;
    void autoenable_created_entities (::XMLSchema::boolean const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::boolean > autoenable_created_entities_;

    public:
    EntityFactoryQosPolicy (::XMLSchema::boolean const& autoenable_created_entities__);

    EntityFactoryQosPolicy (::XSCRT::XML::Element< char > const&);
    EntityFactoryQosPolicy (EntityFactoryQosPolicy const& s);

    EntityFactoryQosPolicy&
    operator= (EntityFactoryQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export WriterDataLifecycleQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < WriterDataLifecycleQosPolicy, ACE_Null_Mutex > _ptr;

    // autoenable_created_entities
    //
    public:
    ::XMLSchema::boolean const& autoenable_created_entities () const;
    void autoenable_created_entities (::XMLSchema::boolean const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::boolean > autoenable_created_entities_;

    public:
    WriterDataLifecycleQosPolicy (::XMLSchema::boolean const& autoenable_created_entities__);

    WriterDataLifecycleQosPolicy (::XSCRT::XML::Element< char > const&);
    WriterDataLifecycleQosPolicy (WriterDataLifecycleQosPolicy const& s);

    WriterDataLifecycleQosPolicy&
    operator= (WriterDataLifecycleQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export ReaderDataLifecycleQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < ReaderDataLifecycleQosPolicy, ACE_Null_Mutex > _ptr;

    // autopurge_nowriter_samples_delay
    //
    public:
    ::iccm::Duration_t const& autopurge_nowriter_samples_delay () const;
    void autopurge_nowriter_samples_delay (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > autopurge_nowriter_samples_delay_;

    // autopurge_disposed_samples_delay
    //
    public:
    ::iccm::Duration_t const& autopurge_disposed_samples_delay () const;
    void autopurge_disposed_samples_delay (::iccm::Duration_t const& );

    protected:
    ::std::auto_ptr< ::iccm::Duration_t > autopurge_disposed_samples_delay_;

    public:
    ReaderDataLifecycleQosPolicy (::iccm::Duration_t const& autopurge_nowriter_samples_delay__,
                                  ::iccm::Duration_t const& autopurge_disposed_samples_delay__);

    ReaderDataLifecycleQosPolicy (::XSCRT::XML::Element< char > const&);
    ReaderDataLifecycleQosPolicy (ReaderDataLifecycleQosPolicy const& s);

    ReaderDataLifecycleQosPolicy&
    operator= (ReaderDataLifecycleQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export SchedulingClassQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < SchedulingClassQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::SchedulingClassQosPolicyKind const& kind () const;
    void kind (::iccm::SchedulingClassQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingClassQosPolicyKind > kind_;

    public:
    SchedulingClassQosPolicy (::iccm::SchedulingClassQosPolicyKind const& kind__);

    SchedulingClassQosPolicy (::XSCRT::XML::Element< char > const&);
    SchedulingClassQosPolicy (SchedulingClassQosPolicy const& s);

    SchedulingClassQosPolicy&
    operator= (SchedulingClassQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export SchedulingPriorityQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < SchedulingPriorityQosPolicy, ACE_Null_Mutex > _ptr;

    // kind
    //
    public:
    ::iccm::SchedulingPriorityQosPolicyKind const& kind () const;
    void kind (::iccm::SchedulingPriorityQosPolicyKind const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingPriorityQosPolicyKind > kind_;

    public:
    SchedulingPriorityQosPolicy (::iccm::SchedulingPriorityQosPolicyKind const& kind__);

    SchedulingPriorityQosPolicy (::XSCRT::XML::Element< char > const&);
    SchedulingPriorityQosPolicy (SchedulingPriorityQosPolicy const& s);

    SchedulingPriorityQosPolicy&
    operator= (SchedulingPriorityQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export SchedulingQosPolicy : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < SchedulingQosPolicy, ACE_Null_Mutex > _ptr;

    // scheduling_class
    //
    public:
    ::iccm::SchedulingClassQosPolicy const& scheduling_class () const;
    void scheduling_class (::iccm::SchedulingClassQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingClassQosPolicy > scheduling_class_;

    // scheduling_priority_kind
    //
    public:
    ::iccm::SchedulingPriorityQosPolicy const& scheduling_priority_kind () const;
    void scheduling_priority_kind (::iccm::SchedulingPriorityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingPriorityQosPolicy > scheduling_priority_kind_;

    // scheduling_priority
    //
    public:
    ::XMLSchema::long_ const& scheduling_priority () const;
    void scheduling_priority (::XMLSchema::long_ const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::long_ > scheduling_priority_;

    public:
    SchedulingQosPolicy (::iccm::SchedulingClassQosPolicy const& scheduling_class__,
                         ::iccm::SchedulingPriorityQosPolicy const& scheduling_priority_kind__,
                         ::XMLSchema::long_ const& scheduling_priority__);

    SchedulingQosPolicy (::XSCRT::XML::Element< char > const&);
    SchedulingQosPolicy (SchedulingQosPolicy const& s);

    SchedulingQosPolicy&
    operator= (SchedulingQosPolicy const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export TopicQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < TopicQos, ACE_Null_Mutex > _ptr;

    // topic_data
    //
    public:
    bool topic_data_p () const;
    ::iccm::TopicDataQosPolicy const& topic_data () const;
    void topic_data (::iccm::TopicDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::TopicDataQosPolicy > topic_data_;

    // durability
    //
    public:
    bool durability_p () const;
    ::iccm::DurabilityQosPolicy const& durability () const;
    void durability (::iccm::DurabilityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DurabilityQosPolicy > durability_;

    // durability_service
    //
    public:
    bool durability_service_p () const;
    ::iccm::DurabilityServiceQosPolicy const& durability_service () const;
    void durability_service (::iccm::DurabilityServiceQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DurabilityServiceQosPolicy > durability_service_;

    // deadline
    //
    public:
    bool deadline_p () const;
    ::iccm::DeadlineQosPolicy const& deadline () const;
    void deadline (::iccm::DeadlineQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DeadlineQosPolicy > deadline_;

    // latency_budget
    //
    public:
    bool latency_budget_p () const;
    ::iccm::LatencyBudgetQosPolicy const& latency_budget () const;
    void latency_budget (::iccm::LatencyBudgetQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LatencyBudgetQosPolicy > latency_budget_;

    // liveliness
    //
    public:
    bool liveliness_p () const;
    ::iccm::LivelinessQosPolicy const& liveliness () const;
    void liveliness (::iccm::LivelinessQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LivelinessQosPolicy > liveliness_;

    // destination_order
    //
    public:
    bool destination_order_p () const;
    ::iccm::DestinationOrderQosPolicy const& destination_order () const;
    void destination_order (::iccm::DestinationOrderQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DestinationOrderQosPolicy > destination_order_;

    // history
    //
    public:
    bool history_p () const;
    ::iccm::HistoryQosPolicy const& history () const;
    void history (::iccm::HistoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::HistoryQosPolicy > history_;

    // resource_limits
    //
    public:
    bool resource_limits_p () const;
    ::iccm::ResourceLimitsQosPolicy const& resource_limits () const;
    void resource_limits (::iccm::ResourceLimitsQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ResourceLimitsQosPolicy > resource_limits_;

    // transport_priority
    //
    public:
    bool transport_priority_p () const;
    ::iccm::TransportPriorityQosPolicy const& transport_priority () const;
    void transport_priority (::iccm::TransportPriorityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::TransportPriorityQosPolicy > transport_priority_;

    // lifespan
    //
    public:
    bool lifespan_p () const;
    ::iccm::LifespanQosPolicy const& lifespan () const;
    void lifespan (::iccm::LifespanQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LifespanQosPolicy > lifespan_;

    // ownership
    //
    public:
    bool ownership_p () const;
    ::iccm::OwnershipQosPolicy const& ownership () const;
    void ownership (::iccm::OwnershipQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::OwnershipQosPolicy > ownership_;

    public:
    TopicQos ();

    TopicQos (::XSCRT::XML::Element< char > const&);
    TopicQos (TopicQos const& s);

    TopicQos&
    operator= (TopicQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DomainParticipantFactoryQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DomainParticipantFactoryQos, ACE_Null_Mutex > _ptr;

    // entity_factory
    //
    public:
    ::iccm::EntityFactoryQosPolicy const& entity_factory () const;
    void entity_factory (::iccm::EntityFactoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::EntityFactoryQosPolicy > entity_factory_;

    public:
    DomainParticipantFactoryQos (::iccm::EntityFactoryQosPolicy const& entity_factory__);

    DomainParticipantFactoryQos (::XSCRT::XML::Element< char > const&);
    DomainParticipantFactoryQos (DomainParticipantFactoryQos const& s);

    DomainParticipantFactoryQos&
    operator= (DomainParticipantFactoryQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DataReaderQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DataReaderQos, ACE_Null_Mutex > _ptr;

    // durability
    //
    public:
    bool durability_p () const;
    ::iccm::DurabilityQosPolicy const& durability () const;
    void durability (::iccm::DurabilityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DurabilityQosPolicy > durability_;

    // deadline
    //
    public:
    bool deadline_p () const;
    ::iccm::DeadlineQosPolicy const& deadline () const;
    void deadline (::iccm::DeadlineQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DeadlineQosPolicy > deadline_;

    // latency_budget
    //
    public:
    bool latency_budget_p () const;
    ::iccm::LatencyBudgetQosPolicy const& latency_budget () const;
    void latency_budget (::iccm::LatencyBudgetQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LatencyBudgetQosPolicy > latency_budget_;

    // liveliness
    //
    public:
    bool liveliness_p () const;
    ::iccm::LivelinessQosPolicy const& liveliness () const;
    void liveliness (::iccm::LivelinessQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LivelinessQosPolicy > liveliness_;

    // reliability
    //
    public:
    bool reliability_p () const;
    ::iccm::ReliabilityQosPolicy const& reliability () const;
    void reliability (::iccm::ReliabilityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ReliabilityQosPolicy > reliability_;

    // destination_order
    //
    public:
    bool destination_order_p () const;
    ::iccm::DestinationOrderQosPolicy const& destination_order () const;
    void destination_order (::iccm::DestinationOrderQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DestinationOrderQosPolicy > destination_order_;

    // history
    //
    public:
    bool history_p () const;
    ::iccm::HistoryQosPolicy const& history () const;
    void history (::iccm::HistoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::HistoryQosPolicy > history_;

    // resource_limits
    //
    public:
    bool resource_limits_p () const;
    ::iccm::ResourceLimitsQosPolicy const& resource_limits () const;
    void resource_limits (::iccm::ResourceLimitsQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ResourceLimitsQosPolicy > resource_limits_;

    // user_data
    //
    public:
    bool user_data_p () const;
    ::iccm::UserDataQosPolicy const& user_data () const;
    void user_data (::iccm::UserDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::UserDataQosPolicy > user_data_;

    // ownership
    //
    public:
    bool ownership_p () const;
    ::iccm::OwnershipQosPolicy const& ownership () const;
    void ownership (::iccm::OwnershipQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::OwnershipQosPolicy > ownership_;

    // time_based_filter
    //
    public:
    bool time_based_filter_p () const;
    ::iccm::TimeBasedFilterQosPolicy const& time_based_filter () const;
    void time_based_filter (::iccm::TimeBasedFilterQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::TimeBasedFilterQosPolicy > time_based_filter_;

    // reader_data_lifecycle
    //
    public:
    bool reader_data_lifecycle_p () const;
    ::iccm::ReaderDataLifecycleQosPolicy const& reader_data_lifecycle () const;
    void reader_data_lifecycle (::iccm::ReaderDataLifecycleQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ReaderDataLifecycleQosPolicy > reader_data_lifecycle_;

    // name
    //
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    // subscriber
    //
    public:
    bool subscriber_p () const;
    ::XMLSchema::string< char > const& subscriber () const;
    ::XMLSchema::string< char >& subscriber ();
    void subscriber (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > subscriber_;

    public:
    DataReaderQos (::XMLSchema::string< char > const& name__);

    DataReaderQos (::XSCRT::XML::Element< char > const&);
    DataReaderQos (DataReaderQos const& s);

    DataReaderQos&
    operator= (DataReaderQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DataWriterQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DataWriterQos, ACE_Null_Mutex > _ptr;

    // durability
    //
    public:
    bool durability_p () const;
    ::iccm::DurabilityQosPolicy const& durability () const;
    void durability (::iccm::DurabilityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DurabilityQosPolicy > durability_;

    // deadline
    //
    public:
    bool deadline_p () const;
    ::iccm::DeadlineQosPolicy const& deadline () const;
    void deadline (::iccm::DeadlineQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DeadlineQosPolicy > deadline_;

    // latency_budget
    //
    public:
    bool latency_budget_p () const;
    ::iccm::LatencyBudgetQosPolicy const& latency_budget () const;
    void latency_budget (::iccm::LatencyBudgetQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LatencyBudgetQosPolicy > latency_budget_;

    // liveliness
    //
    public:
    bool liveliness_p () const;
    ::iccm::LivelinessQosPolicy const& liveliness () const;
    void liveliness (::iccm::LivelinessQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LivelinessQosPolicy > liveliness_;

    // reliability
    //
    public:
    bool reliability_p () const;
    ::iccm::ReliabilityQosPolicy const& reliability () const;
    void reliability (::iccm::ReliabilityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ReliabilityQosPolicy > reliability_;

    // destination_order
    //
    public:
    bool destination_order_p () const;
    ::iccm::DestinationOrderQosPolicy const& destination_order () const;
    void destination_order (::iccm::DestinationOrderQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::DestinationOrderQosPolicy > destination_order_;

    // history
    //
    public:
    bool history_p () const;
    ::iccm::HistoryQosPolicy const& history () const;
    void history (::iccm::HistoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::HistoryQosPolicy > history_;

    // resource_limits
    //
    public:
    bool resource_limits_p () const;
    ::iccm::ResourceLimitsQosPolicy const& resource_limits () const;
    void resource_limits (::iccm::ResourceLimitsQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::ResourceLimitsQosPolicy > resource_limits_;

    // transport_priorty
    //
    public:
    bool transport_priorty_p () const;
    ::iccm::TransportPriorityQosPolicy const& transport_priorty () const;
    void transport_priorty (::iccm::TransportPriorityQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::TransportPriorityQosPolicy > transport_priorty_;

    // lifespan
    //
    public:
    bool lifespan_p () const;
    ::iccm::LifespanQosPolicy const& lifespan () const;
    void lifespan (::iccm::LifespanQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::LifespanQosPolicy > lifespan_;

    // user_data
    //
    public:
    bool user_data_p () const;
    ::iccm::UserDataQosPolicy const& user_data () const;
    void user_data (::iccm::UserDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::UserDataQosPolicy > user_data_;

    // ownership
    //
    public:
    bool ownership_p () const;
    ::iccm::OwnershipQosPolicy const& ownership () const;
    void ownership (::iccm::OwnershipQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::OwnershipQosPolicy > ownership_;

    // ownership_strength
    //
    public:
    bool ownership_strength_p () const;
    ::iccm::OwnershipStrengthQosPolicy const& ownership_strength () const;
    void ownership_strength (::iccm::OwnershipStrengthQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::OwnershipStrengthQosPolicy > ownership_strength_;

    // writer_data_lifecycle
    //
    public:
    bool writer_data_lifecycle_p () const;
    ::iccm::WriterDataLifecycleQosPolicy const& writer_data_lifecycle () const;
    void writer_data_lifecycle (::iccm::WriterDataLifecycleQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::WriterDataLifecycleQosPolicy > writer_data_lifecycle_;

    // name
    //
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    // publisher
    //
    public:
    bool publisher_p () const;
    ::XMLSchema::string< char > const& publisher () const;
    ::XMLSchema::string< char >& publisher ();
    void publisher (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > publisher_;

    // isinstance
    //
    public:
    bool isinstance_p () const;
    ::XMLSchema::boolean const& isinstance () const;
    ::XMLSchema::boolean& isinstance ();
    void isinstance (::XMLSchema::boolean const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::boolean > isinstance_;

    public:
    DataWriterQos (::XMLSchema::string< char > const& name__);

    DataWriterQos (::XSCRT::XML::Element< char > const&);
    DataWriterQos (DataWriterQos const& s);

    DataWriterQos&
    operator= (DataWriterQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export PublisherQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < PublisherQos, ACE_Null_Mutex > _ptr;

    // presentation
    //
    public:
    bool presentation_p () const;
    ::iccm::PresentationQosPolicy const& presentation () const;
    void presentation (::iccm::PresentationQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::PresentationQosPolicy > presentation_;

    // partition
    //
    public:
    bool partition_p () const;
    ::iccm::PartitionQosPolicy const& partition () const;
    void partition (::iccm::PartitionQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::PartitionQosPolicy > partition_;

    // group_data
    //
    public:
    bool group_data_p () const;
    ::iccm::GroupDataQosPolicy const& group_data () const;
    void group_data (::iccm::GroupDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::GroupDataQosPolicy > group_data_;

    // entity_factory
    //
    public:
    bool entity_factory_p () const;
    ::iccm::EntityFactoryQosPolicy const& entity_factory () const;
    void entity_factory (::iccm::EntityFactoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::EntityFactoryQosPolicy > entity_factory_;

    // name
    //
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    PublisherQos (::XMLSchema::string< char > const& name__);

    PublisherQos (::XSCRT::XML::Element< char > const&);
    PublisherQos (PublisherQos const& s);

    PublisherQos&
    operator= (PublisherQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export SubscriberQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < SubscriberQos, ACE_Null_Mutex > _ptr;

    // presentation
    //
    public:
    bool presentation_p () const;
    ::iccm::PresentationQosPolicy const& presentation () const;
    void presentation (::iccm::PresentationQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::PresentationQosPolicy > presentation_;

    // partition
    //
    public:
    bool partition_p () const;
    ::iccm::PartitionQosPolicy const& partition () const;
    void partition (::iccm::PartitionQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::PartitionQosPolicy > partition_;

    // group_data
    //
    public:
    bool group_data_p () const;
    ::iccm::GroupDataQosPolicy const& group_data () const;
    void group_data (::iccm::GroupDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::GroupDataQosPolicy > group_data_;

    // entity_factory
    //
    public:
    bool entity_factory_p () const;
    ::iccm::EntityFactoryQosPolicy const& entity_factory () const;
    void entity_factory (::iccm::EntityFactoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::EntityFactoryQosPolicy > entity_factory_;

    // name
    //
    public:
    ::XMLSchema::string< char > const& name () const;
    ::XMLSchema::string< char >& name ();
    void name (::XMLSchema::string< char > const& );

    protected:
    ::std::auto_ptr< ::XMLSchema::string< char > > name_;

    public:
    SubscriberQos (::XMLSchema::string< char > const& name__);

    SubscriberQos (::XSCRT::XML::Element< char > const&);
    SubscriberQos (SubscriberQos const& s);

    SubscriberQos&
    operator= (SubscriberQos const& s);

    private:
    char regulator__;
  };


  class ICCM_DDS_XML_Export DomainParticipantQos : public ::XSCRT::Type
  {
    typedef ::XSCRT::Type Base;

    public:
    typedef ACE_Refcounted_Auto_Ptr < DomainParticipantQos, ACE_Null_Mutex > _ptr;

    // user_data
    //
    public:
    bool user_data_p () const;
    ::iccm::UserDataQosPolicy const& user_data () const;
    void user_data (::iccm::UserDataQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::UserDataQosPolicy > user_data_;

    // entity_factory
    //
    public:
    bool entity_factory_p () const;
    ::iccm::EntityFactoryQosPolicy const& entity_factory () const;
    void entity_factory (::iccm::EntityFactoryQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::EntityFactoryQosPolicy > entity_factory_;

    // watchdog_scheduling
    //
    public:
    bool watchdog_scheduling_p () const;
    ::iccm::SchedulingQosPolicy const& watchdog_scheduling () const;
    void watchdog_scheduling (::iccm::SchedulingQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingQosPolicy > watchdog_scheduling_;

    // listener_scheduling
    //
    public:
    bool listener_scheduling_p () const;
    ::iccm::SchedulingQosPolicy const& listener_scheduling () const;
    void listener_scheduling (::iccm::SchedulingQosPolicy const& );

    protected:
    ::std::auto_ptr< ::iccm::SchedulingQosPolicy > listener_scheduling_;

    // publisher
    //
    public:
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > >::iterator publisher_iterator;
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > >::const_iterator publisher_const_iterator;
    publisher_iterator begin_publisher ();
    publisher_iterator end_publisher ();
    publisher_const_iterator begin_publisher () const;
    publisher_const_iterator end_publisher () const;
    void add_publisher ( ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > const& );
    XSCRT::Type* get_publisher_ptr ( std::basic_string<char> idref );
    void set_publisher_ptr (std::basic_string<char> idref );
    size_t count_publisher (void) const;

    protected:
    ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex > > publisher_;

    // subscriber
    //
    public:
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > >::iterator subscriber_iterator;
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > >::const_iterator subscriber_const_iterator;
    subscriber_iterator begin_subscriber ();
    subscriber_iterator end_subscriber ();
    subscriber_const_iterator begin_subscriber () const;
    subscriber_const_iterator end_subscriber () const;
    void add_subscriber ( ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > const& );
    XSCRT::Type* get_subscriber_ptr ( std::basic_string<char> idref );
    void set_subscriber_ptr (std::basic_string<char> idref );
    size_t count_subscriber (void) const;

    protected:
    ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex > > subscriber_;

    // datawriter
    //
    public:
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > >::iterator datawriter_iterator;
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > >::const_iterator datawriter_const_iterator;
    datawriter_iterator begin_datawriter ();
    datawriter_iterator end_datawriter ();
    datawriter_const_iterator begin_datawriter () const;
    datawriter_const_iterator end_datawriter () const;
    void add_datawriter ( ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > const& );
    XSCRT::Type* get_datawriter_ptr ( std::basic_string<char> idref );
    void set_datawriter_ptr (std::basic_string<char> idref );
    size_t count_datawriter (void) const;

    protected:
    ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex > > datawriter_;

    // datareader
    //
    public:
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > >::iterator datareader_iterator;
    typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > >::const_iterator datareader_const_iterator;
    datareader_iterator begin_datareader ();
    datareader_iterator end_datareader ();
    datareader_const_iterator begin_datareader () const;
    datareader_const_iterator end_datareader () const;
    void add_datareader ( ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > const& );
    XSCRT::Type* get_datareader_ptr ( std::basic_string<char> idref );
    void set_datareader_ptr (std::basic_string<char> idref );
    size_t count_datareader (void) const;

    protected:
    ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex > > datareader_;

    public:
    DomainParticipantQos ();

    DomainParticipantQos (::XSCRT::XML::Element< char > const&);
    DomainParticipantQos (DomainParticipantQos const& s);

    DomainParticipantQos&
    operator= (DomainParticipantQos const& s);

    private:
    char regulator__;
  };
}

namespace iccm
{
  namespace reader
  {
    ICCM_DDS_XML_Export
    ::iccm::DomainParticipantFactoryQos
    domain (xercesc::DOMDocument const*);
  }


  namespace reader
  {
    ICCM_DDS_XML_Export
    ::iccm::DomainParticipantQos
    participant (xercesc::DOMDocument const*);
  }
}

#include "dds.inl"

#endif // DDS_H
