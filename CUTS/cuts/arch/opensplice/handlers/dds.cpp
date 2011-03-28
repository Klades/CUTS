#include "dds.h"

namespace iccm
{
  namespace dds
  {
    // Duration_t
    //

    Duration_t::
    Duration_t (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "sec")
        {
          ::XMLSchema::long_ t (a);
          sec (t);
        }

        else if (n == "nanosec")
        {
          ::XMLSchema::unsignedLong t (a);
          nanosec (t);
        }

        else
        {
        }
      }
    }

    // TransportPriorityQosPolicy
    //

    TransportPriorityQosPolicy::
    TransportPriorityQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("value"))
        {
          value_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          value_->container (this);
        }

        else
        {
        }
      }
    }

    // PartitionQosPolicy
    //

    PartitionQosPolicy::
    PartitionQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("name"))
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
          name_->container (this);
        }

        else
        {
        }
      }
    }

    // LifespanQosPolicy
    //

    LifespanQosPolicy::
    LifespanQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("period"))
        {
          period_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          period_->container (this);
        }

        else
        {
        }
      }
    }

    // DurabilityQosPolicyKind
    //

    DurabilityQosPolicyKind::
    DurabilityQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "VOLATILE_DURABILITY_QOS") v_ = VOLATILE_DURABILITY_QOS_l;
      else if (v == "TRANSIENT_LOCAL_DURABILITY_QOS") v_ = TRANSIENT_LOCAL_DURABILITY_QOS_l;
      else if (v == "TRANSIENT_DURABILITY_QOS") v_ = TRANSIENT_DURABILITY_QOS_l;
      else if (v == "PERSISTENT_DURABILITY_QOS") v_ = PERSISTENT_DURABILITY_QOS_l;
      else
      {
      }
    }

    DurabilityQosPolicyKind::
    DurabilityQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "VOLATILE_DURABILITY_QOS") v_ = VOLATILE_DURABILITY_QOS_l;
      else if (v == "TRANSIENT_LOCAL_DURABILITY_QOS") v_ = TRANSIENT_LOCAL_DURABILITY_QOS_l;
      else if (v == "TRANSIENT_DURABILITY_QOS") v_ = TRANSIENT_DURABILITY_QOS_l;
      else if (v == "PERSISTENT_DURABILITY_QOS") v_ = PERSISTENT_DURABILITY_QOS_l;
      else
      {
      }
    }

    DurabilityQosPolicyKind const DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS (DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS_l);
    DurabilityQosPolicyKind const DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS (DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS_l);
    DurabilityQosPolicyKind const DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS (DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS_l);
    DurabilityQosPolicyKind const DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS (DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS_l);

    // DurabilityQosPolicy
    //

    DurabilityQosPolicy::
    DurabilityQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicyKind > (new ::iccm::dds::DurabilityQosPolicyKind (e));
          kind_->container (this);
        }

        else
        {
        }
      }
    }

    // PresentationQosPolicyAccessScopeKind
    //

    PresentationQosPolicyAccessScopeKind::
    PresentationQosPolicyAccessScopeKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "INSTANCE_PRESENTATION_QOS") v_ = INSTANCE_PRESENTATION_QOS_l;
      else if (v == "TOPIC_PRESENTATION_QOS") v_ = TOPIC_PRESENTATION_QOS_l;
      else if (v == "GROUP_PRESENTATION_QOS") v_ = GROUP_PRESENTATION_QOS_l;
      else
      {
      }
    }

    PresentationQosPolicyAccessScopeKind::
    PresentationQosPolicyAccessScopeKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "INSTANCE_PRESENTATION_QOS") v_ = INSTANCE_PRESENTATION_QOS_l;
      else if (v == "TOPIC_PRESENTATION_QOS") v_ = TOPIC_PRESENTATION_QOS_l;
      else if (v == "GROUP_PRESENTATION_QOS") v_ = GROUP_PRESENTATION_QOS_l;
      else
      {
      }
    }

    PresentationQosPolicyAccessScopeKind const PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS (PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS_l);
    PresentationQosPolicyAccessScopeKind const PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS (PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS_l);
    PresentationQosPolicyAccessScopeKind const PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS (PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS_l);

    // PresentationQosPolicy
    //

    PresentationQosPolicy::
    PresentationQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("access_scope"))
        {
          access_scope_ = ::std::auto_ptr< ::iccm::dds::PresentationQosPolicyAccessScopeKind > (new ::iccm::dds::PresentationQosPolicyAccessScopeKind (e));
          access_scope_->container (this);
        }

        else if (n == ACE_TEXT("coherent_access"))
        {
          coherent_access_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
          coherent_access_->container (this);
        }

        else if (n == ACE_TEXT("ordered_access"))
        {
          ordered_access_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
          ordered_access_->container (this);
        }

        else
        {
        }
      }
    }

    // DeadlineQosPolicy
    //

    DeadlineQosPolicy::
    DeadlineQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("period"))
        {
          period_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          period_->container (this);
        }

        else
        {
        }
      }
    }

    // LatencyBudgetQosPolicy
    //

    LatencyBudgetQosPolicy::
    LatencyBudgetQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("duration"))
        {
          duration_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          duration_->container (this);
        }

        else
        {
        }
      }
    }

    // OwnershipQosPolicyKind
    //

    OwnershipQosPolicyKind::
    OwnershipQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "SHARED_OWNERSHIP_QOS") v_ = SHARED_OWNERSHIP_QOS_l;
      else if (v == "EXCLUSIVE_OWNERSHIP_QOS") v_ = EXCLUSIVE_OWNERSHIP_QOS_l;
      else
      {
      }
    }

    OwnershipQosPolicyKind::
    OwnershipQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "SHARED_OWNERSHIP_QOS") v_ = SHARED_OWNERSHIP_QOS_l;
      else if (v == "EXCLUSIVE_OWNERSHIP_QOS") v_ = EXCLUSIVE_OWNERSHIP_QOS_l;
      else
      {
      }
    }

    OwnershipQosPolicyKind const OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS (OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS_l);
    OwnershipQosPolicyKind const OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS (OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS_l);

    // OwnershipQosPolicy
    //

    OwnershipQosPolicy::
    OwnershipQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicyKind > (new ::iccm::dds::OwnershipQosPolicyKind (e));
          kind_->container (this);
        }

        else
        {
        }
      }
    }

    // OwnershipStrengthQosPolicy
    //

    OwnershipStrengthQosPolicy::
    OwnershipStrengthQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("value"))
        {
          value_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          value_->container (this);
        }

        else
        {
        }
      }
    }

    // LivelinessQosPolicyKind
    //

    LivelinessQosPolicyKind::
    LivelinessQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "AUTOMATIC_LIVELINESS_QOS") v_ = AUTOMATIC_LIVELINESS_QOS_l;
      else if (v == "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS") v_ = MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l;
      else if (v == "MANUAL_BY_TOPIC_LIVELINESS_QOS") v_ = MANUAL_BY_TOPIC_LIVELINESS_QOS_l;
      else
      {
      }
    }

    LivelinessQosPolicyKind::
    LivelinessQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "AUTOMATIC_LIVELINESS_QOS") v_ = AUTOMATIC_LIVELINESS_QOS_l;
      else if (v == "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS") v_ = MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l;
      else if (v == "MANUAL_BY_TOPIC_LIVELINESS_QOS") v_ = MANUAL_BY_TOPIC_LIVELINESS_QOS_l;
      else
      {
      }
    }

    LivelinessQosPolicyKind const LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS (LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS_l);
    LivelinessQosPolicyKind const LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS (LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS_l);
    LivelinessQosPolicyKind const LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS (LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS_l);

    // LivelinessQosPolicy
    //

    LivelinessQosPolicy::
    LivelinessQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicyKind > (new ::iccm::dds::LivelinessQosPolicyKind (e));
          kind_->container (this);
        }

        else if (n == ACE_TEXT("lease_duration"))
        {
          lease_duration_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          lease_duration_->container (this);
        }

        else
        {
        }
      }
    }

    // TimeBasedFilterQosPolicy
    //

    TimeBasedFilterQosPolicy::
    TimeBasedFilterQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("minimum_separation"))
        {
          minimum_separation_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          minimum_separation_->container (this);
        }

        else
        {
        }
      }
    }

    // ReliabilityQosPolicyKind
    //

    ReliabilityQosPolicyKind::
    ReliabilityQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "BEST_EFFORT_RELIABILITY_QOS") v_ = BEST_EFFORT_RELIABILITY_QOS_l;
      else if (v == "RELIABLE_RELIABILITY_QOS") v_ = RELIABLE_RELIABILITY_QOS_l;
      else
      {
      }
    }

    ReliabilityQosPolicyKind::
    ReliabilityQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "BEST_EFFORT_RELIABILITY_QOS") v_ = BEST_EFFORT_RELIABILITY_QOS_l;
      else if (v == "RELIABLE_RELIABILITY_QOS") v_ = RELIABLE_RELIABILITY_QOS_l;
      else
      {
      }
    }

    ReliabilityQosPolicyKind const ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS (ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS_l);
    ReliabilityQosPolicyKind const ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS (ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS_l);

    // ReliabilityQosPolicy
    //

    ReliabilityQosPolicy::
    ReliabilityQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicyKind > (new ::iccm::dds::ReliabilityQosPolicyKind (e));
          kind_->container (this);
        }

        else if (n == ACE_TEXT("max_blocking_time"))
        {
          max_blocking_time_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          max_blocking_time_->container (this);
        }

        else
        {
        }
      }
    }

    // DestinationOrderQosPolicyKind
    //

    DestinationOrderQosPolicyKind::
    DestinationOrderQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS") v_ = BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l;
      else if (v == "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS") v_ = BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l;
      else
      {
      }
    }

    DestinationOrderQosPolicyKind::
    DestinationOrderQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS") v_ = BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l;
      else if (v == "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS") v_ = BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l;
      else
      {
      }
    }

    DestinationOrderQosPolicyKind const DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS (DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS_l);
    DestinationOrderQosPolicyKind const DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS (DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS_l);

    // DestinationOrderQosPolicy
    //

    DestinationOrderQosPolicy::
    DestinationOrderQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicyKind > (new ::iccm::dds::DestinationOrderQosPolicyKind (e));
          kind_->container (this);
        }

        else
        {
        }
      }
    }

    // HistoryQosPolicyKind
    //

    HistoryQosPolicyKind::
    HistoryQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "KEEP_LAST_HISTORY_QOS") v_ = KEEP_LAST_HISTORY_QOS_l;
      else if (v == "KEEP_ALL_HISTORY_QOS") v_ = KEEP_ALL_HISTORY_QOS_l;
      else
      {
      }
    }

    HistoryQosPolicyKind::
    HistoryQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "KEEP_LAST_HISTORY_QOS") v_ = KEEP_LAST_HISTORY_QOS_l;
      else if (v == "KEEP_ALL_HISTORY_QOS") v_ = KEEP_ALL_HISTORY_QOS_l;
      else
      {
      }
    }

    HistoryQosPolicyKind const HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS (HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS_l);
    HistoryQosPolicyKind const HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS (HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS_l);

    // HistoryQosPolicy
    //

    HistoryQosPolicy::
    HistoryQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::HistoryQosPolicyKind > (new ::iccm::dds::HistoryQosPolicyKind (e));
          kind_->container (this);
        }

        else if (n == ACE_TEXT("depth"))
        {
          depth_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          depth_->container (this);
        }

        else
        {
        }
      }
    }

    // ResourceLimitsQosPolicy
    //

    ResourceLimitsQosPolicy::
    ResourceLimitsQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("max_samples"))
        {
          max_samples_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_samples_->container (this);
        }

        else if (n == ACE_TEXT("max_instances"))
        {
          max_instances_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_instances_->container (this);
        }

        else if (n == ACE_TEXT("max_samples_per_instance"))
        {
          max_samples_per_instance_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_samples_per_instance_->container (this);
        }

        else
        {
        }
      }
    }

    // EntityFactoryQosPolicy
    //

    EntityFactoryQosPolicy::
    EntityFactoryQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("autoenable_created_entities"))
        {
          autoenable_created_entities_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
          autoenable_created_entities_->container (this);
        }

        else
        {
        }
      }
    }

    // WriterDataLifecycleQosPolicy
    //

    WriterDataLifecycleQosPolicy::
    WriterDataLifecycleQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("autoenable_created_entities"))
        {
          autoenable_created_entities_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
          autoenable_created_entities_->container (this);
        }

        else
        {
        }
      }
    }

    // ReaderDataLifecycleQosPolicy
    //

    ReaderDataLifecycleQosPolicy::
    ReaderDataLifecycleQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("autopurge_nowriter_samples_delay"))
        {
          autopurge_nowriter_samples_delay_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          autopurge_nowriter_samples_delay_->container (this);
        }

        else if (n == ACE_TEXT("autopurge_disposed_samples_delay"))
        {
          autopurge_disposed_samples_delay_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          autopurge_disposed_samples_delay_->container (this);
        }

        else
        {
        }
      }
    }

    // DurabilityServiceQosPolicy
    //

    DurabilityServiceQosPolicy::
    DurabilityServiceQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("service_cleanup_delay"))
        {
          service_cleanup_delay_ = ::std::auto_ptr< ::iccm::dds::Duration_t > (new ::iccm::dds::Duration_t (e));
          service_cleanup_delay_->container (this);
        }

        else if (n == ACE_TEXT("history_kind"))
        {
          history_kind_ = ::std::auto_ptr< ::iccm::dds::HistoryQosPolicyKind > (new ::iccm::dds::HistoryQosPolicyKind (e));
          history_kind_->container (this);
        }

        else if (n == ACE_TEXT("history_depth"))
        {
          history_depth_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          history_depth_->container (this);
        }

        else if (n == ACE_TEXT("max_samples"))
        {
          max_samples_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_samples_->container (this);
        }

        else if (n == ACE_TEXT("max_instances"))
        {
          max_instances_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_instances_->container (this);
        }

        else if (n == ACE_TEXT("max_samples_per_instance"))
        {
          max_samples_per_instance_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          max_samples_per_instance_->container (this);
        }

        else
        {
        }
      }
    }

    // SchedulingClassQosPolicyKind
    //

    SchedulingClassQosPolicyKind::
    SchedulingClassQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "SCHEDULING_DEFUALT") v_ = SCHEDULING_DEFUALT_l;
      else if (v == "SCHEDULING_TIMESHARING") v_ = SCHEDULING_TIMESHARING_l;
      else if (v == "SCHEDULING_REALTIME") v_ = SCHEDULING_REALTIME_l;
      else
      {
      }
    }

    SchedulingClassQosPolicyKind::
    SchedulingClassQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "SCHEDULING_DEFUALT") v_ = SCHEDULING_DEFUALT_l;
      else if (v == "SCHEDULING_TIMESHARING") v_ = SCHEDULING_TIMESHARING_l;
      else if (v == "SCHEDULING_REALTIME") v_ = SCHEDULING_REALTIME_l;
      else
      {
      }
    }

    SchedulingClassQosPolicyKind const SchedulingClassQosPolicyKind::SCHEDULING_DEFUALT (SchedulingClassQosPolicyKind::SCHEDULING_DEFUALT_l);
    SchedulingClassQosPolicyKind const SchedulingClassQosPolicyKind::SCHEDULING_TIMESHARING (SchedulingClassQosPolicyKind::SCHEDULING_TIMESHARING_l);
    SchedulingClassQosPolicyKind const SchedulingClassQosPolicyKind::SCHEDULING_REALTIME (SchedulingClassQosPolicyKind::SCHEDULING_REALTIME_l);

    // SchedulingClassQosPolicy
    //

    SchedulingClassQosPolicy::
    SchedulingClassQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::SchedulingClassQosPolicyKind > (new ::iccm::dds::SchedulingClassQosPolicyKind (e));
          kind_->container (this);
        }

        else
        {
        }
      }
    }

    // SchedulingPriorityQosPolicyKind
    //

    SchedulingPriorityQosPolicyKind::
    SchedulingPriorityQosPolicyKind (::XSCRT::XML::Element< char > const& e)
    : ::XSCRT::Type (e)
    {
      ::std::basic_string< char > v (e.value ());

      if (v == "PRIORITY_RELATIVE") v_ = PRIORITY_RELATIVE_l;
      else if (v == "PRIORITY_ABSOLUTE") v_ = PRIORITY_ABSOLUTE_l;
      else
      {
      }
    }

    SchedulingPriorityQosPolicyKind::
    SchedulingPriorityQosPolicyKind (::XSCRT::XML::Attribute< char > const& a)
    : ::XSCRT::Type (a)
    {
      ::std::basic_string< char > v (a.value ());

      if (v == "PRIORITY_RELATIVE") v_ = PRIORITY_RELATIVE_l;
      else if (v == "PRIORITY_ABSOLUTE") v_ = PRIORITY_ABSOLUTE_l;
      else
      {
      }
    }

    SchedulingPriorityQosPolicyKind const SchedulingPriorityQosPolicyKind::PRIORITY_RELATIVE (SchedulingPriorityQosPolicyKind::PRIORITY_RELATIVE_l);
    SchedulingPriorityQosPolicyKind const SchedulingPriorityQosPolicyKind::PRIORITY_ABSOLUTE (SchedulingPriorityQosPolicyKind::PRIORITY_ABSOLUTE_l);

    // SchedulingPriorityQosPolicy
    //

    SchedulingPriorityQosPolicy::
    SchedulingPriorityQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("kind"))
        {
          kind_ = ::std::auto_ptr< ::iccm::dds::SchedulingPriorityQosPolicyKind > (new ::iccm::dds::SchedulingPriorityQosPolicyKind (e));
          kind_->container (this);
        }

        else
        {
        }
      }
    }

    // SchedulingQosPolicy
    //

    SchedulingQosPolicy::
    SchedulingQosPolicy (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("scheduling_class"))
        {
          scheduling_class_ = ::std::auto_ptr< ::iccm::dds::SchedulingClassQosPolicy > (new ::iccm::dds::SchedulingClassQosPolicy (e));
          scheduling_class_->container (this);
        }

        else if (n == ACE_TEXT("scheduling_priority_kind"))
        {
          scheduling_priority_kind_ = ::std::auto_ptr< ::iccm::dds::SchedulingPriorityQosPolicy > (new ::iccm::dds::SchedulingPriorityQosPolicy (e));
          scheduling_priority_kind_->container (this);
        }

        else if (n == ACE_TEXT("scheduling_priority"))
        {
          scheduling_priority_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
          scheduling_priority_->container (this);
        }

        else
        {
        }
      }
    }

    // DomainParticipantFactoryQos
    //

    DomainParticipantFactoryQos::
    DomainParticipantFactoryQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("entity_factory"))
        {
          entity_factory_ = ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > (new ::iccm::dds::EntityFactoryQosPolicy (e));
          entity_factory_->container (this);
        }

        else
        {
        }
      }
    }

    // DataReaderQos
    //

    DataReaderQos::
    DataReaderQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("durability"))
        {
          durability_ = ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicy > (new ::iccm::dds::DurabilityQosPolicy (e));
          durability_->container (this);
        }

        else if (n == ACE_TEXT("deadline"))
        {
          deadline_ = ::std::auto_ptr< ::iccm::dds::DeadlineQosPolicy > (new ::iccm::dds::DeadlineQosPolicy (e));
          deadline_->container (this);
        }

        else if (n == ACE_TEXT("latency_budget"))
        {
          latency_budget_ = ::std::auto_ptr< ::iccm::dds::LatencyBudgetQosPolicy > (new ::iccm::dds::LatencyBudgetQosPolicy (e));
          latency_budget_->container (this);
        }

        else if (n == ACE_TEXT("liveliness"))
        {
          liveliness_ = ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicy > (new ::iccm::dds::LivelinessQosPolicy (e));
          liveliness_->container (this);
        }

        else if (n == ACE_TEXT("reliability"))
        {
          reliability_ = ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicy > (new ::iccm::dds::ReliabilityQosPolicy (e));
          reliability_->container (this);
        }

        else if (n == ACE_TEXT("destination_order"))
        {
          destination_order_ = ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicy > (new ::iccm::dds::DestinationOrderQosPolicy (e));
          destination_order_->container (this);
        }

        else if (n == ACE_TEXT("history"))
        {
          history_ = ::std::auto_ptr< ::iccm::dds::HistoryQosPolicy > (new ::iccm::dds::HistoryQosPolicy (e));
          history_->container (this);
        }

        else if (n == ACE_TEXT("resource_limits"))
        {
          resource_limits_ = ::std::auto_ptr< ::iccm::dds::ResourceLimitsQosPolicy > (new ::iccm::dds::ResourceLimitsQosPolicy (e));
          resource_limits_->container (this);
        }

        else if (n == ACE_TEXT("ownership"))
        {
          ownership_ = ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicy > (new ::iccm::dds::OwnershipQosPolicy (e));
          ownership_->container (this);
        }

        else if (n == ACE_TEXT("time_based_filter"))
        {
          time_based_filter_ = ::std::auto_ptr< ::iccm::dds::TimeBasedFilterQosPolicy > (new ::iccm::dds::TimeBasedFilterQosPolicy (e));
          time_based_filter_->container (this);
        }

        else if (n == ACE_TEXT("reader_data_lifecycle"))
        {
          reader_data_lifecycle_ = ::std::auto_ptr< ::iccm::dds::ReaderDataLifecycleQosPolicy > (new ::iccm::dds::ReaderDataLifecycleQosPolicy (e));
          reader_data_lifecycle_->container (this);
        }

        else
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else
        {
        }
      }
    }

    // DataWriterQos
    //

    DataWriterQos::
    DataWriterQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("durability"))
        {
          durability_ = ::std::auto_ptr< ::iccm::dds::DurabilityQosPolicy > (new ::iccm::dds::DurabilityQosPolicy (e));
          durability_->container (this);
        }

        else if (n == ACE_TEXT("deadline"))
        {
          deadline_ = ::std::auto_ptr< ::iccm::dds::DeadlineQosPolicy > (new ::iccm::dds::DeadlineQosPolicy (e));
          deadline_->container (this);
        }

        else if (n == ACE_TEXT("latency_budget"))
        {
          latency_budget_ = ::std::auto_ptr< ::iccm::dds::LatencyBudgetQosPolicy > (new ::iccm::dds::LatencyBudgetQosPolicy (e));
          latency_budget_->container (this);
        }

        else if (n == ACE_TEXT("liveliness"))
        {
          liveliness_ = ::std::auto_ptr< ::iccm::dds::LivelinessQosPolicy > (new ::iccm::dds::LivelinessQosPolicy (e));
          liveliness_->container (this);
        }

        else if (n == ACE_TEXT("reliability"))
        {
          reliability_ = ::std::auto_ptr< ::iccm::dds::ReliabilityQosPolicy > (new ::iccm::dds::ReliabilityQosPolicy (e));
          reliability_->container (this);
        }

        else if (n == ACE_TEXT("destination_order"))
        {
          destination_order_ = ::std::auto_ptr< ::iccm::dds::DestinationOrderQosPolicy > (new ::iccm::dds::DestinationOrderQosPolicy (e));
          destination_order_->container (this);
        }

        else if (n == ACE_TEXT("history"))
        {
          history_ = ::std::auto_ptr< ::iccm::dds::HistoryQosPolicy > (new ::iccm::dds::HistoryQosPolicy (e));
          history_->container (this);
        }

        else if (n == ACE_TEXT("resource_limits"))
        {
          resource_limits_ = ::std::auto_ptr< ::iccm::dds::ResourceLimitsQosPolicy > (new ::iccm::dds::ResourceLimitsQosPolicy (e));
          resource_limits_->container (this);
        }

        else if (n == ACE_TEXT("transport_priorty"))
        {
          transport_priorty_ = ::std::auto_ptr< ::iccm::dds::TransportPriorityQosPolicy > (new ::iccm::dds::TransportPriorityQosPolicy (e));
          transport_priorty_->container (this);
        }

        else if (n == ACE_TEXT("lifespan"))
        {
          lifespan_ = ::std::auto_ptr< ::iccm::dds::LifespanQosPolicy > (new ::iccm::dds::LifespanQosPolicy (e));
          lifespan_->container (this);
        }

        else if (n == ACE_TEXT("ownership"))
        {
          ownership_ = ::std::auto_ptr< ::iccm::dds::OwnershipQosPolicy > (new ::iccm::dds::OwnershipQosPolicy (e));
          ownership_->container (this);
        }

        else if (n == ACE_TEXT("ownership_strength"))
        {
          ownership_strength_ = ::std::auto_ptr< ::iccm::dds::OwnershipStrengthQosPolicy > (new ::iccm::dds::OwnershipStrengthQosPolicy (e));
          ownership_strength_->container (this);
        }

        else if (n == ACE_TEXT("writer_data_lifecycle"))
        {
          writer_data_lifecycle_ = ::std::auto_ptr< ::iccm::dds::WriterDataLifecycleQosPolicy > (new ::iccm::dds::WriterDataLifecycleQosPolicy (e));
          writer_data_lifecycle_->container (this);
        }

        else
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else
        {
        }
      }
    }

    // PublisherQos
    //

    PublisherQos::
    PublisherQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("presentation"))
        {
          presentation_ = ::std::auto_ptr< ::iccm::dds::PresentationQosPolicy > (new ::iccm::dds::PresentationQosPolicy (e));
          presentation_->container (this);
        }

        else if (n == ACE_TEXT("entity_factory"))
        {
          entity_factory_ = ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > (new ::iccm::dds::EntityFactoryQosPolicy (e));
          entity_factory_->container (this);
        }

        else if (n == ACE_TEXT("datawriter"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex >  t (new ::iccm::dds::DataWriterQos (e));
          add_datawriter (t);
        }

        else
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else
        {
        }
      }
    }

    // SubscriberQos
    //

    SubscriberQos::
    SubscriberQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("presentation"))
        {
          presentation_ = ::std::auto_ptr< ::iccm::dds::PresentationQosPolicy > (new ::iccm::dds::PresentationQosPolicy (e));
          presentation_->container (this);
        }

        else if (n == ACE_TEXT("entity_factory"))
        {
          entity_factory_ = ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > (new ::iccm::dds::EntityFactoryQosPolicy (e));
          entity_factory_->container (this);
        }

        else if (n == ACE_TEXT("datareader"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex >  t (new ::iccm::dds::DataReaderQos (e));
          add_datareader (t);
        }

        else
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (a));
          name_->container (this);
        }

        else
        {
        }
      }
    }

    // DomainParticipantQos
    //

    DomainParticipantQos::
    DomainParticipantQos (::XSCRT::XML::Element< char > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< char > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< char > e (p.next_element ());
        ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == ACE_TEXT("entity_factory"))
        {
          ::iccm::dds::EntityFactoryQosPolicy t (e);
          entity_factory (t);
        }

        else if (n == ACE_TEXT("watchdog_scheduling"))
        {
          ::iccm::dds::SchedulingQosPolicy t (e);
          watchdog_scheduling (t);
        }

        else if (n == ACE_TEXT("listener_scheduling"))
        {
          ::iccm::dds::SchedulingQosPolicy t (e);
          listener_scheduling (t);
        }

        else if (n == ACE_TEXT("datawriter"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex >  t (new ::iccm::dds::DataWriterQos (e));
          add_datawriter (t);
        }

        else if (n == ACE_TEXT("datareader"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex >  t (new ::iccm::dds::DataReaderQos (e));
          add_datareader (t);
        }

        else if (n == ACE_TEXT("publisher"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex >  t (new ::iccm::dds::PublisherQos (e));
          add_publisher (t);
        }

        else if (n == ACE_TEXT("subscriber"))
        {
          ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex >  t (new ::iccm::dds::SubscriberQos (e));
          add_subscriber (t);
        }

        else
        {
        }
      }
    }
  }
}

