#ifndef DDS_H
#define DDS_H

// Forward declarations.
//
namespace iccm
{
  namespace dds
  {
    class Duration_t;
    class TransportPriorityQosPolicy;
    class PartitionQosPolicy;
    class LifespanQosPolicy;
    class DurabilityQosPolicyKind;
    class DurabilityQosPolicy;
    class PresentationQosPolicyAccessScopeKind;
    class PresentationQosPolicy;
    class DeadlineQosPolicy;
    class LatencyBudgetQosPolicy;
    class OwnershipQosPolicyKind;
    class OwnershipQosPolicy;
    class OwnershipStrengthQosPolicy;
    class LivelinessQosPolicyKind;
    class LivelinessQosPolicy;
    class TimeBasedFilterQosPolicy;
    class ReliabilityQosPolicyKind;
    class ReliabilityQosPolicy;
    class DestinationOrderQosPolicyKind;
    class DestinationOrderQosPolicy;
    class HistoryQosPolicyKind;
    class HistoryQosPolicy;
    class ResourceLimitsQosPolicy;
    class EntityFactoryQosPolicy;
    class WriterDataLifecycleQosPolicy;
    class ReaderDataLifecycleQosPolicy;
    class DurabilityServiceQosPolicy;
    class SchedulingClassQosPolicyKind;
    class SchedulingClassQosPolicy;
    class SchedulingPriorityQosPolicyKind;
    class SchedulingPriorityQosPolicy;
    class SchedulingQosPolicy;
    class DomainParticipantFactoryQos;
    class DataReaderQos;
    class DataWriterQos;
    class PublisherQos;
    class SubscriberQos;
    class DomainParticipantQos;
  }
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
  namespace dds
  {
    class Duration_t : public ::XSCRT::Type
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


    class TransportPriorityQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < TransportPriorityQosPolicy, ACE_Null_Mutex > _ptr;

      // value
      //
      public:
      ::XMLSchema::long_ const& value () const;
      void value (::XMLSchema::long_ const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::long_ > value_;

      public:
      TransportPriorityQosPolicy (::XMLSchema::long_ const& value__);

      TransportPriorityQosPolicy (::XSCRT::XML::Element< char > const&);
      TransportPriorityQosPolicy (TransportPriorityQosPolicy const& s);

      TransportPriorityQosPolicy&
      operator= (TransportPriorityQosPolicy const& s);

      private:
      char regulator__;
    };


    class PartitionQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < PartitionQosPolicy, ACE_Null_Mutex > _ptr;

      // name
      //
      public:
      ::XMLSchema::string< char > const& name () const;
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      public:
      PartitionQosPolicy (::XMLSchema::string< char > const& name__);

      PartitionQosPolicy (::XSCRT::XML::Element< char > const&);
      PartitionQosPolicy (PartitionQosPolicy const& s);

      PartitionQosPolicy&
      operator= (PartitionQosPolicy const& s);

      private:
      char regulator__;
    };


    class LifespanQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < LifespanQosPolicy, ACE_Null_Mutex > _ptr;

      // period
      //
      public:
      ::iccm::dds::Duration_t const& period () const;
      void period (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > period_;

      public:
      LifespanQosPolicy (::iccm::dds::Duration_t const& period__);

      LifespanQosPolicy (::XSCRT::XML::Element< char > const&);
      LifespanQosPolicy (LifespanQosPolicy const& s);

      LifespanQosPolicy&
      operator= (LifespanQosPolicy const& s);

      private:
      char regulator__;
    };


    class DurabilityQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (DurabilityQosPolicyKind const& a, DurabilityQosPolicyKind const& b);

      friend bool
      operator!= (DurabilityQosPolicyKind const& a, DurabilityQosPolicyKind const& b);

      private:
      DurabilityQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (DurabilityQosPolicyKind const &a, DurabilityQosPolicyKind const &b);

    bool operator!= (DurabilityQosPolicyKind const &a, DurabilityQosPolicyKind const &b);


    class DurabilityQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DurabilityQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::DurabilityQosPolicyKind const& kind () const;
      void kind (::iccm::dds::DurabilityQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicyKind > kind_;

      public:
      DurabilityQosPolicy (::iccm::dds::DurabilityQosPolicyKind const& kind__);

      DurabilityQosPolicy (::XSCRT::XML::Element< char > const&);
      DurabilityQosPolicy (DurabilityQosPolicy const& s);

      DurabilityQosPolicy&
      operator= (DurabilityQosPolicy const& s);

      private:
      char regulator__;
    };


    class PresentationQosPolicyAccessScopeKind : public ::XSCRT::Type
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

