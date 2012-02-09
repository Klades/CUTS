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

    if (v == "SCHEDULING_DEFAULT") v_ = SCHEDULING_DEFAULT_l;
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

    if (v == "SCHEDULING_DEFAULT") v_ = SCHEDULING_DEFAULT_l;
    else if (v == "SCHEDULING_TIMESHARING") v_ = SCHEDULING_TIMESHARING_l;
    else if (v == "SCHEDULING_REALTIME") v_ = SCHEDULING_REALTIME_l;
    else
    {
    }
  }

  SchedulingClassQosPolicyKind const SchedulingClassQosPolicyKind::SCHEDULING_DEFAULT (SchedulingClassQosPolicyKind::SCHEDULING_DEFAULT_l);
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

  // StringSeq
  //

  StringSeq::
  StringSeq (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == ACE_TEXT("item"))
      {
        ACE_Refcounted_Auto_Ptr < ::XMLSchema::string< char >, ACE_Null_Mutex >  t (new ::XMLSchema::string< char > (e));
        add_item (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "value")
      {
        ::XMLSchema::long_ t (a);
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
        name_ = ::std::auto_ptr< ::iccm::StringSeq > (new ::iccm::StringSeq (e));
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "duration")
      {
        ::XMLSchema::double_ t (a);
        duration (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "history_depth")
      {
        ::XMLSchema::long_ t (a);
        history_depth (t);
      }

      else if (n == "max_samples")
      {
        ::XMLSchema::long_ t (a);
        max_samples (t);
      }

      else if (n == "max_instances")
      {
        ::XMLSchema::long_ t (a);
        max_instances (t);
      }

      else if (n == "max_samples_per_instance")
      {
        ::XMLSchema::long_ t (a);
        max_samples_per_instance (t);
      }

      else if (n == "history_kind")
      {
        ::iccm::HistoryQosPolicyKind t (a);
        history_kind (t);
      }

      else if (n == "service_cleanup_delay")
      {
        ::XMLSchema::double_ t (a);
        service_cleanup_delay (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::DurabilityQosPolicyKind t (a);
        kind (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "access_scope")
      {
        ::iccm::PresentationQosPolicyAccessScopeKind t (a);
        access_scope (t);
      }

      else if (n == "coherent_access")
      {
        ::XMLSchema::boolean t (a);
        coherent_access (t);
      }

      else if (n == "ordered_access")
      {
        ::XMLSchema::boolean t (a);
        ordered_access (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "period")
      {
        ::XMLSchema::double_ t (a);
        period (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "duration")
      {
        ::XMLSchema::double_ t (a);
        duration (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::OwnershipQosPolicyKind t (a);
        kind (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "value")
      {
        ::XMLSchema::long_ t (a);
        value (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "lease_duration")
      {
        ::XMLSchema::double_ t (a);
        lease_duration (t);
      }

      else if (n == "kind")
      {
        ::iccm::LivelinessQosPolicyKind t (a);
        kind (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "minimum_separation")
      {
        ::XMLSchema::double_ t (a);
        minimum_separation (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::ReliabilityQosPolicyKind t (a);
        kind (t);
      }

      else if (n == "synchronous")
      {
        ::XMLSchema::boolean t (a);
        synchronous (t);
      }

      else if (n == "max_blocking_time")
      {
        ::XMLSchema::double_ t (a);
        max_blocking_time (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::DestinationOrderQosPolicyKind t (a);
        kind (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::HistoryQosPolicyKind t (a);
        kind (t);
      }

      else if (n == "depth")
      {
        ::XMLSchema::long_ t (a);
        depth (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "max_samples")
      {
        ::XMLSchema::long_ t (a);
        max_samples (t);
      }

      else if (n == "max_instances")
      {
        ::XMLSchema::long_ t (a);
        max_instances (t);
      }

      else if (n == "max_samples_per_instance")
      {
        ::XMLSchema::long_ t (a);
        max_samples_per_instance (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "autoenable_created_entities")
      {
        ::XMLSchema::boolean t (a);
        autoenable_created_entities (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "autopurge_suspended_samples_delay")
      {
        ::XMLSchema::double_ t (a);
        autopurge_suspended_samples_delay (t);
      }

      else if (n == "autounregister_instance_delay")
      {
        ::XMLSchema::double_ t (a);
        autounregister_instance_delay (t);
      }

      else if (n == "autodispose_unregistered_instances")
      {
        ::XMLSchema::boolean t (a);
        autodispose_unregistered_instances (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "autopurge_nowriter_samples_delay")
      {
        ::XMLSchema::double_ t (a);
        autopurge_nowriter_samples_delay (t);
      }

      else if (n == "autopurge_disposed_samples_delay")
      {
        ::XMLSchema::double_ t (a);
        autopurge_disposed_samples_delay (t);
      }

      else if (n == "enable_invalid_samples")
      {
        ::XMLSchema::boolean t (a);
        enable_invalid_samples (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::SchedulingClassQosPolicyKind t (a);
        kind (t);
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

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "kind")
      {
        ::iccm::SchedulingPriorityQosPolicyKind t (a);
        kind (t);
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
        ::iccm::SchedulingClassQosPolicy t (e);
        scheduling_class (t);
      }

      else if (n == ACE_TEXT("scheduling_priority_kind"))
      {
        ::iccm::SchedulingPriorityQosPolicy t (e);
        scheduling_priority_kind (t);
      }

      else
      {
      }
    }

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "scheduling_priority")
      {
        ::XMLSchema::long_ t (a);
        scheduling_priority (t);
      }

      else
      {
      }
    }
  }

  // SubscriptionKeyQosPolicy
  //

  SubscriptionKeyQosPolicy::
  SubscriptionKeyQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_elements ())
    {
      ::XSCRT::XML::Element< char > e (p.next_element ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (e.name ()));

      if (n == ACE_TEXT("key_list"))
      {
        ::iccm::StringSeq t (e);
        key_list (t);
      }

      else
      {
      }
    }

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "use_key_list")
      {
        ::XMLSchema::boolean t (a);
        use_key_list (t);
      }

      else
      {
      }
    }
  }

  // ShareQosPolicy
  //

  ShareQosPolicy::
  ShareQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "name")
      {
        ::XMLSchema::string< char > t (a);
        name (t);
      }

      else if (n == "enable")
      {
        ::XMLSchema::boolean t (a);
        enable (t);
      }

      else
      {
      }
    }
  }

  // ReaderLifespanQosPolicy
  //

  ReaderLifespanQosPolicy::
  ReaderLifespanQosPolicy (::XSCRT::XML::Element< char > const& e)
  :Base (e), regulator__ ()
  {

    ::XSCRT::Parser< char > p (e);

    while (p.more_attributes ())
    {
      ::XSCRT::XML::Attribute< char > a (p.next_attribute ());
      ::std::basic_string< char > n (::XSCRT::XML::uq_name (a.name ()));
      if (n == "duration")
      {
        ::XMLSchema::double_ t (a);
        duration (t);
      }

      else if (n == "use_lifespan")
      {
        ::XMLSchema::boolean t (a);
        use_lifespan (t);
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

      else if (n == ACE_TEXT("subscription_keys"))
      {
        ::iccm::SubscriptionKeyQosPolicy t (e);
        subscription_keys (t);
      }

      else if (n == ACE_TEXT("reader_lifespan"))
      {
        ::iccm::ReaderLifespanQosPolicy t (e);
        reader_lifespan (t);
      }

      else if (n == ACE_TEXT("share"))
      {
        ::iccm::ShareQosPolicy t (e);
        share (t);
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

      else if (n == ACE_TEXT("share"))
      {
        ::iccm::ShareQosPolicy t (e);
        share (t);
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

      else if (n == ACE_TEXT("topic"))
      {
        ACE_Refcounted_Auto_Ptr < ::iccm::TopicQos, ACE_Null_Mutex >  t (new ::iccm::TopicQos (e));
        add_topic (t);
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