namespace iccm
{
  namespace dds
  {
    namespace reader
    {
      ::iccm::dds::DomainParticipantFactoryQos
      domain (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("domain"))
        {
          ::iccm::dds::DomainParticipantFactoryQos r (e);

          (*TSS_ID_Map)->resolve_idref();

          return r;
        }

        else
        {
          throw 1;
        }
      }
    }

    namespace reader
    {
      ::iccm::dds::DomainParticipantQos
      participant (xercesc::DOMDocument const* d)
      {
        //Initiate our Singleton as an ACE_TSS object (ensures thread
        //specific storage
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


        ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
        if (e.name () == ACE_TEXT("participant"))
        {
          ::iccm::dds::DomainParticipantQos r (e);

          (*TSS_ID_Map)->resolve_idref();

          return r;
        }

        else
        {
          throw 1;
        }
      }
    }
  }
}

#include "XMLSchema/TypeInfo.hpp"

namespace iccm
{
  namespace dds
  {
    namespace
    {
      ::XMLSchema::TypeInfoInitializer < char > XMLSchemaTypeInfoInitializer_ (::XSCRT::extended_type_info_map ());

      struct Duration_tTypeInfoInitializer
      {
        Duration_tTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::Duration_t));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      Duration_tTypeInfoInitializer Duration_tTypeInfoInitializer_;

