namespace iccm
{
  namespace dds
  {
    // Duration_t
    //

    inline
    Duration_t::
    Duration_t ()
    :
    regulator__ ()
    {
    }

    inline
    Duration_t::
    Duration_t (Duration_t const& s)
    :
    sec_ (s.sec_.get () ? new ::XMLSchema::long_ (*s.sec_) : 0),
    nanosec_ (s.nanosec_.get () ? new ::XMLSchema::unsignedLong (*s.nanosec_) : 0),
    regulator__ ()
    {
      if (sec_.get ()) sec_->container (this);
      if (nanosec_.get ()) nanosec_->container (this);
    }

    inline
    Duration_t& Duration_t::
    operator= (Duration_t const& s)
    {
      if (s.sec_.get ()) sec (*(s.sec_));
      else sec_ = ::std::auto_ptr< ::XMLSchema::long_ > (0);

      if (s.nanosec_.get ()) nanosec (*(s.nanosec_));
      else nanosec_ = ::std::auto_ptr< ::XMLSchema::unsignedLong > (0);

      return *this;
    }


    // Duration_t
    //
    inline
    bool Duration_t::
    sec_p () const
    {
      return sec_.get () != 0;
    }

    inline
    ::XMLSchema::long_ const& Duration_t::
    sec () const
    {
      return *sec_;
    }

    inline
    ::XMLSchema::long_& Duration_t::
    sec ()
    {
      return *sec_;
    }

    inline
    void Duration_t::
    sec (::XMLSchema::long_ const& e)
    {
      if (sec_.get ())
      {
        *sec_ = e;
      }

      else
      {
        sec_ = ::std::auto_ptr< ::XMLSchema::long_ > (new ::XMLSchema::long_ (e));
        sec_->container (this);
      }
    }

    // Duration_t
    //
    inline
    bool Duration_t::
    nanosec_p () const
    {
      return nanosec_.get () != 0;
    }

    inline
    ::XMLSchema::unsignedLong const& Duration_t::
    nanosec () const
    {
      return *nanosec_;
    }

    inline
    ::XMLSchema::unsignedLong& Duration_t::
    nanosec ()
    {
      return *nanosec_;
    }

    inline
    void Duration_t::
    nanosec (::XMLSchema::unsignedLong const& e)
    {
      if (nanosec_.get ())
      {
        *nanosec_ = e;
      }

      else
      {
        nanosec_ = ::std::auto_ptr< ::XMLSchema::unsignedLong > (new ::XMLSchema::unsignedLong (e));
        nanosec_->container (this);
      }
    }


    // TransportPriorityQosPolicy
    //

    inline
    TransportPriorityQosPolicy::
    TransportPriorityQosPolicy (::XMLSchema::long_ const& value__)
    :
    ::XSCRT::Type (),
    value_ (new ::XMLSchema::long_ (value__)),
    regulator__ ()
    {
      value_->container (this);
    }

    inline
    TransportPriorityQosPolicy::
    TransportPriorityQosPolicy (TransportPriorityQosPolicy const& s)
    :
    ::XSCRT::Type (),
    value_ (new ::XMLSchema::long_ (*s.value_)),
    regulator__ ()
    {
      value_->container (this);
    }

    inline
    TransportPriorityQosPolicy& TransportPriorityQosPolicy::
    operator= (TransportPriorityQosPolicy const& s)
    {
      value (*s.value_);

      return *this;
    }


    // TransportPriorityQosPolicy
    //
    inline
    ::XMLSchema::long_ const& TransportPriorityQosPolicy::
    value () const
    {
      return *value_;
    }

    inline
    void TransportPriorityQosPolicy::
    value (::XMLSchema::long_ const& e)
    {
      *value_ = e;
    }


    // PartitionQosPolicy
    //

    inline
    PartitionQosPolicy::
    PartitionQosPolicy (::XMLSchema::string< char > const& name__)
    :
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      name_->container (this);
    }

