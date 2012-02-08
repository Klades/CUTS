#include "dds.h"

namespace iccm
{
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

  // TopicDataQosPolicy
  //

  TopicDataQosPolicy::
  TopicDataQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {
  }

  TopicDataQosPolicy::
  TopicDataQosPolicy (::XSCRT::XML::Attribute< char > const& a)
  :
  Base (a),
  regulator__ ()
  {
  }

  // GroupDataQosPolicy
  //

  GroupDataQosPolicy::
  GroupDataQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {
  }

  GroupDataQosPolicy::
  GroupDataQosPolicy (::XSCRT::XML::Attribute< char > const& a)
  :
  Base (a),
  regulator__ ()
  {
  }

  // UserDataQosPolicy
  //

  UserDataQosPolicy::
  UserDataQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {
  }

  UserDataQosPolicy::
  UserDataQosPolicy (::XSCRT::XML::Attribute< char > const& a)
  :
  Base (a),
  regulator__ ()
  {
  }

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
        ::XMLSchema::long_ t (e);
        value (t);
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
        ::XMLSchema::string< char > t (e);
        name (t);
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
        ::iccm::Duration_t t (e);
        period (t);
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
        ::iccm::Duration_t t (e);
        service_cleanup_delay (t);
      }

      else if (n == ACE_TEXT("history_kind"))
      {
        ::iccm::HistoryQosPolicyKind t (e);
        history_kind (t);
      }

      else if (n == ACE_TEXT("history_depth"))
      {
        ::XMLSchema::long_ t (e);
        history_depth (t);
      }

      else if (n == ACE_TEXT("max_samples"))
      {
        ::XMLSchema::long_ t (e);
        max_samples (t);
      }

      else if (n == ACE_TEXT("max_instances"))
      {
        ::XMLSchema::long_ t (e);
        max_instances (t);
      }

      else if (n == ACE_TEXT("max_samples_per_instance"))
      {
        ::XMLSchema::long_ t (e);
        max_samples_per_instance (t);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::DurabilityQosPolicyKind > (new ::iccm::DurabilityQosPolicyKind (e));
        kind_->container (this);
      }

      else
      {
      }
    }
  }

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
        access_scope_ = ::std::auto_ptr< ::iccm::PresentationQosPolicyAccessScopeKind > (new ::iccm::PresentationQosPolicyAccessScopeKind (e));
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
        period_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
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
        duration_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
        duration_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::OwnershipQosPolicyKind > (new ::iccm::OwnershipQosPolicyKind (e));
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
        kind_ = ::std::auto_ptr< ::iccm::LivelinessQosPolicyKind > (new ::iccm::LivelinessQosPolicyKind (e));
        kind_->container (this);
      }

      else if (n == ACE_TEXT("lease_duration"))
      {
        lease_duration_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
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
        minimum_separation_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
        minimum_separation_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::ReliabilityQosPolicyKind > (new ::iccm::ReliabilityQosPolicyKind (e));
        kind_->container (this);
      }

      else if (n == ACE_TEXT("max_blocking_time"))
      {
        max_blocking_time_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
        max_blocking_time_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::DestinationOrderQosPolicyKind > (new ::iccm::DestinationOrderQosPolicyKind (e));
        kind_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::HistoryQosPolicyKind > (new ::iccm::HistoryQosPolicyKind (e));
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
        autopurge_nowriter_samples_delay_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
        autopurge_nowriter_samples_delay_->container (this);
      }

      else if (n == ACE_TEXT("autopurge_disposed_samples_delay"))
      {
        autopurge_disposed_samples_delay_ = ::std::auto_ptr< ::iccm::Duration_t > (new ::iccm::Duration_t (e));
        autopurge_disposed_samples_delay_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::SchedulingClassQosPolicyKind > (new ::iccm::SchedulingClassQosPolicyKind (e));
        kind_->container (this);
      }

      else
      {
      }
    }
  }

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
        kind_ = ::std::auto_ptr< ::iccm::SchedulingPriorityQosPolicyKind > (new ::iccm::SchedulingPriorityQosPolicyKind (e));
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
        scheduling_class_ = ::std::auto_ptr< ::iccm::SchedulingClassQosPolicy > (new ::iccm::SchedulingClassQosPolicy (e));
        scheduling_class_->container (this);
      }

      else if (n == ACE_TEXT("scheduling_priority_kind"))
      {
        scheduling_priority_kind_ = ::std::auto_ptr< ::iccm::SchedulingPriorityQosPolicy > (new ::iccm::SchedulingPriorityQosPolicy (e));
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

  // TopicQos
  //

  TopicQos::
  TopicQos (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == ACE_TEXT("topic_data"))
      {
        ::iccm::TopicDataQosPolicy t (e);
        topic_data (t);
      }

      else if (n == ACE_TEXT("durability"))
      {
        ::iccm::DurabilityQosPolicy t (e);
        durability (t);
      }

      else if (n == ACE_TEXT("durability_service"))
      {
        ::iccm::DurabilityServiceQosPolicy t (e);
        durability_service (t);
      }

      else if (n == ACE_TEXT("deadline"))
      {
        ::iccm::DeadlineQosPolicy t (e);
        deadline (t);
      }

      else if (n == ACE_TEXT("latency_budget"))
      {
        ::iccm::LatencyBudgetQosPolicy t (e);
        latency_budget (t);
      }

      else if (n == ACE_TEXT("liveliness"))
      {
        ::iccm::LivelinessQosPolicy t (e);
        liveliness (t);
      }

      else if (n == ACE_TEXT("destination_order"))
      {
        ::iccm::DestinationOrderQosPolicy t (e);
        destination_order (t);
      }

      else if (n == ACE_TEXT("history"))
      {
        ::iccm::HistoryQosPolicy t (e);
        history (t);
      }

      else if (n == ACE_TEXT("resource_limits"))
      {
        ::iccm::ResourceLimitsQosPolicy t (e);
        resource_limits (t);
      }

      else if (n == ACE_TEXT("transport_priority"))
      {
        ::iccm::TransportPriorityQosPolicy t (e);
        transport_priority (t);
      }

      else if (n == ACE_TEXT("lifespan"))
      {
        ::iccm::LifespanQosPolicy t (e);
        lifespan (t);
      }

      else if (n == ACE_TEXT("ownership"))
      {
        ::iccm::OwnershipQosPolicy t (e);
        ownership (t);
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
        ::iccm::EntityFactoryQosPolicy t (e);
        entity_factory (t);
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
        ::iccm::DurabilityQosPolicy t (e);
        durability (t);
      }

      else if (n == ACE_TEXT("deadline"))
      {
        ::iccm::DeadlineQosPolicy t (e);
        deadline (t);
      }

      else if (n == ACE_TEXT("latency_budget"))
      {
        ::iccm::LatencyBudgetQosPolicy t (e);
        latency_budget (t);
      }

      else if (n == ACE_TEXT("liveliness"))
      {
        ::iccm::LivelinessQosPolicy t (e);
        liveliness (t);
      }

      else if (n == ACE_TEXT("reliability"))
      {
        ::iccm::ReliabilityQosPolicy t (e);
        reliability (t);
      }

      else if (n == ACE_TEXT("destination_order"))
      {
        ::iccm::DestinationOrderQosPolicy t (e);
        destination_order (t);
      }

      else if (n == ACE_TEXT("history"))
      {
        ::iccm::HistoryQosPolicy t (e);
        history (t);
      }

      else if (n == ACE_TEXT("resource_limits"))
      {
        ::iccm::ResourceLimitsQosPolicy t (e);
        resource_limits (t);
      }

      else if (n == ACE_TEXT("user_data"))
      {
        ::iccm::UserDataQosPolicy t (e);
        user_data (t);
      }

      else if (n == ACE_TEXT("ownership"))
      {
        ::iccm::OwnershipQosPolicy t (e);
        ownership (t);
      }

      else if (n == ACE_TEXT("time_based_filter"))
      {
        ::iccm::TimeBasedFilterQosPolicy t (e);
        time_based_filter (t);
      }

      else if (n == ACE_TEXT("reader_data_lifecycle"))
      {
        ::iccm::ReaderDataLifecycleQosPolicy t (e);
        reader_data_lifecycle (t);
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

      else if (n == "subscriber")
      {
        ::XMLSchema::string< char > t (a);
        subscriber (t);
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
        ::iccm::DurabilityQosPolicy t (e);
        durability (t);
      }

      else if (n == ACE_TEXT("deadline"))
      {
        ::iccm::DeadlineQosPolicy t (e);
        deadline (t);
      }

      else if (n == ACE_TEXT("latency_budget"))
      {
        ::iccm::LatencyBudgetQosPolicy t (e);
        latency_budget (t);
      }

      else if (n == ACE_TEXT("liveliness"))
      {
        ::iccm::LivelinessQosPolicy t (e);
        liveliness (t);
      }

      else if (n == ACE_TEXT("reliability"))
      {
        ::iccm::ReliabilityQosPolicy t (e);
        reliability (t);
      }

      else if (n == ACE_TEXT("destination_order"))
      {
        ::iccm::DestinationOrderQosPolicy t (e);
        destination_order (t);
      }

      else if (n == ACE_TEXT("history"))
      {
        ::iccm::HistoryQosPolicy t (e);
        history (t);
      }

      else if (n == ACE_TEXT("resource_limits"))
      {
        ::iccm::ResourceLimitsQosPolicy t (e);
        resource_limits (t);
      }

      else if (n == ACE_TEXT("transport_priorty"))
      {
        ::iccm::TransportPriorityQosPolicy t (e);
        transport_priorty (t);
      }

      else if (n == ACE_TEXT("lifespan"))
      {
        ::iccm::LifespanQosPolicy t (e);
        lifespan (t);
      }

      else if (n == ACE_TEXT("user_data"))
      {
        ::iccm::UserDataQosPolicy t (e);
        user_data (t);
      }

      else if (n == ACE_TEXT("ownership"))
      {
        ::iccm::OwnershipQosPolicy t (e);
        ownership (t);
      }

      else if (n == ACE_TEXT("ownership_strength"))
      {
        ::iccm::OwnershipStrengthQosPolicy t (e);
        ownership_strength (t);
      }

      else if (n == ACE_TEXT("writer_data_lifecycle"))
      {
        ::iccm::WriterDataLifecycleQosPolicy t (e);
        writer_data_lifecycle (t);
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

      else if (n == "publisher")
      {
        ::XMLSchema::string< char > t (a);
        publisher (t);
      }

      else if (n == "isinstance")
      {
        ::XMLSchema::boolean t (a);
        isinstance (t);
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
        ::iccm::PresentationQosPolicy t (e);
        presentation (t);
      }

      else if (n == ACE_TEXT("partition"))
      {
        ::iccm::PartitionQosPolicy t (e);
        partition (t);
      }

      else if (n == ACE_TEXT("group_data"))
      {
        ::iccm::GroupDataQosPolicy t (e);
        group_data (t);
      }

      else if (n == ACE_TEXT("entity_factory"))
      {
        ::iccm::EntityFactoryQosPolicy t (e);
        entity_factory (t);
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
        ::iccm::PresentationQosPolicy t (e);
        presentation (t);
      }

      else if (n == ACE_TEXT("partition"))
      {
        ::iccm::PartitionQosPolicy t (e);
        partition (t);
      }

      else if (n == ACE_TEXT("group_data"))
      {
        ::iccm::GroupDataQosPolicy t (e);
        group_data (t);
      }

      else if (n == ACE_TEXT("entity_factory"))
      {
        ::iccm::EntityFactoryQosPolicy t (e);
        entity_factory (t);
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

      if (n == ACE_TEXT("user_data"))
      {
        ::iccm::UserDataQosPolicy t (e);
        user_data (t);
      }

      else if (n == ACE_TEXT("entity_factory"))
      {
        ::iccm::EntityFactoryQosPolicy t (e);
        entity_factory (t);
      }

      else if (n == ACE_TEXT("watchdog_scheduling"))
      {
        ::iccm::SchedulingQosPolicy t (e);
        watchdog_scheduling (t);
      }

      else if (n == ACE_TEXT("listener_scheduling"))
      {
        ::iccm::SchedulingQosPolicy t (e);
        listener_scheduling (t);
      }

      else if (n == ACE_TEXT("publisher"))
      {
        ACE_Refcounted_Auto_Ptr < ::iccm::PublisherQos, ACE_Null_Mutex >  t (new ::iccm::PublisherQos (e));
        add_publisher (t);
      }

      else if (n == ACE_TEXT("subscriber"))
      {
        ACE_Refcounted_Auto_Ptr < ::iccm::SubscriberQos, ACE_Null_Mutex >  t (new ::iccm::SubscriberQos (e));
        add_subscriber (t);
      }

      else if (n == ACE_TEXT("datawriter"))
      {
        ACE_Refcounted_Auto_Ptr < ::iccm::DataWriterQos, ACE_Null_Mutex >  t (new ::iccm::DataWriterQos (e));
        add_datawriter (t);
      }

      else if (n == ACE_TEXT("datareader"))
      {
        ACE_Refcounted_Auto_Ptr < ::iccm::DataReaderQos, ACE_Null_Mutex >  t (new ::iccm::DataReaderQos (e));
        add_datareader (t);
      }

      else
      {
      }
    }
  }
}

namespace iccm
{
  namespace reader
  {
    ::iccm::DomainParticipantFactoryQos
    domain (xercesc::DOMDocument const* d)
    {
      //Initiate our Singleton as an ACE_TSS object (ensures thread
      //specific storage
      ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == ACE_TEXT("domain"))
      {
        ::iccm::DomainParticipantFactoryQos r (e);

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
    ::iccm::DomainParticipantQos
    participant (xercesc::DOMDocument const* d)
    {
      //Initiate our Singleton as an ACE_TSS object (ensures thread
      //specific storage
      ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());


      ::XSCRT::XML::Element< char > e (d->getDocumentElement ());
      if (e.name () == ACE_TEXT("participant"))
      {
        ::iccm::DomainParticipantQos r (e);

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