      friend bool
      operator== (PresentationQosPolicyAccessScopeKind const& a, PresentationQosPolicyAccessScopeKind const& b);

      friend bool
      operator!= (PresentationQosPolicyAccessScopeKind const& a, PresentationQosPolicyAccessScopeKind const& b);

      private:
      PresentationQosPolicyAccessScopeKind (Value v);

      Value v_;
    };

    bool operator== (PresentationQosPolicyAccessScopeKind const &a, PresentationQosPolicyAccessScopeKind const &b);

    bool operator!= (PresentationQosPolicyAccessScopeKind const &a, PresentationQosPolicyAccessScopeKind const &b);


    class PresentationQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < PresentationQosPolicy, ACE_Null_Mutex > _ptr;

      // access_scope
      //
      public:
      ::iccm::dds::PresentationQosPolicyAccessScopeKind const& access_scope () const;
      void access_scope (::iccm::dds::PresentationQosPolicyAccessScopeKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::PresentationQosPolicyAccessScopeKind > access_scope_;

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
      PresentationQosPolicy (::iccm::dds::PresentationQosPolicyAccessScopeKind const& access_scope__,
                             ::XMLSchema::boolean const& coherent_access__,
                             ::XMLSchema::boolean const& ordered_access__);

      PresentationQosPolicy (::XSCRT::XML::Element< char > const&);
      PresentationQosPolicy (PresentationQosPolicy const& s);

      PresentationQosPolicy&
      operator= (PresentationQosPolicy const& s);

      private:
      char regulator__;
    };


    class DeadlineQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DeadlineQosPolicy, ACE_Null_Mutex > _ptr;

      // period
      //
      public:
      ::iccm::dds::Duration_t const& period () const;
      void period (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > period_;

      public:
      DeadlineQosPolicy (::iccm::dds::Duration_t const& period__);

      DeadlineQosPolicy (::XSCRT::XML::Element< char > const&);
      DeadlineQosPolicy (DeadlineQosPolicy const& s);

      DeadlineQosPolicy&
      operator= (DeadlineQosPolicy const& s);

      private:
      char regulator__;
    };


    class LatencyBudgetQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < LatencyBudgetQosPolicy, ACE_Null_Mutex > _ptr;

      // duration
      //
      public:
      ::iccm::dds::Duration_t const& duration () const;
      void duration (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > duration_;

      public:
      LatencyBudgetQosPolicy (::iccm::dds::Duration_t const& duration__);

      LatencyBudgetQosPolicy (::XSCRT::XML::Element< char > const&);
      LatencyBudgetQosPolicy (LatencyBudgetQosPolicy const& s);

      LatencyBudgetQosPolicy&
      operator= (LatencyBudgetQosPolicy const& s);

      private:
      char regulator__;
    };


    class OwnershipQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (OwnershipQosPolicyKind const& a, OwnershipQosPolicyKind const& b);

      friend bool
      operator!= (OwnershipQosPolicyKind const& a, OwnershipQosPolicyKind const& b);

      private:
      OwnershipQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (OwnershipQosPolicyKind const &a, OwnershipQosPolicyKind const &b);

    bool operator!= (OwnershipQosPolicyKind const &a, OwnershipQosPolicyKind const &b);


    class OwnershipQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < OwnershipQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::OwnershipQosPolicyKind const& kind () const;
      void kind (::iccm::dds::OwnershipQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicyKind > kind_;

      public:
      OwnershipQosPolicy (::iccm::dds::OwnershipQosPolicyKind const& kind__);

      OwnershipQosPolicy (::XSCRT::XML::Element< char > const&);
      OwnershipQosPolicy (OwnershipQosPolicy const& s);

      OwnershipQosPolicy&
      operator= (OwnershipQosPolicy const& s);

      private:
      char regulator__;
    };


    class OwnershipStrengthQosPolicy : public ::XSCRT::Type
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


    class LivelinessQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (LivelinessQosPolicyKind const& a, LivelinessQosPolicyKind const& b);

      friend bool
      operator!= (LivelinessQosPolicyKind const& a, LivelinessQosPolicyKind const& b);

      private:
      LivelinessQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (LivelinessQosPolicyKind const &a, LivelinessQosPolicyKind const &b);

    bool operator!= (LivelinessQosPolicyKind const &a, LivelinessQosPolicyKind const &b);


    class LivelinessQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < LivelinessQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::LivelinessQosPolicyKind const& kind () const;
      void kind (::iccm::dds::LivelinessQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicyKind > kind_;

      // lease_duration
      //
      public:
      ::iccm::dds::Duration_t const& lease_duration () const;
      void lease_duration (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > lease_duration_;

      public:
      LivelinessQosPolicy (::iccm::dds::LivelinessQosPolicyKind const& kind__,
                           ::iccm::dds::Duration_t const& lease_duration__);

      LivelinessQosPolicy (::XSCRT::XML::Element< char > const&);
      LivelinessQosPolicy (LivelinessQosPolicy const& s);

      LivelinessQosPolicy&
      operator= (LivelinessQosPolicy const& s);

      private:
      char regulator__;
    };


    class TimeBasedFilterQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < TimeBasedFilterQosPolicy, ACE_Null_Mutex > _ptr;

      // minimum_separation
      //
      public:
      ::iccm::dds::Duration_t const& minimum_separation () const;
      void minimum_separation (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > minimum_separation_;

      public:
      TimeBasedFilterQosPolicy (::iccm::dds::Duration_t const& minimum_separation__);

      TimeBasedFilterQosPolicy (::XSCRT::XML::Element< char > const&);
      TimeBasedFilterQosPolicy (TimeBasedFilterQosPolicy const& s);

      TimeBasedFilterQosPolicy&
      operator= (TimeBasedFilterQosPolicy const& s);

      private:
      char regulator__;
    };


    class ReliabilityQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (ReliabilityQosPolicyKind const& a, ReliabilityQosPolicyKind const& b);

      friend bool
      operator!= (ReliabilityQosPolicyKind const& a, ReliabilityQosPolicyKind const& b);

      private:
      ReliabilityQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (ReliabilityQosPolicyKind const &a, ReliabilityQosPolicyKind const &b);

    bool operator!= (ReliabilityQosPolicyKind const &a, ReliabilityQosPolicyKind const &b);


    class ReliabilityQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < ReliabilityQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::ReliabilityQosPolicyKind const& kind () const;
      void kind (::iccm::dds::ReliabilityQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicyKind > kind_;

      // max_blocking_time
      //
      public:
      ::iccm::dds::Duration_t const& max_blocking_time () const;
      void max_blocking_time (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > max_blocking_time_;

      public:
      ReliabilityQosPolicy (::iccm::dds::ReliabilityQosPolicyKind const& kind__,
                            ::iccm::dds::Duration_t const& max_blocking_time__);

      ReliabilityQosPolicy (::XSCRT::XML::Element< char > const&);
      ReliabilityQosPolicy (ReliabilityQosPolicy const& s);

      ReliabilityQosPolicy&
      operator= (ReliabilityQosPolicy const& s);

      private:
      char regulator__;
    };


    class DestinationOrderQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (DestinationOrderQosPolicyKind const& a, DestinationOrderQosPolicyKind const& b);

      friend bool
      operator!= (DestinationOrderQosPolicyKind const& a, DestinationOrderQosPolicyKind const& b);

      private:
      DestinationOrderQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (DestinationOrderQosPolicyKind const &a, DestinationOrderQosPolicyKind const &b);

    bool operator!= (DestinationOrderQosPolicyKind const &a, DestinationOrderQosPolicyKind const &b);


    class DestinationOrderQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DestinationOrderQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::DestinationOrderQosPolicyKind const& kind () const;
      void kind (::iccm::dds::DestinationOrderQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicyKind > kind_;

      public:
      DestinationOrderQosPolicy (::iccm::dds::DestinationOrderQosPolicyKind const& kind__);

      DestinationOrderQosPolicy (::XSCRT::XML::Element< char > const&);
      DestinationOrderQosPolicy (DestinationOrderQosPolicy const& s);

      DestinationOrderQosPolicy&
      operator= (DestinationOrderQosPolicy const& s);

      private:
      char regulator__;
    };


    class HistoryQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (HistoryQosPolicyKind const& a, HistoryQosPolicyKind const& b);

      friend bool
      operator!= (HistoryQosPolicyKind const& a, HistoryQosPolicyKind const& b);

      private:
      HistoryQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (HistoryQosPolicyKind const &a, HistoryQosPolicyKind const &b);

    bool operator!= (HistoryQosPolicyKind const &a, HistoryQosPolicyKind const &b);


    class HistoryQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < HistoryQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::HistoryQosPolicyKind const& kind () const;
      void kind (::iccm::dds::HistoryQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::HistoryQosPolicyKind > kind_;

      // depth
      //
      public:
      ::XMLSchema::long_ const& depth () const;
      void depth (::XMLSchema::long_ const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::long_ > depth_;

      public:
      HistoryQosPolicy (::iccm::dds::HistoryQosPolicyKind const& kind__,
                        ::XMLSchema::long_ const& depth__);

      HistoryQosPolicy (::XSCRT::XML::Element< char > const&);
      HistoryQosPolicy (HistoryQosPolicy const& s);

      HistoryQosPolicy&
      operator= (HistoryQosPolicy const& s);

      private:
      char regulator__;
    };


    class ResourceLimitsQosPolicy : public ::XSCRT::Type
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


    class EntityFactoryQosPolicy : public ::XSCRT::Type
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


    class WriterDataLifecycleQosPolicy : public ::XSCRT::Type
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


    class ReaderDataLifecycleQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < ReaderDataLifecycleQosPolicy, ACE_Null_Mutex > _ptr;

      // autopurge_nowriter_samples_delay
      //
      public:
      ::iccm::dds::Duration_t const& autopurge_nowriter_samples_delay () const;
      void autopurge_nowriter_samples_delay (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > autopurge_nowriter_samples_delay_;

      // autopurge_disposed_samples_delay
      //
      public:
      ::iccm::dds::Duration_t const& autopurge_disposed_samples_delay () const;
      void autopurge_disposed_samples_delay (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > autopurge_disposed_samples_delay_;

      public:
      ReaderDataLifecycleQosPolicy (::iccm::dds::Duration_t const& autopurge_nowriter_samples_delay__,
                                    ::iccm::dds::Duration_t const& autopurge_disposed_samples_delay__);

      ReaderDataLifecycleQosPolicy (::XSCRT::XML::Element< char > const&);
      ReaderDataLifecycleQosPolicy (ReaderDataLifecycleQosPolicy const& s);

      ReaderDataLifecycleQosPolicy&
      operator= (ReaderDataLifecycleQosPolicy const& s);

      private:
      char regulator__;
    };


    class DurabilityServiceQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DurabilityServiceQosPolicy, ACE_Null_Mutex > _ptr;

      // service_cleanup_delay
      //
      public:
      ::iccm::dds::Duration_t const& service_cleanup_delay () const;
      void service_cleanup_delay (::iccm::dds::Duration_t const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::Duration_t > service_cleanup_delay_;

      // history_kind
      //
      public:
      ::iccm::dds::HistoryQosPolicyKind const& history_kind () const;
      void history_kind (::iccm::dds::HistoryQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::HistoryQosPolicyKind > history_kind_;

      // history_depth
      //
      public:
      ::XMLSchema::long_ const& history_depth () const;
      void history_depth (::XMLSchema::long_ const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::long_ > history_depth_;

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
      DurabilityServiceQosPolicy (::iccm::dds::Duration_t const& service_cleanup_delay__,
                                  ::iccm::dds::HistoryQosPolicyKind const& history_kind__,
                                  ::XMLSchema::long_ const& history_depth__,
                                  ::XMLSchema::long_ const& max_samples__,
                                  ::XMLSchema::long_ const& max_instances__,
                                  ::XMLSchema::long_ const& max_samples_per_instance__);

      DurabilityServiceQosPolicy (::XSCRT::XML::Element< char > const&);
      DurabilityServiceQosPolicy (DurabilityServiceQosPolicy const& s);

      DurabilityServiceQosPolicy&
      operator= (DurabilityServiceQosPolicy const& s);

      private:
      char regulator__;
    };


    class SchedulingClassQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (SchedulingClassQosPolicyKind const& a, SchedulingClassQosPolicyKind const& b);

      friend bool
      operator!= (SchedulingClassQosPolicyKind const& a, SchedulingClassQosPolicyKind const& b);

      private:
      SchedulingClassQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (SchedulingClassQosPolicyKind const &a, SchedulingClassQosPolicyKind const &b);

    bool operator!= (SchedulingClassQosPolicyKind const &a, SchedulingClassQosPolicyKind const &b);


    class SchedulingClassQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < SchedulingClassQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::SchedulingClassQosPolicyKind const& kind () const;
      void kind (::iccm::dds::SchedulingClassQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingClassQosPolicyKind > kind_;

      public:
      SchedulingClassQosPolicy (::iccm::dds::SchedulingClassQosPolicyKind const& kind__);

      SchedulingClassQosPolicy (::XSCRT::XML::Element< char > const&);
      SchedulingClassQosPolicy (SchedulingClassQosPolicy const& s);

      SchedulingClassQosPolicy&
      operator= (SchedulingClassQosPolicy const& s);

      private:
      char regulator__;
    };


    class SchedulingPriorityQosPolicyKind : public ::XSCRT::Type
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

      friend bool
      operator== (SchedulingPriorityQosPolicyKind const& a, SchedulingPriorityQosPolicyKind const& b);

      friend bool
      operator!= (SchedulingPriorityQosPolicyKind const& a, SchedulingPriorityQosPolicyKind const& b);

      private:
      SchedulingPriorityQosPolicyKind (Value v);

      Value v_;
    };

    bool operator== (SchedulingPriorityQosPolicyKind const &a, SchedulingPriorityQosPolicyKind const &b);

    bool operator!= (SchedulingPriorityQosPolicyKind const &a, SchedulingPriorityQosPolicyKind const &b);


    class SchedulingPriorityQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < SchedulingPriorityQosPolicy, ACE_Null_Mutex > _ptr;

      // kind
      //
      public:
      ::iccm::dds::SchedulingPriorityQosPolicyKind const& kind () const;
      void kind (::iccm::dds::SchedulingPriorityQosPolicyKind const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingPriorityQosPolicyKind > kind_;

      public:
      SchedulingPriorityQosPolicy (::iccm::dds::SchedulingPriorityQosPolicyKind const& kind__);

      SchedulingPriorityQosPolicy (::XSCRT::XML::Element< char > const&);
      SchedulingPriorityQosPolicy (SchedulingPriorityQosPolicy const& s);

      SchedulingPriorityQosPolicy&
      operator= (SchedulingPriorityQosPolicy const& s);

      private:
      char regulator__;
    };


    class SchedulingQosPolicy : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < SchedulingQosPolicy, ACE_Null_Mutex > _ptr;

      // scheduling_class
      //
      public:
      ::iccm::dds::SchedulingClassQosPolicy const& scheduling_class () const;
      void scheduling_class (::iccm::dds::SchedulingClassQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingClassQosPolicy > scheduling_class_;

      // scheduling_priority_kind
      //
      public:
      ::iccm::dds::SchedulingPriorityQosPolicy const& scheduling_priority_kind () const;
      void scheduling_priority_kind (::iccm::dds::SchedulingPriorityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingPriorityQosPolicy > scheduling_priority_kind_;

      // scheduling_priority
      //
      public:
      ::XMLSchema::long_ const& scheduling_priority () const;
      void scheduling_priority (::XMLSchema::long_ const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::long_ > scheduling_priority_;

      public:
      SchedulingQosPolicy (::iccm::dds::SchedulingClassQosPolicy const& scheduling_class__,
                           ::iccm::dds::SchedulingPriorityQosPolicy const& scheduling_priority_kind__,
                           ::XMLSchema::long_ const& scheduling_priority__);

      SchedulingQosPolicy (::XSCRT::XML::Element< char > const&);
      SchedulingQosPolicy (SchedulingQosPolicy const& s);

      SchedulingQosPolicy&
      operator= (SchedulingQosPolicy const& s);

      private:
      char regulator__;
    };


    class DomainParticipantFactoryQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DomainParticipantFactoryQos, ACE_Null_Mutex > _ptr;

      // entity_factory
      //
      public:
      ::iccm::dds::EntityFactoryQosPolicy const& entity_factory () const;
      void entity_factory (::iccm::dds::EntityFactoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > entity_factory_;

      public:
      DomainParticipantFactoryQos (::iccm::dds::EntityFactoryQosPolicy const& entity_factory__);

      DomainParticipantFactoryQos (::XSCRT::XML::Element< char > const&);
      DomainParticipantFactoryQos (DomainParticipantFactoryQos const& s);

      DomainParticipantFactoryQos&
      operator= (DomainParticipantFactoryQos const& s);

      private:
      char regulator__;
    };


    class DataReaderQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DataReaderQos, ACE_Null_Mutex > _ptr;

      // durability
      //
      public:
      ::iccm::dds::DurabilityQosPolicy const& durability () const;
      void durability (::iccm::dds::DurabilityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicy > durability_;

      // deadline
      //
      public:
      ::iccm::dds::DeadlineQosPolicy const& deadline () const;
      void deadline (::iccm::dds::DeadlineQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DeadlineQosPolicy > deadline_;

      // latency_budget
      //
      public:
      ::iccm::dds::LatencyBudgetQosPolicy const& latency_budget () const;
      void latency_budget (::iccm::dds::LatencyBudgetQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LatencyBudgetQosPolicy > latency_budget_;

      // liveliness
      //
      public:
      ::iccm::dds::LivelinessQosPolicy const& liveliness () const;
      void liveliness (::iccm::dds::LivelinessQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicy > liveliness_;

      // reliability
      //
      public:
      ::iccm::dds::ReliabilityQosPolicy const& reliability () const;
      void reliability (::iccm::dds::ReliabilityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicy > reliability_;

      // destination_order
      //
      public:
      ::iccm::dds::DestinationOrderQosPolicy const& destination_order () const;
      void destination_order (::iccm::dds::DestinationOrderQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicy > destination_order_;

      // history
      //
      public:
      ::iccm::dds::HistoryQosPolicy const& history () const;
      void history (::iccm::dds::HistoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::HistoryQosPolicy > history_;

      // resource_limits
      //
      public:
      ::iccm::dds::ResourceLimitsQosPolicy const& resource_limits () const;
      void resource_limits (::iccm::dds::ResourceLimitsQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ResourceLimitsQosPolicy > resource_limits_;

      // ownership
      //
      public:
      ::iccm::dds::OwnershipQosPolicy const& ownership () const;
      void ownership (::iccm::dds::OwnershipQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicy > ownership_;

      // time_based_filter
      //
      public:
      ::iccm::dds::TimeBasedFilterQosPolicy const& time_based_filter () const;
      void time_based_filter (::iccm::dds::TimeBasedFilterQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::TimeBasedFilterQosPolicy > time_based_filter_;

      // reader_data_lifecycle
      //
      public:
      ::iccm::dds::ReaderDataLifecycleQosPolicy const& reader_data_lifecycle () const;
      void reader_data_lifecycle (::iccm::dds::ReaderDataLifecycleQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ReaderDataLifecycleQosPolicy > reader_data_lifecycle_;

      // name
      //
      public:
      ::XMLSchema::string< char > const& name () const;
      ::XMLSchema::string< char >& name ();
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      public:
      DataReaderQos (::iccm::dds::DurabilityQosPolicy const& durability__,
                     ::iccm::dds::DeadlineQosPolicy const& deadline__,
                     ::iccm::dds::LatencyBudgetQosPolicy const& latency_budget__,
                     ::iccm::dds::LivelinessQosPolicy const& liveliness__,
                     ::iccm::dds::ReliabilityQosPolicy const& reliability__,
                     ::iccm::dds::DestinationOrderQosPolicy const& destination_order__,
                     ::iccm::dds::HistoryQosPolicy const& history__,
                     ::iccm::dds::ResourceLimitsQosPolicy const& resource_limits__,
                     ::iccm::dds::OwnershipQosPolicy const& ownership__,
                     ::iccm::dds::TimeBasedFilterQosPolicy const& time_based_filter__,
                     ::iccm::dds::ReaderDataLifecycleQosPolicy const& reader_data_lifecycle__,
                     ::XMLSchema::string< char > const& name__);

      DataReaderQos (::XSCRT::XML::Element< char > const&);
      DataReaderQos (DataReaderQos const& s);

      DataReaderQos&
      operator= (DataReaderQos const& s);

      private:
      char regulator__;
    };


    class DataWriterQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DataWriterQos, ACE_Null_Mutex > _ptr;

      // durability
      //
      public:
      ::iccm::dds::DurabilityQosPolicy const& durability () const;
      void durability (::iccm::dds::DurabilityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicy > durability_;

      // deadline
      //
      public:
      ::iccm::dds::DeadlineQosPolicy const& deadline () const;
      void deadline (::iccm::dds::DeadlineQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DeadlineQosPolicy > deadline_;

      // latency_budget
      //
      public:
      ::iccm::dds::LatencyBudgetQosPolicy const& latency_budget () const;
      void latency_budget (::iccm::dds::LatencyBudgetQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LatencyBudgetQosPolicy > latency_budget_;

      // liveliness
      //
      public:
      ::iccm::dds::LivelinessQosPolicy const& liveliness () const;
      void liveliness (::iccm::dds::LivelinessQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicy > liveliness_;

      // reliability
      //
      public:
      ::iccm::dds::ReliabilityQosPolicy const& reliability () const;
      void reliability (::iccm::dds::ReliabilityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicy > reliability_;

      // destination_order
      //
      public:
      ::iccm::dds::DestinationOrderQosPolicy const& destination_order () const;
      void destination_order (::iccm::dds::DestinationOrderQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicy > destination_order_;

      // history
      //
      public:
      ::iccm::dds::HistoryQosPolicy const& history () const;
      void history (::iccm::dds::HistoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::HistoryQosPolicy > history_;

      // resource_limits
      //
      public:
      ::iccm::dds::ResourceLimitsQosPolicy const& resource_limits () const;
      void resource_limits (::iccm::dds::ResourceLimitsQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::ResourceLimitsQosPolicy > resource_limits_;

      // transport_priorty
      //
      public:
      ::iccm::dds::TransportPriorityQosPolicy const& transport_priorty () const;
      void transport_priorty (::iccm::dds::TransportPriorityQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::TransportPriorityQosPolicy > transport_priorty_;

      // lifespan
      //
      public:
      ::iccm::dds::LifespanQosPolicy const& lifespan () const;
      void lifespan (::iccm::dds::LifespanQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::LifespanQosPolicy > lifespan_;

      // ownership
      //
      public:
      ::iccm::dds::OwnershipQosPolicy const& ownership () const;
      void ownership (::iccm::dds::OwnershipQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicy > ownership_;

      // ownership_strength
      //
      public:
      ::iccm::dds::OwnershipStrengthQosPolicy const& ownership_strength () const;
      void ownership_strength (::iccm::dds::OwnershipStrengthQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::OwnershipStrengthQosPolicy > ownership_strength_;

      // writer_data_lifecycle
      //
      public:
      ::iccm::dds::WriterDataLifecycleQosPolicy const& writer_data_lifecycle () const;
      void writer_data_lifecycle (::iccm::dds::WriterDataLifecycleQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::WriterDataLifecycleQosPolicy > writer_data_lifecycle_;

      // name
      //
      public:
      ::XMLSchema::string< char > const& name () const;
      ::XMLSchema::string< char >& name ();
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      public:
      DataWriterQos (::iccm::dds::DurabilityQosPolicy const& durability__,
                     ::iccm::dds::DeadlineQosPolicy const& deadline__,
                     ::iccm::dds::LatencyBudgetQosPolicy const& latency_budget__,
                     ::iccm::dds::LivelinessQosPolicy const& liveliness__,
                     ::iccm::dds::ReliabilityQosPolicy const& reliability__,
                     ::iccm::dds::DestinationOrderQosPolicy const& destination_order__,
                     ::iccm::dds::HistoryQosPolicy const& history__,
                     ::iccm::dds::ResourceLimitsQosPolicy const& resource_limits__,
                     ::iccm::dds::TransportPriorityQosPolicy const& transport_priorty__,
                     ::iccm::dds::LifespanQosPolicy const& lifespan__,
                     ::iccm::dds::OwnershipQosPolicy const& ownership__,
                     ::iccm::dds::OwnershipStrengthQosPolicy const& ownership_strength__,
                     ::iccm::dds::WriterDataLifecycleQosPolicy const& writer_data_lifecycle__,
                     ::XMLSchema::string< char > const& name__);

      DataWriterQos (::XSCRT::XML::Element< char > const&);
      DataWriterQos (DataWriterQos const& s);

      DataWriterQos&
      operator= (DataWriterQos const& s);

      private:
      char regulator__;
    };


    class PublisherQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < PublisherQos, ACE_Null_Mutex > _ptr;

      // presentation
      //
      public:
      ::iccm::dds::PresentationQosPolicy const& presentation () const;
      void presentation (::iccm::dds::PresentationQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::PresentationQosPolicy > presentation_;

      // entity_factory
      //
      public:
      ::iccm::dds::EntityFactoryQosPolicy const& entity_factory () const;
      void entity_factory (::iccm::dds::EntityFactoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > entity_factory_;

      // datawriter
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > >::iterator datawriter_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > >::const_iterator datawriter_const_iterator;
      datawriter_iterator begin_datawriter ();
      datawriter_iterator end_datawriter ();
      datawriter_const_iterator begin_datawriter () const;
      datawriter_const_iterator end_datawriter () const;
      void add_datawriter ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_datawriter_ptr ( std::basic_string<char> idref );
      void set_datawriter_ptr (std::basic_string<char> idref );
      size_t count_datawriter (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > > datawriter_;

      // name
      //
      public:
      ::XMLSchema::string< char > const& name () const;
      ::XMLSchema::string< char >& name ();
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      public:
      PublisherQos (::iccm::dds::PresentationQosPolicy const& presentation__,
                    ::iccm::dds::EntityFactoryQosPolicy const& entity_factory__,
                    ::XMLSchema::string< char > const& name__);

      PublisherQos (::XSCRT::XML::Element< char > const&);
      PublisherQos (PublisherQos const& s);

      PublisherQos&
      operator= (PublisherQos const& s);

      private:
      char regulator__;
    };


    class SubscriberQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < SubscriberQos, ACE_Null_Mutex > _ptr;

      // presentation
      //
      public:
      ::iccm::dds::PresentationQosPolicy const& presentation () const;
      void presentation (::iccm::dds::PresentationQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::PresentationQosPolicy > presentation_;

      // entity_factory
      //
      public:
      ::iccm::dds::EntityFactoryQosPolicy const& entity_factory () const;
      void entity_factory (::iccm::dds::EntityFactoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > entity_factory_;

      // datareader
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > >::iterator datareader_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > >::const_iterator datareader_const_iterator;
      datareader_iterator begin_datareader ();
      datareader_iterator end_datareader ();
      datareader_const_iterator begin_datareader () const;
      datareader_const_iterator end_datareader () const;
      void add_datareader ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_datareader_ptr ( std::basic_string<char> idref );
      void set_datareader_ptr (std::basic_string<char> idref );
      size_t count_datareader (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > > datareader_;

      // name
      //
      public:
      ::XMLSchema::string< char > const& name () const;
      ::XMLSchema::string< char >& name ();
      void name (::XMLSchema::string< char > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< char > > name_;

      public:
      SubscriberQos (::iccm::dds::PresentationQosPolicy const& presentation__,
                     ::iccm::dds::EntityFactoryQosPolicy const& entity_factory__,
                     ::XMLSchema::string< char > const& name__);

      SubscriberQos (::XSCRT::XML::Element< char > const&);
      SubscriberQos (SubscriberQos const& s);

      SubscriberQos&
      operator= (SubscriberQos const& s);

      private:
      char regulator__;
    };


    class DomainParticipantQos : public ::XSCRT::Type
    {
      typedef ::XSCRT::Type Base;

      public:
      typedef ACE_Refcounted_Auto_Ptr < DomainParticipantQos, ACE_Null_Mutex > _ptr;

      // entity_factory
      //
      public:
      bool entity_factory_p () const;
      ::iccm::dds::EntityFactoryQosPolicy const& entity_factory () const;
      void entity_factory (::iccm::dds::EntityFactoryQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > entity_factory_;

      // watchdog_scheduling
      //
      public:
      bool watchdog_scheduling_p () const;
      ::iccm::dds::SchedulingQosPolicy const& watchdog_scheduling () const;
      void watchdog_scheduling (::iccm::dds::SchedulingQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingQosPolicy > watchdog_scheduling_;

      // listener_scheduling
      //
      public:
      bool listener_scheduling_p () const;
      ::iccm::dds::SchedulingQosPolicy const& listener_scheduling () const;
      void listener_scheduling (::iccm::dds::SchedulingQosPolicy const& );

      protected:
      ::std::auto_ptr< ::iccm::dds::SchedulingQosPolicy > listener_scheduling_;

      // datawriter
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > >::iterator datawriter_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > >::const_iterator datawriter_const_iterator;
      datawriter_iterator begin_datawriter ();
      datawriter_iterator end_datawriter ();
      datawriter_const_iterator begin_datawriter () const;
      datawriter_const_iterator end_datawriter () const;
      void add_datawriter ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_datawriter_ptr ( std::basic_string<char> idref );
      void set_datawriter_ptr (std::basic_string<char> idref );
      size_t count_datawriter (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex > > datawriter_;

      // datareader
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > >::iterator datareader_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > >::const_iterator datareader_const_iterator;
      datareader_iterator begin_datareader ();
      datareader_iterator end_datareader ();
      datareader_const_iterator begin_datareader () const;
      datareader_const_iterator end_datareader () const;
      void add_datareader ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_datareader_ptr ( std::basic_string<char> idref );
      void set_datareader_ptr (std::basic_string<char> idref );
      size_t count_datareader (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex > > datareader_;

      // publisher
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex > >::iterator publisher_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex > >::const_iterator publisher_const_iterator;
      publisher_iterator begin_publisher ();
      publisher_iterator end_publisher ();
      publisher_const_iterator begin_publisher () const;
      publisher_const_iterator end_publisher () const;
      void add_publisher ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_publisher_ptr ( std::basic_string<char> idref );
      void set_publisher_ptr (std::basic_string<char> idref );
      size_t count_publisher (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex > > publisher_;

      // subscriber
      //
      public:
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex > >::iterator subscriber_iterator;
      typedef ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex > >::const_iterator subscriber_const_iterator;
      subscriber_iterator begin_subscriber ();
      subscriber_iterator end_subscriber ();
      subscriber_const_iterator begin_subscriber () const;
      subscriber_const_iterator end_subscriber () const;
      void add_subscriber ( ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex > const& );
      XSCRT::Type* get_subscriber_ptr ( std::basic_string<char> idref );
      void set_subscriber_ptr (std::basic_string<char> idref );
      size_t count_subscriber (void) const;

      protected:
      ::std::list< ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex > > subscriber_;

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
}

namespace iccm
{
  namespace dds
  {
    namespace reader
    {
      ::iccm::dds::DomainParticipantFactoryQos
      domain (xercesc::DOMDocument const*);
    }


    namespace reader
    {
      ::iccm::dds::DomainParticipantQos
      participant (xercesc::DOMDocument const*);
    }
  }
}

#include "dds.inl"

#endif // DDS_H