    inline
    PartitionQosPolicy::
    PartitionQosPolicy (PartitionQosPolicy const& s)
    :
    ::XSCRT::Type (),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      name_->container (this);
    }

    inline
    PartitionQosPolicy& PartitionQosPolicy::
    operator= (PartitionQosPolicy const& s)
    {
      name (*s.name_);

      return *this;
    }


    // PartitionQosPolicy
    //
    inline
    ::XMLSchema::string< char > const& PartitionQosPolicy::
    name () const
    {
      return *name_;
    }

    inline
    void PartitionQosPolicy::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // LifespanQosPolicy
    //

    inline
    LifespanQosPolicy::
    LifespanQosPolicy (::iccm::dds::Duration_t const& period__)
    :
    period_ (new ::iccm::dds::Duration_t (period__)),
    regulator__ ()
    {
      period_->container (this);
    }

    inline
    LifespanQosPolicy::
    LifespanQosPolicy (LifespanQosPolicy const& s)
    :
    ::XSCRT::Type (),
    period_ (new ::iccm::dds::Duration_t (*s.period_)),
    regulator__ ()
    {
      period_->container (this);
    }

    inline
    LifespanQosPolicy& LifespanQosPolicy::
    operator= (LifespanQosPolicy const& s)
    {
      period (*s.period_);

      return *this;
    }


    // LifespanQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& LifespanQosPolicy::
    period () const
    {
      return *period_;
    }

    inline
    void LifespanQosPolicy::
    period (::iccm::dds::Duration_t const& e)
    {
      *period_ = e;
    }


    // DurabilityQosPolicyKind
    //

    inline
    DurabilityQosPolicyKind::Value DurabilityQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::DurabilityQosPolicyKind const& a, ::iccm::dds::DurabilityQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::DurabilityQosPolicyKind const& a, ::iccm::dds::DurabilityQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    DurabilityQosPolicyKind::
    DurabilityQosPolicyKind (DurabilityQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // DurabilityQosPolicy
    //

    inline
    DurabilityQosPolicy::
    DurabilityQosPolicy (::iccm::dds::DurabilityQosPolicyKind const& kind__)
    :
    kind_ (new ::iccm::dds::DurabilityQosPolicyKind (kind__)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    DurabilityQosPolicy::
    DurabilityQosPolicy (DurabilityQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::DurabilityQosPolicyKind (*s.kind_)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    DurabilityQosPolicy& DurabilityQosPolicy::
    operator= (DurabilityQosPolicy const& s)
    {
      kind (*s.kind_);

      return *this;
    }


    // DurabilityQosPolicy
    //
    inline
    ::iccm::dds::DurabilityQosPolicyKind const& DurabilityQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void DurabilityQosPolicy::
    kind (::iccm::dds::DurabilityQosPolicyKind const& e)
    {
      *kind_ = e;
    }


    // PresentationQosPolicyAccessScopeKind
    //

    inline
    PresentationQosPolicyAccessScopeKind::Value PresentationQosPolicyAccessScopeKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::PresentationQosPolicyAccessScopeKind const& a, ::iccm::dds::PresentationQosPolicyAccessScopeKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::PresentationQosPolicyAccessScopeKind const& a, ::iccm::dds::PresentationQosPolicyAccessScopeKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    PresentationQosPolicyAccessScopeKind::
    PresentationQosPolicyAccessScopeKind (PresentationQosPolicyAccessScopeKind::Value v)
    : v_ (v)
    {
    }

    // PresentationQosPolicy
    //

    inline
    PresentationQosPolicy::
    PresentationQosPolicy (::iccm::dds::PresentationQosPolicyAccessScopeKind const& access_scope__,
                           ::XMLSchema::boolean const& coherent_access__,
                           ::XMLSchema::boolean const& ordered_access__)
    :
    access_scope_ (new ::iccm::dds::PresentationQosPolicyAccessScopeKind (access_scope__)),
    coherent_access_ (new ::XMLSchema::boolean (coherent_access__)),
    ordered_access_ (new ::XMLSchema::boolean (ordered_access__)),
    regulator__ ()
    {
      access_scope_->container (this);
      coherent_access_->container (this);
      ordered_access_->container (this);
    }

    inline
    PresentationQosPolicy::
    PresentationQosPolicy (PresentationQosPolicy const& s)
    :
    ::XSCRT::Type (),
    access_scope_ (new ::iccm::dds::PresentationQosPolicyAccessScopeKind (*s.access_scope_)),
    coherent_access_ (new ::XMLSchema::boolean (*s.coherent_access_)),
    ordered_access_ (new ::XMLSchema::boolean (*s.ordered_access_)),
    regulator__ ()
    {
      access_scope_->container (this);
      coherent_access_->container (this);
      ordered_access_->container (this);
    }

    inline
    PresentationQosPolicy& PresentationQosPolicy::
    operator= (PresentationQosPolicy const& s)
    {
      access_scope (*s.access_scope_);

      coherent_access (*s.coherent_access_);

      ordered_access (*s.ordered_access_);

      return *this;
    }


    // PresentationQosPolicy
    //
    inline
    ::iccm::dds::PresentationQosPolicyAccessScopeKind const& PresentationQosPolicy::
    access_scope () const
    {
      return *access_scope_;
    }

    inline
    void PresentationQosPolicy::
    access_scope (::iccm::dds::PresentationQosPolicyAccessScopeKind const& e)
    {
      *access_scope_ = e;
    }

    // PresentationQosPolicy
    //
    inline
    ::XMLSchema::boolean const& PresentationQosPolicy::
    coherent_access () const
    {
      return *coherent_access_;
    }

    inline
    void PresentationQosPolicy::
    coherent_access (::XMLSchema::boolean const& e)
    {
      *coherent_access_ = e;
    }

    // PresentationQosPolicy
    //
    inline
    ::XMLSchema::boolean const& PresentationQosPolicy::
    ordered_access () const
    {
      return *ordered_access_;
    }

    inline
    void PresentationQosPolicy::
    ordered_access (::XMLSchema::boolean const& e)
    {
      *ordered_access_ = e;
    }


    // DeadlineQosPolicy
    //

    inline
    DeadlineQosPolicy::
    DeadlineQosPolicy (::iccm::dds::Duration_t const& period__)
    :
    period_ (new ::iccm::dds::Duration_t (period__)),
    regulator__ ()
    {
      period_->container (this);
    }

    inline
    DeadlineQosPolicy::
    DeadlineQosPolicy (DeadlineQosPolicy const& s)
    :
    ::XSCRT::Type (),
    period_ (new ::iccm::dds::Duration_t (*s.period_)),
    regulator__ ()
    {
      period_->container (this);
    }

    inline
    DeadlineQosPolicy& DeadlineQosPolicy::
    operator= (DeadlineQosPolicy const& s)
    {
      period (*s.period_);

      return *this;
    }


    // DeadlineQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& DeadlineQosPolicy::
    period () const
    {
      return *period_;
    }

    inline
    void DeadlineQosPolicy::
    period (::iccm::dds::Duration_t const& e)
    {
      *period_ = e;
    }


    // LatencyBudgetQosPolicy
    //

    inline
    LatencyBudgetQosPolicy::
    LatencyBudgetQosPolicy (::iccm::dds::Duration_t const& duration__)
    :
    duration_ (new ::iccm::dds::Duration_t (duration__)),
    regulator__ ()
    {
      duration_->container (this);
    }

    inline
    LatencyBudgetQosPolicy::
    LatencyBudgetQosPolicy (LatencyBudgetQosPolicy const& s)
    :
    ::XSCRT::Type (),
    duration_ (new ::iccm::dds::Duration_t (*s.duration_)),
    regulator__ ()
    {
      duration_->container (this);
    }

    inline
    LatencyBudgetQosPolicy& LatencyBudgetQosPolicy::
    operator= (LatencyBudgetQosPolicy const& s)
    {
      duration (*s.duration_);

      return *this;
    }


    // LatencyBudgetQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& LatencyBudgetQosPolicy::
    duration () const
    {
      return *duration_;
    }

    inline
    void LatencyBudgetQosPolicy::
    duration (::iccm::dds::Duration_t const& e)
    {
      *duration_ = e;
    }


    // OwnershipQosPolicyKind
    //

    inline
    OwnershipQosPolicyKind::Value OwnershipQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::OwnershipQosPolicyKind const& a, ::iccm::dds::OwnershipQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::OwnershipQosPolicyKind const& a, ::iccm::dds::OwnershipQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    OwnershipQosPolicyKind::
    OwnershipQosPolicyKind (OwnershipQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // OwnershipQosPolicy
    //

    inline
    OwnershipQosPolicy::
    OwnershipQosPolicy (::iccm::dds::OwnershipQosPolicyKind const& kind__)
    :
    kind_ (new ::iccm::dds::OwnershipQosPolicyKind (kind__)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    OwnershipQosPolicy::
    OwnershipQosPolicy (OwnershipQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::OwnershipQosPolicyKind (*s.kind_)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    OwnershipQosPolicy& OwnershipQosPolicy::
    operator= (OwnershipQosPolicy const& s)
    {
      kind (*s.kind_);

      return *this;
    }


    // OwnershipQosPolicy
    //
    inline
    ::iccm::dds::OwnershipQosPolicyKind const& OwnershipQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void OwnershipQosPolicy::
    kind (::iccm::dds::OwnershipQosPolicyKind const& e)
    {
      *kind_ = e;
    }


    // OwnershipStrengthQosPolicy
    //

    inline
    OwnershipStrengthQosPolicy::
    OwnershipStrengthQosPolicy (::XMLSchema::long_ const& value__)
    :
    value_ (new ::XMLSchema::long_ (value__)),
    regulator__ ()
    {
      value_->container (this);
    }

    inline
    OwnershipStrengthQosPolicy::
    OwnershipStrengthQosPolicy (OwnershipStrengthQosPolicy const& s)
    :
    ::XSCRT::Type (),
    value_ (new ::XMLSchema::long_ (*s.value_)),
    regulator__ ()
    {
      value_->container (this);
    }

    inline
    OwnershipStrengthQosPolicy& OwnershipStrengthQosPolicy::
    operator= (OwnershipStrengthQosPolicy const& s)
    {
      value (*s.value_);

      return *this;
    }


    // OwnershipStrengthQosPolicy
    //
    inline
    ::XMLSchema::long_ const& OwnershipStrengthQosPolicy::
    value () const
    {
      return *value_;
    }

    inline
    void OwnershipStrengthQosPolicy::
    value (::XMLSchema::long_ const& e)
    {
      *value_ = e;
    }


    // LivelinessQosPolicyKind
    //

    inline
    LivelinessQosPolicyKind::Value LivelinessQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::LivelinessQosPolicyKind const& a, ::iccm::dds::LivelinessQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::LivelinessQosPolicyKind const& a, ::iccm::dds::LivelinessQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    LivelinessQosPolicyKind::
    LivelinessQosPolicyKind (LivelinessQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // LivelinessQosPolicy
    //

    inline
    LivelinessQosPolicy::
    LivelinessQosPolicy (::iccm::dds::LivelinessQosPolicyKind const& kind__,
                         ::iccm::dds::Duration_t const& lease_duration__)
    :
    kind_ (new ::iccm::dds::LivelinessQosPolicyKind (kind__)),
    lease_duration_ (new ::iccm::dds::Duration_t (lease_duration__)),
    regulator__ ()
    {
      kind_->container (this);
      lease_duration_->container (this);
    }

    inline
    LivelinessQosPolicy::
    LivelinessQosPolicy (LivelinessQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::LivelinessQosPolicyKind (*s.kind_)),
    lease_duration_ (new ::iccm::dds::Duration_t (*s.lease_duration_)),
    regulator__ ()
    {
      kind_->container (this);
      lease_duration_->container (this);
    }

    inline
    LivelinessQosPolicy& LivelinessQosPolicy::
    operator= (LivelinessQosPolicy const& s)
    {
      kind (*s.kind_);

      lease_duration (*s.lease_duration_);

      return *this;
    }


    // LivelinessQosPolicy
    //
    inline
    ::iccm::dds::LivelinessQosPolicyKind const& LivelinessQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void LivelinessQosPolicy::
    kind (::iccm::dds::LivelinessQosPolicyKind const& e)
    {
      *kind_ = e;
    }

    // LivelinessQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& LivelinessQosPolicy::
    lease_duration () const
    {
      return *lease_duration_;
    }

    inline
    void LivelinessQosPolicy::
    lease_duration (::iccm::dds::Duration_t const& e)
    {
      *lease_duration_ = e;
    }


    // TimeBasedFilterQosPolicy
    //

    inline
    TimeBasedFilterQosPolicy::
    TimeBasedFilterQosPolicy (::iccm::dds::Duration_t const& minimum_separation__)
    :
    minimum_separation_ (new ::iccm::dds::Duration_t (minimum_separation__)),
    regulator__ ()
    {
      minimum_separation_->container (this);
    }

    inline
    TimeBasedFilterQosPolicy::
    TimeBasedFilterQosPolicy (TimeBasedFilterQosPolicy const& s)
    :
    ::XSCRT::Type (),
    minimum_separation_ (new ::iccm::dds::Duration_t (*s.minimum_separation_)),
    regulator__ ()
    {
      minimum_separation_->container (this);
    }

    inline
    TimeBasedFilterQosPolicy& TimeBasedFilterQosPolicy::
    operator= (TimeBasedFilterQosPolicy const& s)
    {
      minimum_separation (*s.minimum_separation_);

      return *this;
    }


    // TimeBasedFilterQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& TimeBasedFilterQosPolicy::
    minimum_separation () const
    {
      return *minimum_separation_;
    }

    inline
    void TimeBasedFilterQosPolicy::
    minimum_separation (::iccm::dds::Duration_t const& e)
    {
      *minimum_separation_ = e;
    }


    // ReliabilityQosPolicyKind
    //

    inline
    ReliabilityQosPolicyKind::Value ReliabilityQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::ReliabilityQosPolicyKind const& a, ::iccm::dds::ReliabilityQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::ReliabilityQosPolicyKind const& a, ::iccm::dds::ReliabilityQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    ReliabilityQosPolicyKind::
    ReliabilityQosPolicyKind (ReliabilityQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // ReliabilityQosPolicy
    //

    inline
    ReliabilityQosPolicy::
    ReliabilityQosPolicy (::iccm::dds::ReliabilityQosPolicyKind const& kind__,
                          ::iccm::dds::Duration_t const& max_blocking_time__)
    :
    kind_ (new ::iccm::dds::ReliabilityQosPolicyKind (kind__)),
    max_blocking_time_ (new ::iccm::dds::Duration_t (max_blocking_time__)),
    regulator__ ()
    {
      kind_->container (this);
      max_blocking_time_->container (this);
    }

    inline
    ReliabilityQosPolicy::
    ReliabilityQosPolicy (ReliabilityQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::ReliabilityQosPolicyKind (*s.kind_)),
    max_blocking_time_ (new ::iccm::dds::Duration_t (*s.max_blocking_time_)),
    regulator__ ()
    {
      kind_->container (this);
      max_blocking_time_->container (this);
    }

    inline
    ReliabilityQosPolicy& ReliabilityQosPolicy::
    operator= (ReliabilityQosPolicy const& s)
    {
      kind (*s.kind_);

      max_blocking_time (*s.max_blocking_time_);

      return *this;
    }


    // ReliabilityQosPolicy
    //
    inline
    ::iccm::dds::ReliabilityQosPolicyKind const& ReliabilityQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void ReliabilityQosPolicy::
    kind (::iccm::dds::ReliabilityQosPolicyKind const& e)
    {
      *kind_ = e;
    }

    // ReliabilityQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& ReliabilityQosPolicy::
    max_blocking_time () const
    {
      return *max_blocking_time_;
    }

    inline
    void ReliabilityQosPolicy::
    max_blocking_time (::iccm::dds::Duration_t const& e)
    {
      *max_blocking_time_ = e;
    }


    // DestinationOrderQosPolicyKind
    //

    inline
    DestinationOrderQosPolicyKind::Value DestinationOrderQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::DestinationOrderQosPolicyKind const& a, ::iccm::dds::DestinationOrderQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::DestinationOrderQosPolicyKind const& a, ::iccm::dds::DestinationOrderQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    DestinationOrderQosPolicyKind::
    DestinationOrderQosPolicyKind (DestinationOrderQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // DestinationOrderQosPolicy
    //

    inline
    DestinationOrderQosPolicy::
    DestinationOrderQosPolicy (::iccm::dds::DestinationOrderQosPolicyKind const& kind__)
    :
    kind_ (new ::iccm::dds::DestinationOrderQosPolicyKind (kind__)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    DestinationOrderQosPolicy::
    DestinationOrderQosPolicy (DestinationOrderQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::DestinationOrderQosPolicyKind (*s.kind_)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    DestinationOrderQosPolicy& DestinationOrderQosPolicy::
    operator= (DestinationOrderQosPolicy const& s)
    {
      kind (*s.kind_);

      return *this;
    }


    // DestinationOrderQosPolicy
    //
    inline
    ::iccm::dds::DestinationOrderQosPolicyKind const& DestinationOrderQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void DestinationOrderQosPolicy::
    kind (::iccm::dds::DestinationOrderQosPolicyKind const& e)
    {
      *kind_ = e;
    }


    // HistoryQosPolicyKind
    //

    inline
    HistoryQosPolicyKind::Value HistoryQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::HistoryQosPolicyKind const& a, ::iccm::dds::HistoryQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::HistoryQosPolicyKind const& a, ::iccm::dds::HistoryQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    HistoryQosPolicyKind::
    HistoryQosPolicyKind (HistoryQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // HistoryQosPolicy
    //

    inline
    HistoryQosPolicy::
    HistoryQosPolicy (::iccm::dds::HistoryQosPolicyKind const& kind__,
                      ::XMLSchema::long_ const& depth__)
    :
    kind_ (new ::iccm::dds::HistoryQosPolicyKind (kind__)),
    depth_ (new ::XMLSchema::long_ (depth__)),
    regulator__ ()
    {
      kind_->container (this);
      depth_->container (this);
    }

    inline
    HistoryQosPolicy::
    HistoryQosPolicy (HistoryQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::HistoryQosPolicyKind (*s.kind_)),
    depth_ (new ::XMLSchema::long_ (*s.depth_)),
    regulator__ ()
    {
      kind_->container (this);
      depth_->container (this);
    }

    inline
    HistoryQosPolicy& HistoryQosPolicy::
    operator= (HistoryQosPolicy const& s)
    {
      kind (*s.kind_);

      depth (*s.depth_);

      return *this;
    }


    // HistoryQosPolicy
    //
    inline
    ::iccm::dds::HistoryQosPolicyKind const& HistoryQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void HistoryQosPolicy::
    kind (::iccm::dds::HistoryQosPolicyKind const& e)
    {
      *kind_ = e;
    }

    // HistoryQosPolicy
    //
    inline
    ::XMLSchema::long_ const& HistoryQosPolicy::
    depth () const
    {
      return *depth_;
    }

    inline
    void HistoryQosPolicy::
    depth (::XMLSchema::long_ const& e)
    {
      *depth_ = e;
    }


    // ResourceLimitsQosPolicy
    //

    inline
    ResourceLimitsQosPolicy::
    ResourceLimitsQosPolicy (::XMLSchema::long_ const& max_samples__,
                             ::XMLSchema::long_ const& max_instances__,
                             ::XMLSchema::long_ const& max_samples_per_instance__)
    :
    max_samples_ (new ::XMLSchema::long_ (max_samples__)),
    max_instances_ (new ::XMLSchema::long_ (max_instances__)),
    max_samples_per_instance_ (new ::XMLSchema::long_ (max_samples_per_instance__)),
    regulator__ ()
    {
      max_samples_->container (this);
      max_instances_->container (this);
      max_samples_per_instance_->container (this);
    }

    inline
    ResourceLimitsQosPolicy::
    ResourceLimitsQosPolicy (ResourceLimitsQosPolicy const& s)
    :
    ::XSCRT::Type (),
    max_samples_ (new ::XMLSchema::long_ (*s.max_samples_)),
    max_instances_ (new ::XMLSchema::long_ (*s.max_instances_)),
    max_samples_per_instance_ (new ::XMLSchema::long_ (*s.max_samples_per_instance_)),
    regulator__ ()
    {
      max_samples_->container (this);
      max_instances_->container (this);
      max_samples_per_instance_->container (this);
    }

    inline
    ResourceLimitsQosPolicy& ResourceLimitsQosPolicy::
    operator= (ResourceLimitsQosPolicy const& s)
    {
      max_samples (*s.max_samples_);

      max_instances (*s.max_instances_);

      max_samples_per_instance (*s.max_samples_per_instance_);

      return *this;
    }


    // ResourceLimitsQosPolicy
    //
    inline
    ::XMLSchema::long_ const& ResourceLimitsQosPolicy::
    max_samples () const
    {
      return *max_samples_;
    }

    inline
    void ResourceLimitsQosPolicy::
    max_samples (::XMLSchema::long_ const& e)
    {
      *max_samples_ = e;
    }

    // ResourceLimitsQosPolicy
    //
    inline
    ::XMLSchema::long_ const& ResourceLimitsQosPolicy::
    max_instances () const
    {
      return *max_instances_;
    }

    inline
    void ResourceLimitsQosPolicy::
    max_instances (::XMLSchema::long_ const& e)
    {
      *max_instances_ = e;
    }

    // ResourceLimitsQosPolicy
    //
    inline
    ::XMLSchema::long_ const& ResourceLimitsQosPolicy::
    max_samples_per_instance () const
    {
      return *max_samples_per_instance_;
    }

    inline
    void ResourceLimitsQosPolicy::
    max_samples_per_instance (::XMLSchema::long_ const& e)
    {
      *max_samples_per_instance_ = e;
    }


    // EntityFactoryQosPolicy
    //

    inline
    EntityFactoryQosPolicy::
    EntityFactoryQosPolicy (::XMLSchema::boolean const& autoenable_created_entities__)
    :
    autoenable_created_entities_ (new ::XMLSchema::boolean (autoenable_created_entities__)),
    regulator__ ()
    {
      autoenable_created_entities_->container (this);
    }

    inline
    EntityFactoryQosPolicy::
    EntityFactoryQosPolicy (EntityFactoryQosPolicy const& s)
    :
    ::XSCRT::Type (),
    autoenable_created_entities_ (new ::XMLSchema::boolean (*s.autoenable_created_entities_)),
    regulator__ ()
    {
      autoenable_created_entities_->container (this);
    }

    inline
    EntityFactoryQosPolicy& EntityFactoryQosPolicy::
    operator= (EntityFactoryQosPolicy const& s)
    {
      autoenable_created_entities (*s.autoenable_created_entities_);

      return *this;
    }


    // EntityFactoryQosPolicy
    //
    inline
    ::XMLSchema::boolean const& EntityFactoryQosPolicy::
    autoenable_created_entities () const
    {
      return *autoenable_created_entities_;
    }

    inline
    void EntityFactoryQosPolicy::
    autoenable_created_entities (::XMLSchema::boolean const& e)
    {
      *autoenable_created_entities_ = e;
    }


    // WriterDataLifecycleQosPolicy
    //

    inline
    WriterDataLifecycleQosPolicy::
    WriterDataLifecycleQosPolicy (::XMLSchema::boolean const& autoenable_created_entities__)
    :
    autoenable_created_entities_ (new ::XMLSchema::boolean (autoenable_created_entities__)),
    regulator__ ()
    {
      autoenable_created_entities_->container (this);
    }

    inline
    WriterDataLifecycleQosPolicy::
    WriterDataLifecycleQosPolicy (WriterDataLifecycleQosPolicy const& s)
    :
    ::XSCRT::Type (),
    autoenable_created_entities_ (new ::XMLSchema::boolean (*s.autoenable_created_entities_)),
    regulator__ ()
    {
      autoenable_created_entities_->container (this);
    }

    inline
    WriterDataLifecycleQosPolicy& WriterDataLifecycleQosPolicy::
    operator= (WriterDataLifecycleQosPolicy const& s)
    {
      autoenable_created_entities (*s.autoenable_created_entities_);

      return *this;
    }


    // WriterDataLifecycleQosPolicy
    //
    inline
    ::XMLSchema::boolean const& WriterDataLifecycleQosPolicy::
    autoenable_created_entities () const
    {
      return *autoenable_created_entities_;
    }

    inline
    void WriterDataLifecycleQosPolicy::
    autoenable_created_entities (::XMLSchema::boolean const& e)
    {
      *autoenable_created_entities_ = e;
    }


    // ReaderDataLifecycleQosPolicy
    //

    inline
    ReaderDataLifecycleQosPolicy::
    ReaderDataLifecycleQosPolicy (::iccm::dds::Duration_t const& autopurge_nowriter_samples_delay__,
                                  ::iccm::dds::Duration_t const& autopurge_disposed_samples_delay__)
    :
    autopurge_nowriter_samples_delay_ (new ::iccm::dds::Duration_t (autopurge_nowriter_samples_delay__)),
    autopurge_disposed_samples_delay_ (new ::iccm::dds::Duration_t (autopurge_disposed_samples_delay__)),
    regulator__ ()
    {
      autopurge_nowriter_samples_delay_->container (this);
      autopurge_disposed_samples_delay_->container (this);
    }

    inline
    ReaderDataLifecycleQosPolicy::
    ReaderDataLifecycleQosPolicy (ReaderDataLifecycleQosPolicy const& s)
    :
    ::XSCRT::Type (),
    autopurge_nowriter_samples_delay_ (new ::iccm::dds::Duration_t (*s.autopurge_nowriter_samples_delay_)),
    autopurge_disposed_samples_delay_ (new ::iccm::dds::Duration_t (*s.autopurge_disposed_samples_delay_)),
    regulator__ ()
    {
      autopurge_nowriter_samples_delay_->container (this);
      autopurge_disposed_samples_delay_->container (this);
    }

    inline
    ReaderDataLifecycleQosPolicy& ReaderDataLifecycleQosPolicy::
    operator= (ReaderDataLifecycleQosPolicy const& s)
    {
      autopurge_nowriter_samples_delay (*s.autopurge_nowriter_samples_delay_);

      autopurge_disposed_samples_delay (*s.autopurge_disposed_samples_delay_);

      return *this;
    }


    // ReaderDataLifecycleQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& ReaderDataLifecycleQosPolicy::
    autopurge_nowriter_samples_delay () const
    {
      return *autopurge_nowriter_samples_delay_;
    }

    inline
    void ReaderDataLifecycleQosPolicy::
    autopurge_nowriter_samples_delay (::iccm::dds::Duration_t const& e)
    {
      *autopurge_nowriter_samples_delay_ = e;
    }

    // ReaderDataLifecycleQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& ReaderDataLifecycleQosPolicy::
    autopurge_disposed_samples_delay () const
    {
      return *autopurge_disposed_samples_delay_;
    }

    inline
    void ReaderDataLifecycleQosPolicy::
    autopurge_disposed_samples_delay (::iccm::dds::Duration_t const& e)
    {
      *autopurge_disposed_samples_delay_ = e;
    }


    // DurabilityServiceQosPolicy
    //

    inline
    DurabilityServiceQosPolicy::
    DurabilityServiceQosPolicy (::iccm::dds::Duration_t const& service_cleanup_delay__,
                                ::iccm::dds::HistoryQosPolicyKind const& history_kind__,
                                ::XMLSchema::long_ const& history_depth__,
                                ::XMLSchema::long_ const& max_samples__,
                                ::XMLSchema::long_ const& max_instances__,
                                ::XMLSchema::long_ const& max_samples_per_instance__)
    :
    service_cleanup_delay_ (new ::iccm::dds::Duration_t (service_cleanup_delay__)),
    history_kind_ (new ::iccm::dds::HistoryQosPolicyKind (history_kind__)),
    history_depth_ (new ::XMLSchema::long_ (history_depth__)),
    max_samples_ (new ::XMLSchema::long_ (max_samples__)),
    max_instances_ (new ::XMLSchema::long_ (max_instances__)),
    max_samples_per_instance_ (new ::XMLSchema::long_ (max_samples_per_instance__)),
    regulator__ ()
    {
      service_cleanup_delay_->container (this);
      history_kind_->container (this);
      history_depth_->container (this);
      max_samples_->container (this);
      max_instances_->container (this);
      max_samples_per_instance_->container (this);
    }

    inline
    DurabilityServiceQosPolicy::
    DurabilityServiceQosPolicy (DurabilityServiceQosPolicy const& s)
    :
    ::XSCRT::Type (),
    service_cleanup_delay_ (new ::iccm::dds::Duration_t (*s.service_cleanup_delay_)),
    history_kind_ (new ::iccm::dds::HistoryQosPolicyKind (*s.history_kind_)),
    history_depth_ (new ::XMLSchema::long_ (*s.history_depth_)),
    max_samples_ (new ::XMLSchema::long_ (*s.max_samples_)),
    max_instances_ (new ::XMLSchema::long_ (*s.max_instances_)),
    max_samples_per_instance_ (new ::XMLSchema::long_ (*s.max_samples_per_instance_)),
    regulator__ ()
    {
      service_cleanup_delay_->container (this);
      history_kind_->container (this);
      history_depth_->container (this);
      max_samples_->container (this);
      max_instances_->container (this);
      max_samples_per_instance_->container (this);
    }

    inline
    DurabilityServiceQosPolicy& DurabilityServiceQosPolicy::
    operator= (DurabilityServiceQosPolicy const& s)
    {
      service_cleanup_delay (*s.service_cleanup_delay_);

      history_kind (*s.history_kind_);

      history_depth (*s.history_depth_);

      max_samples (*s.max_samples_);

      max_instances (*s.max_instances_);

      max_samples_per_instance (*s.max_samples_per_instance_);

      return *this;
    }


    // DurabilityServiceQosPolicy
    //
    inline
    ::iccm::dds::Duration_t const& DurabilityServiceQosPolicy::
    service_cleanup_delay () const
    {
      return *service_cleanup_delay_;
    }

    inline
    void DurabilityServiceQosPolicy::
    service_cleanup_delay (::iccm::dds::Duration_t const& e)
    {
      *service_cleanup_delay_ = e;
    }

    // DurabilityServiceQosPolicy
    //
    inline
    ::iccm::dds::HistoryQosPolicyKind const& DurabilityServiceQosPolicy::
    history_kind () const
    {
      return *history_kind_;
    }

    inline
    void DurabilityServiceQosPolicy::
    history_kind (::iccm::dds::HistoryQosPolicyKind const& e)
    {
      *history_kind_ = e;
    }

    // DurabilityServiceQosPolicy
    //
    inline
    ::XMLSchema::long_ const& DurabilityServiceQosPolicy::
    history_depth () const
    {
      return *history_depth_;
    }

    inline
    void DurabilityServiceQosPolicy::
    history_depth (::XMLSchema::long_ const& e)
    {
      *history_depth_ = e;
    }

    // DurabilityServiceQosPolicy
    //
    inline
    ::XMLSchema::long_ const& DurabilityServiceQosPolicy::
    max_samples () const
    {
      return *max_samples_;
    }

    inline
    void DurabilityServiceQosPolicy::
    max_samples (::XMLSchema::long_ const& e)
    {
      *max_samples_ = e;
    }

    // DurabilityServiceQosPolicy
    //
    inline
    ::XMLSchema::long_ const& DurabilityServiceQosPolicy::
    max_instances () const
    {
      return *max_instances_;
    }

    inline
    void DurabilityServiceQosPolicy::
    max_instances (::XMLSchema::long_ const& e)
    {
      *max_instances_ = e;
    }

    // DurabilityServiceQosPolicy
    //
    inline
    ::XMLSchema::long_ const& DurabilityServiceQosPolicy::
    max_samples_per_instance () const
    {
      return *max_samples_per_instance_;
    }

    inline
    void DurabilityServiceQosPolicy::
    max_samples_per_instance (::XMLSchema::long_ const& e)
    {
      *max_samples_per_instance_ = e;
    }


    // SchedulingClassQosPolicyKind
    //

    inline
    SchedulingClassQosPolicyKind::Value SchedulingClassQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::SchedulingClassQosPolicyKind const& a, ::iccm::dds::SchedulingClassQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::SchedulingClassQosPolicyKind const& a, ::iccm::dds::SchedulingClassQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    SchedulingClassQosPolicyKind::
    SchedulingClassQosPolicyKind (SchedulingClassQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // SchedulingClassQosPolicy
    //

    inline
    SchedulingClassQosPolicy::
    SchedulingClassQosPolicy (::iccm::dds::SchedulingClassQosPolicyKind const& kind__)
    :
    kind_ (new ::iccm::dds::SchedulingClassQosPolicyKind (kind__)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    SchedulingClassQosPolicy::
    SchedulingClassQosPolicy (SchedulingClassQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::SchedulingClassQosPolicyKind (*s.kind_)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    SchedulingClassQosPolicy& SchedulingClassQosPolicy::
    operator= (SchedulingClassQosPolicy const& s)
    {
      kind (*s.kind_);

      return *this;
    }


    // SchedulingClassQosPolicy
    //
    inline
    ::iccm::dds::SchedulingClassQosPolicyKind const& SchedulingClassQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void SchedulingClassQosPolicy::
    kind (::iccm::dds::SchedulingClassQosPolicyKind const& e)
    {
      *kind_ = e;
    }


    // SchedulingPriorityQosPolicyKind
    //

    inline
    SchedulingPriorityQosPolicyKind::Value SchedulingPriorityQosPolicyKind::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::iccm::dds::SchedulingPriorityQosPolicyKind const& a, ::iccm::dds::SchedulingPriorityQosPolicyKind const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::iccm::dds::SchedulingPriorityQosPolicyKind const& a, ::iccm::dds::SchedulingPriorityQosPolicyKind const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    SchedulingPriorityQosPolicyKind::
    SchedulingPriorityQosPolicyKind (SchedulingPriorityQosPolicyKind::Value v)
    : v_ (v)
    {
    }

    // SchedulingPriorityQosPolicy
    //

    inline
    SchedulingPriorityQosPolicy::
    SchedulingPriorityQosPolicy (::iccm::dds::SchedulingPriorityQosPolicyKind const& kind__)
    :
    kind_ (new ::iccm::dds::SchedulingPriorityQosPolicyKind (kind__)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    SchedulingPriorityQosPolicy::
    SchedulingPriorityQosPolicy (SchedulingPriorityQosPolicy const& s)
    :
    ::XSCRT::Type (),
    kind_ (new ::iccm::dds::SchedulingPriorityQosPolicyKind (*s.kind_)),
    regulator__ ()
    {
      kind_->container (this);
    }

    inline
    SchedulingPriorityQosPolicy& SchedulingPriorityQosPolicy::
    operator= (SchedulingPriorityQosPolicy const& s)
    {
      kind (*s.kind_);

      return *this;
    }


    // SchedulingPriorityQosPolicy
    //
    inline
    ::iccm::dds::SchedulingPriorityQosPolicyKind const& SchedulingPriorityQosPolicy::
    kind () const
    {
      return *kind_;
    }

    inline
    void SchedulingPriorityQosPolicy::
    kind (::iccm::dds::SchedulingPriorityQosPolicyKind const& e)
    {
      *kind_ = e;
    }


    // SchedulingQosPolicy
    //

    inline
    SchedulingQosPolicy::
    SchedulingQosPolicy (::iccm::dds::SchedulingClassQosPolicy const& scheduling_class__,
                         ::iccm::dds::SchedulingPriorityQosPolicy const& scheduling_priority_kind__,
                         ::XMLSchema::long_ const& scheduling_priority__)
    :
    scheduling_class_ (new ::iccm::dds::SchedulingClassQosPolicy (scheduling_class__)),
    scheduling_priority_kind_ (new ::iccm::dds::SchedulingPriorityQosPolicy (scheduling_priority_kind__)),
    scheduling_priority_ (new ::XMLSchema::long_ (scheduling_priority__)),
    regulator__ ()
    {
      scheduling_class_->container (this);
      scheduling_priority_kind_->container (this);
      scheduling_priority_->container (this);
    }

    inline
    SchedulingQosPolicy::
    SchedulingQosPolicy (SchedulingQosPolicy const& s)
    :
    ::XSCRT::Type (),
    scheduling_class_ (new ::iccm::dds::SchedulingClassQosPolicy (*s.scheduling_class_)),
    scheduling_priority_kind_ (new ::iccm::dds::SchedulingPriorityQosPolicy (*s.scheduling_priority_kind_)),
    scheduling_priority_ (new ::XMLSchema::long_ (*s.scheduling_priority_)),
    regulator__ ()
    {
      scheduling_class_->container (this);
      scheduling_priority_kind_->container (this);
      scheduling_priority_->container (this);
    }

    inline
    SchedulingQosPolicy& SchedulingQosPolicy::
    operator= (SchedulingQosPolicy const& s)
    {
      scheduling_class (*s.scheduling_class_);

      scheduling_priority_kind (*s.scheduling_priority_kind_);

      scheduling_priority (*s.scheduling_priority_);

      return *this;
    }


    // SchedulingQosPolicy
    //
    inline
    ::iccm::dds::SchedulingClassQosPolicy const& SchedulingQosPolicy::
    scheduling_class () const
    {
      return *scheduling_class_;
    }

    inline
    void SchedulingQosPolicy::
    scheduling_class (::iccm::dds::SchedulingClassQosPolicy const& e)
    {
      *scheduling_class_ = e;
    }

    // SchedulingQosPolicy
    //
    inline
    ::iccm::dds::SchedulingPriorityQosPolicy const& SchedulingQosPolicy::
    scheduling_priority_kind () const
    {
      return *scheduling_priority_kind_;
    }

    inline
    void SchedulingQosPolicy::
    scheduling_priority_kind (::iccm::dds::SchedulingPriorityQosPolicy const& e)
    {
      *scheduling_priority_kind_ = e;
    }

    // SchedulingQosPolicy
    //
    inline
    ::XMLSchema::long_ const& SchedulingQosPolicy::
    scheduling_priority () const
    {
      return *scheduling_priority_;
    }

    inline
    void SchedulingQosPolicy::
    scheduling_priority (::XMLSchema::long_ const& e)
    {
      *scheduling_priority_ = e;
    }


    // DomainParticipantFactoryQos
    //

    inline
    DomainParticipantFactoryQos::
    DomainParticipantFactoryQos (::iccm::dds::EntityFactoryQosPolicy const& entity_factory__)
    :
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (entity_factory__)),
    regulator__ ()
    {
      entity_factory_->container (this);
    }

    inline
    DomainParticipantFactoryQos::
    DomainParticipantFactoryQos (DomainParticipantFactoryQos const& s)
    :
    ::XSCRT::Type (),
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (*s.entity_factory_)),
    regulator__ ()
    {
      entity_factory_->container (this);
    }

    inline
    DomainParticipantFactoryQos& DomainParticipantFactoryQos::
    operator= (DomainParticipantFactoryQos const& s)
    {
      entity_factory (*s.entity_factory_);

      return *this;
    }


    // DomainParticipantFactoryQos
    //
    inline
    ::iccm::dds::EntityFactoryQosPolicy const& DomainParticipantFactoryQos::
    entity_factory () const
    {
      return *entity_factory_;
    }

    inline
    void DomainParticipantFactoryQos::
    entity_factory (::iccm::dds::EntityFactoryQosPolicy const& e)
    {
      *entity_factory_ = e;
    }


    // DataReaderQos
    //

    inline
    DataReaderQos::
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
                   ::XMLSchema::string< char > const& name__)
    :
    durability_ (new ::iccm::dds::DurabilityQosPolicy (durability__)),
    deadline_ (new ::iccm::dds::DeadlineQosPolicy (deadline__)),
    latency_budget_ (new ::iccm::dds::LatencyBudgetQosPolicy (latency_budget__)),
    liveliness_ (new ::iccm::dds::LivelinessQosPolicy (liveliness__)),
    reliability_ (new ::iccm::dds::ReliabilityQosPolicy (reliability__)),
    destination_order_ (new ::iccm::dds::DestinationOrderQosPolicy (destination_order__)),
    history_ (new ::iccm::dds::HistoryQosPolicy (history__)),
    resource_limits_ (new ::iccm::dds::ResourceLimitsQosPolicy (resource_limits__)),
    ownership_ (new ::iccm::dds::OwnershipQosPolicy (ownership__)),
    time_based_filter_ (new ::iccm::dds::TimeBasedFilterQosPolicy (time_based_filter__)),
    reader_data_lifecycle_ (new ::iccm::dds::ReaderDataLifecycleQosPolicy (reader_data_lifecycle__)),
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      durability_->container (this);
      deadline_->container (this);
      latency_budget_->container (this);
      liveliness_->container (this);
      reliability_->container (this);
      destination_order_->container (this);
      history_->container (this);
      resource_limits_->container (this);
      ownership_->container (this);
      time_based_filter_->container (this);
      reader_data_lifecycle_->container (this);
      name_->container (this);
    }

    inline
    DataReaderQos::
    DataReaderQos (DataReaderQos const& s)
    :
    ::XSCRT::Type (),
    durability_ (new ::iccm::dds::DurabilityQosPolicy (*s.durability_)),
    deadline_ (new ::iccm::dds::DeadlineQosPolicy (*s.deadline_)),
    latency_budget_ (new ::iccm::dds::LatencyBudgetQosPolicy (*s.latency_budget_)),
    liveliness_ (new ::iccm::dds::LivelinessQosPolicy (*s.liveliness_)),
    reliability_ (new ::iccm::dds::ReliabilityQosPolicy (*s.reliability_)),
    destination_order_ (new ::iccm::dds::DestinationOrderQosPolicy (*s.destination_order_)),
    history_ (new ::iccm::dds::HistoryQosPolicy (*s.history_)),
    resource_limits_ (new ::iccm::dds::ResourceLimitsQosPolicy (*s.resource_limits_)),
    ownership_ (new ::iccm::dds::OwnershipQosPolicy (*s.ownership_)),
    time_based_filter_ (new ::iccm::dds::TimeBasedFilterQosPolicy (*s.time_based_filter_)),
    reader_data_lifecycle_ (new ::iccm::dds::ReaderDataLifecycleQosPolicy (*s.reader_data_lifecycle_)),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      durability_->container (this);
      deadline_->container (this);
      latency_budget_->container (this);
      liveliness_->container (this);
      reliability_->container (this);
      destination_order_->container (this);
      history_->container (this);
      resource_limits_->container (this);
      ownership_->container (this);
      time_based_filter_->container (this);
      reader_data_lifecycle_->container (this);
      name_->container (this);
    }

    inline
    DataReaderQos& DataReaderQos::
    operator= (DataReaderQos const& s)
    {
      durability (*s.durability_);

      deadline (*s.deadline_);

      latency_budget (*s.latency_budget_);

      liveliness (*s.liveliness_);

      reliability (*s.reliability_);

      destination_order (*s.destination_order_);

      history (*s.history_);

      resource_limits (*s.resource_limits_);

      ownership (*s.ownership_);

      time_based_filter (*s.time_based_filter_);

      reader_data_lifecycle (*s.reader_data_lifecycle_);

      name (s.name ());

      return *this;
    }


    // DataReaderQos
    //
    inline
    ::iccm::dds::DurabilityQosPolicy const& DataReaderQos::
    durability () const
    {
      return *durability_;
    }

    inline
    void DataReaderQos::
    durability (::iccm::dds::DurabilityQosPolicy const& e)
    {
      *durability_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::DeadlineQosPolicy const& DataReaderQos::
    deadline () const
    {
      return *deadline_;
    }

    inline
    void DataReaderQos::
    deadline (::iccm::dds::DeadlineQosPolicy const& e)
    {
      *deadline_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::LatencyBudgetQosPolicy const& DataReaderQos::
    latency_budget () const
    {
      return *latency_budget_;
    }

    inline
    void DataReaderQos::
    latency_budget (::iccm::dds::LatencyBudgetQosPolicy const& e)
    {
      *latency_budget_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::LivelinessQosPolicy const& DataReaderQos::
    liveliness () const
    {
      return *liveliness_;
    }

    inline
    void DataReaderQos::
    liveliness (::iccm::dds::LivelinessQosPolicy const& e)
    {
      *liveliness_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::ReliabilityQosPolicy const& DataReaderQos::
    reliability () const
    {
      return *reliability_;
    }

    inline
    void DataReaderQos::
    reliability (::iccm::dds::ReliabilityQosPolicy const& e)
    {
      *reliability_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::DestinationOrderQosPolicy const& DataReaderQos::
    destination_order () const
    {
      return *destination_order_;
    }

    inline
    void DataReaderQos::
    destination_order (::iccm::dds::DestinationOrderQosPolicy const& e)
    {
      *destination_order_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::HistoryQosPolicy const& DataReaderQos::
    history () const
    {
      return *history_;
    }

    inline
    void DataReaderQos::
    history (::iccm::dds::HistoryQosPolicy const& e)
    {
      *history_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::ResourceLimitsQosPolicy const& DataReaderQos::
    resource_limits () const
    {
      return *resource_limits_;
    }

    inline
    void DataReaderQos::
    resource_limits (::iccm::dds::ResourceLimitsQosPolicy const& e)
    {
      *resource_limits_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::OwnershipQosPolicy const& DataReaderQos::
    ownership () const
    {
      return *ownership_;
    }

    inline
    void DataReaderQos::
    ownership (::iccm::dds::OwnershipQosPolicy const& e)
    {
      *ownership_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::TimeBasedFilterQosPolicy const& DataReaderQos::
    time_based_filter () const
    {
      return *time_based_filter_;
    }

    inline
    void DataReaderQos::
    time_based_filter (::iccm::dds::TimeBasedFilterQosPolicy const& e)
    {
      *time_based_filter_ = e;
    }

    // DataReaderQos
    //
    inline
    ::iccm::dds::ReaderDataLifecycleQosPolicy const& DataReaderQos::
    reader_data_lifecycle () const
    {
      return *reader_data_lifecycle_;
    }

    inline
    void DataReaderQos::
    reader_data_lifecycle (::iccm::dds::ReaderDataLifecycleQosPolicy const& e)
    {
      *reader_data_lifecycle_ = e;
    }

    // DataReaderQos
    //
    inline
    ::XMLSchema::string< char > const& DataReaderQos::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& DataReaderQos::
    name ()
    {
      return *name_;
    }

    inline
    void DataReaderQos::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // DataWriterQos
    //

    inline
    DataWriterQos::
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
                   ::XMLSchema::string< char > const& name__)
    :
    durability_ (new ::iccm::dds::DurabilityQosPolicy (durability__)),
    deadline_ (new ::iccm::dds::DeadlineQosPolicy (deadline__)),
    latency_budget_ (new ::iccm::dds::LatencyBudgetQosPolicy (latency_budget__)),
    liveliness_ (new ::iccm::dds::LivelinessQosPolicy (liveliness__)),
    reliability_ (new ::iccm::dds::ReliabilityQosPolicy (reliability__)),
    destination_order_ (new ::iccm::dds::DestinationOrderQosPolicy (destination_order__)),
    history_ (new ::iccm::dds::HistoryQosPolicy (history__)),
    resource_limits_ (new ::iccm::dds::ResourceLimitsQosPolicy (resource_limits__)),
    transport_priorty_ (new ::iccm::dds::TransportPriorityQosPolicy (transport_priorty__)),
    lifespan_ (new ::iccm::dds::LifespanQosPolicy (lifespan__)),
    ownership_ (new ::iccm::dds::OwnershipQosPolicy (ownership__)),
    ownership_strength_ (new ::iccm::dds::OwnershipStrengthQosPolicy (ownership_strength__)),
    writer_data_lifecycle_ (new ::iccm::dds::WriterDataLifecycleQosPolicy (writer_data_lifecycle__)),
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      durability_->container (this);
      deadline_->container (this);
      latency_budget_->container (this);
      liveliness_->container (this);
      reliability_->container (this);
      destination_order_->container (this);
      history_->container (this);
      resource_limits_->container (this);
      transport_priorty_->container (this);
      lifespan_->container (this);
      ownership_->container (this);
      ownership_strength_->container (this);
      writer_data_lifecycle_->container (this);
      name_->container (this);
    }

    inline
    DataWriterQos::
    DataWriterQos (DataWriterQos const& s)
    :
    ::XSCRT::Type (),
    durability_ (new ::iccm::dds::DurabilityQosPolicy (*s.durability_)),
    deadline_ (new ::iccm::dds::DeadlineQosPolicy (*s.deadline_)),
    latency_budget_ (new ::iccm::dds::LatencyBudgetQosPolicy (*s.latency_budget_)),
    liveliness_ (new ::iccm::dds::LivelinessQosPolicy (*s.liveliness_)),
    reliability_ (new ::iccm::dds::ReliabilityQosPolicy (*s.reliability_)),
    destination_order_ (new ::iccm::dds::DestinationOrderQosPolicy (*s.destination_order_)),
    history_ (new ::iccm::dds::HistoryQosPolicy (*s.history_)),
    resource_limits_ (new ::iccm::dds::ResourceLimitsQosPolicy (*s.resource_limits_)),
    transport_priorty_ (new ::iccm::dds::TransportPriorityQosPolicy (*s.transport_priorty_)),
    lifespan_ (new ::iccm::dds::LifespanQosPolicy (*s.lifespan_)),
    ownership_ (new ::iccm::dds::OwnershipQosPolicy (*s.ownership_)),
    ownership_strength_ (new ::iccm::dds::OwnershipStrengthQosPolicy (*s.ownership_strength_)),
    writer_data_lifecycle_ (new ::iccm::dds::WriterDataLifecycleQosPolicy (*s.writer_data_lifecycle_)),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      durability_->container (this);
      deadline_->container (this);
      latency_budget_->container (this);
      liveliness_->container (this);
      reliability_->container (this);
      destination_order_->container (this);
      history_->container (this);
      resource_limits_->container (this);
      transport_priorty_->container (this);
      lifespan_->container (this);
      ownership_->container (this);
      ownership_strength_->container (this);
      writer_data_lifecycle_->container (this);
      name_->container (this);
    }

    inline
    DataWriterQos& DataWriterQos::
    operator= (DataWriterQos const& s)
    {
      durability (*s.durability_);

      deadline (*s.deadline_);

      latency_budget (*s.latency_budget_);

      liveliness (*s.liveliness_);

      reliability (*s.reliability_);

      destination_order (*s.destination_order_);

      history (*s.history_);

      resource_limits (*s.resource_limits_);

      transport_priorty (*s.transport_priorty_);

      lifespan (*s.lifespan_);

      ownership (*s.ownership_);

      ownership_strength (*s.ownership_strength_);

      writer_data_lifecycle (*s.writer_data_lifecycle_);

      name (s.name ());

      return *this;
    }


    // DataWriterQos
    //
    inline
    ::iccm::dds::DurabilityQosPolicy const& DataWriterQos::
    durability () const
    {
      return *durability_;
    }

    inline
    void DataWriterQos::
    durability (::iccm::dds::DurabilityQosPolicy const& e)
    {
      *durability_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::DeadlineQosPolicy const& DataWriterQos::
    deadline () const
    {
      return *deadline_;
    }

    inline
    void DataWriterQos::
    deadline (::iccm::dds::DeadlineQosPolicy const& e)
    {
      *deadline_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::LatencyBudgetQosPolicy const& DataWriterQos::
    latency_budget () const
    {
      return *latency_budget_;
    }

    inline
    void DataWriterQos::
    latency_budget (::iccm::dds::LatencyBudgetQosPolicy const& e)
    {
      *latency_budget_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::LivelinessQosPolicy const& DataWriterQos::
    liveliness () const
    {
      return *liveliness_;
    }

    inline
    void DataWriterQos::
    liveliness (::iccm::dds::LivelinessQosPolicy const& e)
    {
      *liveliness_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::ReliabilityQosPolicy const& DataWriterQos::
    reliability () const
    {
      return *reliability_;
    }

    inline
    void DataWriterQos::
    reliability (::iccm::dds::ReliabilityQosPolicy const& e)
    {
      *reliability_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::DestinationOrderQosPolicy const& DataWriterQos::
    destination_order () const
    {
      return *destination_order_;
    }

    inline
    void DataWriterQos::
    destination_order (::iccm::dds::DestinationOrderQosPolicy const& e)
    {
      *destination_order_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::HistoryQosPolicy const& DataWriterQos::
    history () const
    {
      return *history_;
    }

    inline
    void DataWriterQos::
    history (::iccm::dds::HistoryQosPolicy const& e)
    {
      *history_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::ResourceLimitsQosPolicy const& DataWriterQos::
    resource_limits () const
    {
      return *resource_limits_;
    }

    inline
    void DataWriterQos::
    resource_limits (::iccm::dds::ResourceLimitsQosPolicy const& e)
    {
      *resource_limits_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::TransportPriorityQosPolicy const& DataWriterQos::
    transport_priorty () const
    {
      return *transport_priorty_;
    }

    inline
    void DataWriterQos::
    transport_priorty (::iccm::dds::TransportPriorityQosPolicy const& e)
    {
      *transport_priorty_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::LifespanQosPolicy const& DataWriterQos::
    lifespan () const
    {
      return *lifespan_;
    }

    inline
    void DataWriterQos::
    lifespan (::iccm::dds::LifespanQosPolicy const& e)
    {
      *lifespan_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::OwnershipQosPolicy const& DataWriterQos::
    ownership () const
    {
      return *ownership_;
    }

    inline
    void DataWriterQos::
    ownership (::iccm::dds::OwnershipQosPolicy const& e)
    {
      *ownership_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::OwnershipStrengthQosPolicy const& DataWriterQos::
    ownership_strength () const
    {
      return *ownership_strength_;
    }

    inline
    void DataWriterQos::
    ownership_strength (::iccm::dds::OwnershipStrengthQosPolicy const& e)
    {
      *ownership_strength_ = e;
    }

    // DataWriterQos
    //
    inline
    ::iccm::dds::WriterDataLifecycleQosPolicy const& DataWriterQos::
    writer_data_lifecycle () const
    {
      return *writer_data_lifecycle_;
    }

    inline
    void DataWriterQos::
    writer_data_lifecycle (::iccm::dds::WriterDataLifecycleQosPolicy const& e)
    {
      *writer_data_lifecycle_ = e;
    }

    // DataWriterQos
    //
    inline
    ::XMLSchema::string< char > const& DataWriterQos::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& DataWriterQos::
    name ()
    {
      return *name_;
    }

    inline
    void DataWriterQos::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // PublisherQos
    //

    inline
    PublisherQos::
    PublisherQos (::iccm::dds::PresentationQosPolicy const& presentation__,
                  ::iccm::dds::EntityFactoryQosPolicy const& entity_factory__,
                  ::XMLSchema::string< char > const& name__)
    :
    presentation_ (new ::iccm::dds::PresentationQosPolicy (presentation__)),
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (entity_factory__)),
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      presentation_->container (this);
      entity_factory_->container (this);
      name_->container (this);
    }

    inline
    PublisherQos::
    PublisherQos (PublisherQos const& s)
    :
    ::XSCRT::Type (),
    presentation_ (new ::iccm::dds::PresentationQosPolicy (*s.presentation_)),
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (*s.entity_factory_)),
    datawriter_ (s.datawriter_),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      presentation_->container (this);
      entity_factory_->container (this);
      name_->container (this);
    }

    inline
    PublisherQos& PublisherQos::
    operator= (PublisherQos const& s)
    {
      presentation (*s.presentation_);

      entity_factory (*s.entity_factory_);

      datawriter_ = s.datawriter_;

      name (s.name ());

      return *this;
    }


    // PublisherQos
    //
    inline
    ::iccm::dds::PresentationQosPolicy const& PublisherQos::
    presentation () const
    {
      return *presentation_;
    }

    inline
    void PublisherQos::
    presentation (::iccm::dds::PresentationQosPolicy const& e)
    {
      *presentation_ = e;
    }

    // PublisherQos
    //
    inline
    ::iccm::dds::EntityFactoryQosPolicy const& PublisherQos::
    entity_factory () const
    {
      return *entity_factory_;
    }

    inline
    void PublisherQos::
    entity_factory (::iccm::dds::EntityFactoryQosPolicy const& e)
    {
      *entity_factory_ = e;
    }

    // PublisherQos
    //
    inline
    PublisherQos::datawriter_iterator PublisherQos::
    begin_datawriter ()
    {
      return datawriter_.begin ();
    }

    inline
    PublisherQos::datawriter_iterator PublisherQos::
    end_datawriter ()
    {
      return datawriter_.end ();
    }

    inline
    PublisherQos::datawriter_const_iterator PublisherQos::
    begin_datawriter () const
    {
      return datawriter_.begin ();
    }

    inline
    PublisherQos::datawriter_const_iterator PublisherQos::
    end_datawriter () const
    {
      return datawriter_.end ();
    }

    inline
    void PublisherQos::
    add_datawriter (ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex >  const& e)
    {
      datawriter_.push_back (e);
    }

    inline
    size_t PublisherQos::
    count_datawriter(void) const
    {
      return datawriter_.size ();
    }

    // PublisherQos
    //
    inline
    ::XMLSchema::string< char > const& PublisherQos::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& PublisherQos::
    name ()
    {
      return *name_;
    }

    inline
    void PublisherQos::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // SubscriberQos
    //

    inline
    SubscriberQos::
    SubscriberQos (::iccm::dds::PresentationQosPolicy const& presentation__,
                   ::iccm::dds::EntityFactoryQosPolicy const& entity_factory__,
                   ::XMLSchema::string< char > const& name__)
    :
    presentation_ (new ::iccm::dds::PresentationQosPolicy (presentation__)),
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (entity_factory__)),
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      presentation_->container (this);
      entity_factory_->container (this);
      name_->container (this);
    }

    inline
    SubscriberQos::
    SubscriberQos (SubscriberQos const& s)
    :
    ::XSCRT::Type (),
    presentation_ (new ::iccm::dds::PresentationQosPolicy (*s.presentation_)),
    entity_factory_ (new ::iccm::dds::EntityFactoryQosPolicy (*s.entity_factory_)),
    datareader_ (s.datareader_),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      presentation_->container (this);
      entity_factory_->container (this);
      name_->container (this);
    }

    inline
    SubscriberQos& SubscriberQos::
    operator= (SubscriberQos const& s)
    {
      presentation (*s.presentation_);

      entity_factory (*s.entity_factory_);

      datareader_ = s.datareader_;

      name (s.name ());

      return *this;
    }


    // SubscriberQos
    //
    inline
    ::iccm::dds::PresentationQosPolicy const& SubscriberQos::
    presentation () const
    {
      return *presentation_;
    }

    inline
    void SubscriberQos::
    presentation (::iccm::dds::PresentationQosPolicy const& e)
    {
      *presentation_ = e;
    }

    // SubscriberQos
    //
    inline
    ::iccm::dds::EntityFactoryQosPolicy const& SubscriberQos::
    entity_factory () const
    {
      return *entity_factory_;
    }

    inline
    void SubscriberQos::
    entity_factory (::iccm::dds::EntityFactoryQosPolicy const& e)
    {
      *entity_factory_ = e;
    }

    // SubscriberQos
    //
    inline
    SubscriberQos::datareader_iterator SubscriberQos::
    begin_datareader ()
    {
      return datareader_.begin ();
    }

    inline
    SubscriberQos::datareader_iterator SubscriberQos::
    end_datareader ()
    {
      return datareader_.end ();
    }

    inline
    SubscriberQos::datareader_const_iterator SubscriberQos::
    begin_datareader () const
    {
      return datareader_.begin ();
    }

    inline
    SubscriberQos::datareader_const_iterator SubscriberQos::
    end_datareader () const
    {
      return datareader_.end ();
    }

    inline
    void SubscriberQos::
    add_datareader (ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex >  const& e)
    {
      datareader_.push_back (e);
    }

    inline
    size_t SubscriberQos::
    count_datareader(void) const
    {
      return datareader_.size ();
    }

    // SubscriberQos
    //
    inline
    ::XMLSchema::string< char > const& SubscriberQos::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& SubscriberQos::
    name ()
    {
      return *name_;
    }

    inline
    void SubscriberQos::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // DomainParticipantQos
    //

    inline
    DomainParticipantQos::
    DomainParticipantQos ()
    :
    regulator__ ()
    {
    }

    inline
    DomainParticipantQos::
    DomainParticipantQos (DomainParticipantQos const& s)
    :
    ::XSCRT::Type (),
    entity_factory_ (s.entity_factory_.get () ? new ::iccm::dds::EntityFactoryQosPolicy (*s.entity_factory_) : 0),
    watchdog_scheduling_ (s.watchdog_scheduling_.get () ? new ::iccm::dds::SchedulingQosPolicy (*s.watchdog_scheduling_) : 0),
    listener_scheduling_ (s.listener_scheduling_.get () ? new ::iccm::dds::SchedulingQosPolicy (*s.listener_scheduling_) : 0),
    datawriter_ (s.datawriter_),
    datareader_ (s.datareader_),
    publisher_ (s.publisher_),
    subscriber_ (s.subscriber_),
    regulator__ ()
    {
      if (entity_factory_.get ()) entity_factory_->container (this);
      if (watchdog_scheduling_.get ()) watchdog_scheduling_->container (this);
      if (listener_scheduling_.get ()) listener_scheduling_->container (this);
    }

    inline
    DomainParticipantQos& DomainParticipantQos::
    operator= (DomainParticipantQos const& s)
    {
      if (s.entity_factory_.get ())
        entity_factory (*(s.entity_factory_));
      else
        entity_factory_.reset (0);

      if (s.watchdog_scheduling_.get ())
        watchdog_scheduling (*(s.watchdog_scheduling_));
      else
        watchdog_scheduling_.reset (0);

      if (s.listener_scheduling_.get ())
        listener_scheduling (*(s.listener_scheduling_));
      else
        listener_scheduling_.reset (0);

      datawriter_ = s.datawriter_;

      datareader_ = s.datareader_;

      publisher_ = s.publisher_;

      subscriber_ = s.subscriber_;

      return *this;
    }


    // DomainParticipantQos
    //
    inline
    bool DomainParticipantQos::
    entity_factory_p () const
    {
      return entity_factory_.get () != 0;
    }

    inline
    ::iccm::dds::EntityFactoryQosPolicy const& DomainParticipantQos::
    entity_factory () const
    {
      return *entity_factory_;
    }

    inline
    void DomainParticipantQos::
    entity_factory (::iccm::dds::EntityFactoryQosPolicy const& e)
    {
      if (entity_factory_.get ())
      {
        *entity_factory_ = e;
      }

      else
      {
        entity_factory_ = ::std::auto_ptr< ::iccm::dds::EntityFactoryQosPolicy > (new ::iccm::dds::EntityFactoryQosPolicy (e));
        entity_factory_->container (this);
      }
    }

    // DomainParticipantQos
    //
    inline
    bool DomainParticipantQos::
    watchdog_scheduling_p () const
    {
      return watchdog_scheduling_.get () != 0;
    }

    inline
    ::iccm::dds::SchedulingQosPolicy const& DomainParticipantQos::
    watchdog_scheduling () const
    {
      return *watchdog_scheduling_;
    }

    inline
    void DomainParticipantQos::
    watchdog_scheduling (::iccm::dds::SchedulingQosPolicy const& e)
    {
      if (watchdog_scheduling_.get ())
      {
        *watchdog_scheduling_ = e;
      }

      else
      {
        watchdog_scheduling_ = ::std::auto_ptr< ::iccm::dds::SchedulingQosPolicy > (new ::iccm::dds::SchedulingQosPolicy (e));
        watchdog_scheduling_->container (this);
      }
    }

    // DomainParticipantQos
    //
    inline
    bool DomainParticipantQos::
    listener_scheduling_p () const
    {
      return listener_scheduling_.get () != 0;
    }

    inline
    ::iccm::dds::SchedulingQosPolicy const& DomainParticipantQos::
    listener_scheduling () const
    {
      return *listener_scheduling_;
    }

    inline
    void DomainParticipantQos::
    listener_scheduling (::iccm::dds::SchedulingQosPolicy const& e)
    {
      if (listener_scheduling_.get ())
      {
        *listener_scheduling_ = e;
      }

      else
      {
        listener_scheduling_ = ::std::auto_ptr< ::iccm::dds::SchedulingQosPolicy > (new ::iccm::dds::SchedulingQosPolicy (e));
        listener_scheduling_->container (this);
      }
    }

    // DomainParticipantQos
    //
    inline
    DomainParticipantQos::datawriter_iterator DomainParticipantQos::
    begin_datawriter ()
    {
      return datawriter_.begin ();
    }

    inline
    DomainParticipantQos::datawriter_iterator DomainParticipantQos::
    end_datawriter ()
    {
      return datawriter_.end ();
    }

    inline
    DomainParticipantQos::datawriter_const_iterator DomainParticipantQos::
    begin_datawriter () const
    {
      return datawriter_.begin ();
    }

    inline
    DomainParticipantQos::datawriter_const_iterator DomainParticipantQos::
    end_datawriter () const
    {
      return datawriter_.end ();
    }

    inline
    void DomainParticipantQos::
    add_datawriter (ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataWriterQos, ACE_Null_Mutex >  const& e)
    {
      datawriter_.push_back (e);
    }

    inline
    size_t DomainParticipantQos::
    count_datawriter(void) const
    {
      return datawriter_.size ();
    }

    // DomainParticipantQos
    //
    inline
    DomainParticipantQos::datareader_iterator DomainParticipantQos::
    begin_datareader ()
    {
      return datareader_.begin ();
    }

    inline
    DomainParticipantQos::datareader_iterator DomainParticipantQos::
    end_datareader ()
    {
      return datareader_.end ();
    }

    inline
    DomainParticipantQos::datareader_const_iterator DomainParticipantQos::
    begin_datareader () const
    {
      return datareader_.begin ();
    }

    inline
    DomainParticipantQos::datareader_const_iterator DomainParticipantQos::
    end_datareader () const
    {
      return datareader_.end ();
    }

    inline
    void DomainParticipantQos::
    add_datareader (ACE_Refcounted_Auto_Ptr < ::iccm::dds::DataReaderQos, ACE_Null_Mutex >  const& e)
    {
      datareader_.push_back (e);
    }

    inline
    size_t DomainParticipantQos::
    count_datareader(void) const
    {
      return datareader_.size ();
    }

    // DomainParticipantQos
    //
    inline
    DomainParticipantQos::publisher_iterator DomainParticipantQos::
    begin_publisher ()
    {
      return publisher_.begin ();
    }

    inline
    DomainParticipantQos::publisher_iterator DomainParticipantQos::
    end_publisher ()
    {
      return publisher_.end ();
    }

    inline
    DomainParticipantQos::publisher_const_iterator DomainParticipantQos::
    begin_publisher () const
    {
      return publisher_.begin ();
    }

    inline
    DomainParticipantQos::publisher_const_iterator DomainParticipantQos::
    end_publisher () const
    {
      return publisher_.end ();
    }

    inline
    void DomainParticipantQos::
    add_publisher (ACE_Refcounted_Auto_Ptr < ::iccm::dds::PublisherQos, ACE_Null_Mutex >  const& e)
    {
      publisher_.push_back (e);
    }

    inline
    size_t DomainParticipantQos::
    count_publisher(void) const
    {
      return publisher_.size ();
    }

    // DomainParticipantQos
    //
    inline
    DomainParticipantQos::subscriber_iterator DomainParticipantQos::
    begin_subscriber ()
    {
      return subscriber_.begin ();
    }

    inline
    DomainParticipantQos::subscriber_iterator DomainParticipantQos::
    end_subscriber ()
    {
      return subscriber_.end ();
    }

    inline
    DomainParticipantQos::subscriber_const_iterator DomainParticipantQos::
    begin_subscriber () const
    {
      return subscriber_.begin ();
    }

    inline
    DomainParticipantQos::subscriber_const_iterator DomainParticipantQos::
    end_subscriber () const
    {
      return subscriber_.end ();
    }

    inline
    void DomainParticipantQos::
    add_subscriber (ACE_Refcounted_Auto_Ptr < ::iccm::dds::SubscriberQos, ACE_Null_Mutex >  const& e)
    {
      subscriber_.push_back (e);
    }

    inline
    size_t DomainParticipantQos::
    count_subscriber(void) const
    {
      return subscriber_.size ();
    }
  }
}