      struct TransportPriorityQosPolicyTypeInfoInitializer
      {
        TransportPriorityQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::TransportPriorityQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      TransportPriorityQosPolicyTypeInfoInitializer TransportPriorityQosPolicyTypeInfoInitializer_;

      struct PartitionQosPolicyTypeInfoInitializer
      {
        PartitionQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::PartitionQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      PartitionQosPolicyTypeInfoInitializer PartitionQosPolicyTypeInfoInitializer_;

      struct LifespanQosPolicyTypeInfoInitializer
      {
        LifespanQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::LifespanQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      LifespanQosPolicyTypeInfoInitializer LifespanQosPolicyTypeInfoInitializer_;

      struct DurabilityQosPolicyKindTypeInfoInitializer
      {
        DurabilityQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (DurabilityQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DurabilityQosPolicyKindTypeInfoInitializer DurabilityQosPolicyKindTypeInfoInitializer_;

      struct DurabilityQosPolicyTypeInfoInitializer
      {
        DurabilityQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DurabilityQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DurabilityQosPolicyTypeInfoInitializer DurabilityQosPolicyTypeInfoInitializer_;

      struct PresentationQosPolicyAccessScopeKindTypeInfoInitializer
      {
        PresentationQosPolicyAccessScopeKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (PresentationQosPolicyAccessScopeKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      PresentationQosPolicyAccessScopeKindTypeInfoInitializer PresentationQosPolicyAccessScopeKindTypeInfoInitializer_;

      struct PresentationQosPolicyTypeInfoInitializer
      {
        PresentationQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::PresentationQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      PresentationQosPolicyTypeInfoInitializer PresentationQosPolicyTypeInfoInitializer_;

      struct DeadlineQosPolicyTypeInfoInitializer
      {
        DeadlineQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DeadlineQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DeadlineQosPolicyTypeInfoInitializer DeadlineQosPolicyTypeInfoInitializer_;

      struct LatencyBudgetQosPolicyTypeInfoInitializer
      {
        LatencyBudgetQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::LatencyBudgetQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      LatencyBudgetQosPolicyTypeInfoInitializer LatencyBudgetQosPolicyTypeInfoInitializer_;

      struct OwnershipQosPolicyKindTypeInfoInitializer
      {
        OwnershipQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (OwnershipQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      OwnershipQosPolicyKindTypeInfoInitializer OwnershipQosPolicyKindTypeInfoInitializer_;

      struct OwnershipQosPolicyTypeInfoInitializer
      {
        OwnershipQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::OwnershipQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      OwnershipQosPolicyTypeInfoInitializer OwnershipQosPolicyTypeInfoInitializer_;

      struct OwnershipStrengthQosPolicyTypeInfoInitializer
      {
        OwnershipStrengthQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::OwnershipStrengthQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      OwnershipStrengthQosPolicyTypeInfoInitializer OwnershipStrengthQosPolicyTypeInfoInitializer_;

      struct LivelinessQosPolicyKindTypeInfoInitializer
      {
        LivelinessQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (LivelinessQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      LivelinessQosPolicyKindTypeInfoInitializer LivelinessQosPolicyKindTypeInfoInitializer_;

      struct LivelinessQosPolicyTypeInfoInitializer
      {
        LivelinessQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::LivelinessQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      LivelinessQosPolicyTypeInfoInitializer LivelinessQosPolicyTypeInfoInitializer_;

      struct TimeBasedFilterQosPolicyTypeInfoInitializer
      {
        TimeBasedFilterQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::TimeBasedFilterQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      TimeBasedFilterQosPolicyTypeInfoInitializer TimeBasedFilterQosPolicyTypeInfoInitializer_;

      struct ReliabilityQosPolicyKindTypeInfoInitializer
      {
        ReliabilityQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (ReliabilityQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      ReliabilityQosPolicyKindTypeInfoInitializer ReliabilityQosPolicyKindTypeInfoInitializer_;

      struct ReliabilityQosPolicyTypeInfoInitializer
      {
        ReliabilityQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::ReliabilityQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      ReliabilityQosPolicyTypeInfoInitializer ReliabilityQosPolicyTypeInfoInitializer_;

      struct DestinationOrderQosPolicyKindTypeInfoInitializer
      {
        DestinationOrderQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (DestinationOrderQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DestinationOrderQosPolicyKindTypeInfoInitializer DestinationOrderQosPolicyKindTypeInfoInitializer_;

      struct DestinationOrderQosPolicyTypeInfoInitializer
      {
        DestinationOrderQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DestinationOrderQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DestinationOrderQosPolicyTypeInfoInitializer DestinationOrderQosPolicyTypeInfoInitializer_;

      struct HistoryQosPolicyKindTypeInfoInitializer
      {
        HistoryQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (HistoryQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      HistoryQosPolicyKindTypeInfoInitializer HistoryQosPolicyKindTypeInfoInitializer_;

      struct HistoryQosPolicyTypeInfoInitializer
      {
        HistoryQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::HistoryQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      HistoryQosPolicyTypeInfoInitializer HistoryQosPolicyTypeInfoInitializer_;

      struct ResourceLimitsQosPolicyTypeInfoInitializer
      {
        ResourceLimitsQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::ResourceLimitsQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      ResourceLimitsQosPolicyTypeInfoInitializer ResourceLimitsQosPolicyTypeInfoInitializer_;

      struct EntityFactoryQosPolicyTypeInfoInitializer
      {
        EntityFactoryQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::EntityFactoryQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      EntityFactoryQosPolicyTypeInfoInitializer EntityFactoryQosPolicyTypeInfoInitializer_;

      struct WriterDataLifecycleQosPolicyTypeInfoInitializer
      {
        WriterDataLifecycleQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::WriterDataLifecycleQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      WriterDataLifecycleQosPolicyTypeInfoInitializer WriterDataLifecycleQosPolicyTypeInfoInitializer_;

      struct ReaderDataLifecycleQosPolicyTypeInfoInitializer
      {
        ReaderDataLifecycleQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::ReaderDataLifecycleQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      ReaderDataLifecycleQosPolicyTypeInfoInitializer ReaderDataLifecycleQosPolicyTypeInfoInitializer_;

      struct DurabilityServiceQosPolicyTypeInfoInitializer
      {
        DurabilityServiceQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DurabilityServiceQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DurabilityServiceQosPolicyTypeInfoInitializer DurabilityServiceQosPolicyTypeInfoInitializer_;

      struct SchedulingClassQosPolicyKindTypeInfoInitializer
      {
        SchedulingClassQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (SchedulingClassQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SchedulingClassQosPolicyKindTypeInfoInitializer SchedulingClassQosPolicyKindTypeInfoInitializer_;

      struct SchedulingClassQosPolicyTypeInfoInitializer
      {
        SchedulingClassQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::SchedulingClassQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SchedulingClassQosPolicyTypeInfoInitializer SchedulingClassQosPolicyTypeInfoInitializer_;

      struct SchedulingPriorityQosPolicyKindTypeInfoInitializer
      {
        SchedulingPriorityQosPolicyKindTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (SchedulingPriorityQosPolicyKind));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));

          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SchedulingPriorityQosPolicyKindTypeInfoInitializer SchedulingPriorityQosPolicyKindTypeInfoInitializer_;

      struct SchedulingPriorityQosPolicyTypeInfoInitializer
      {
        SchedulingPriorityQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::SchedulingPriorityQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SchedulingPriorityQosPolicyTypeInfoInitializer SchedulingPriorityQosPolicyTypeInfoInitializer_;

      struct SchedulingQosPolicyTypeInfoInitializer
      {
        SchedulingQosPolicyTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::SchedulingQosPolicy));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SchedulingQosPolicyTypeInfoInitializer SchedulingQosPolicyTypeInfoInitializer_;

      struct DomainParticipantFactoryQosTypeInfoInitializer
      {
        DomainParticipantFactoryQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DomainParticipantFactoryQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DomainParticipantFactoryQosTypeInfoInitializer DomainParticipantFactoryQosTypeInfoInitializer_;

      struct DataReaderQosTypeInfoInitializer
      {
        DataReaderQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DataReaderQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DataReaderQosTypeInfoInitializer DataReaderQosTypeInfoInitializer_;

      struct DataWriterQosTypeInfoInitializer
      {
        DataWriterQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DataWriterQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DataWriterQosTypeInfoInitializer DataWriterQosTypeInfoInitializer_;

      struct PublisherQosTypeInfoInitializer
      {
        PublisherQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::PublisherQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      PublisherQosTypeInfoInitializer PublisherQosTypeInfoInitializer_;

      struct SubscriberQosTypeInfoInitializer
      {
        SubscriberQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::SubscriberQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      SubscriberQosTypeInfoInitializer SubscriberQosTypeInfoInitializer_;

      struct DomainParticipantQosTypeInfoInitializer
      {
        DomainParticipantQosTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::iccm::dds::DomainParticipantQos));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      DomainParticipantQosTypeInfoInitializer DomainParticipantQosTypeInfoInitializer_;
    }
  }
}

