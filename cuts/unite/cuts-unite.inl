namespace CUTS
{
  namespace XML
  {
    // testConfig
    //

    inline
    testConfig::
    testConfig (::XMLSchema::string< char > const& name__,
                ::XMLSchema::string< char > const& evaluation__,
                ::XMLSchema::string< char > const& aggregation__,
                ::CUTS::XML::datagraphLink const& datagraph__)
    :
    ::XSCRT::Type (),
    name_ (new ::XMLSchema::string< char > (name__)),
    evaluation_ (new ::XMLSchema::string< char > (evaluation__)),
    aggregation_ (new ::XMLSchema::string< char > (aggregation__)),
    datagraph_ (new ::CUTS::XML::datagraphLink (datagraph__)),
    regulator__ ()
    {
      name_->container (this);
      evaluation_->container (this);
      aggregation_->container (this);
      datagraph_->container (this);
    }

    inline
    testConfig::
    testConfig (testConfig const& s)
    :
    ::XSCRT::Type (),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    description_ (s.description_.get () ? new ::XMLSchema::string< char > (*s.description_) : 0),
    evaluation_ (new ::XMLSchema::string< char > (*s.evaluation_)),
    aggregation_ (new ::XMLSchema::string< char > (*s.aggregation_)),
    datagraph_ (new ::CUTS::XML::datagraphLink (*s.datagraph_)),
    grouping_ (s.grouping_.get () ? new ::CUTS::XML::groupingType (*s.grouping_) : 0),
    services_ (s.services_.get () ? new ::CUTS::XML::serviceList (*s.services_) : 0),
    regulator__ ()
    {
      name_->container (this);
      if (description_.get ()) description_->container (this);
      evaluation_->container (this);
      aggregation_->container (this);
      datagraph_->container (this);
      if (grouping_.get ()) grouping_->container (this);
      if (services_.get ()) services_->container (this);
    }

    inline
    testConfig& testConfig::
    operator= (testConfig const& s)
    {
      name (*s.name_);

      if (s.description_.get ())
        description (*(s.description_));
      else
        description_.reset (0);

      evaluation (*s.evaluation_);

      aggregation (*s.aggregation_);

      datagraph (*s.datagraph_);

      if (s.grouping_.get ())
        grouping (*(s.grouping_));
      else
        grouping_.reset (0);

      if (s.services_.get ())
        services (*(s.services_));
      else
        services_.reset (0);

      return *this;
    }


    // testConfig
    //
    inline
    ::XMLSchema::string< char > const& testConfig::
    name () const
    {
      return *name_;
    }

    inline
    void testConfig::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }

    // testConfig
    //
    inline
    bool testConfig::
    description_p () const
    {
      return description_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& testConfig::
    description () const
    {
      return *description_;
    }

    inline
    void testConfig::
    description (::XMLSchema::string< char > const& e)
    {
      if (description_.get ())
      {
        *description_ = e;
      }

      else
      {
        description_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        description_->container (this);
      }
    }

    // testConfig
    //
    inline
    ::XMLSchema::string< char > const& testConfig::
    evaluation () const
    {
      return *evaluation_;
    }

    inline
    void testConfig::
    evaluation (::XMLSchema::string< char > const& e)
    {
      *evaluation_ = e;
    }

    // testConfig
    //
    inline
    ::XMLSchema::string< char > const& testConfig::
    aggregation () const
    {
      return *aggregation_;
    }

    inline
    void testConfig::
    aggregation (::XMLSchema::string< char > const& e)
    {
      *aggregation_ = e;
    }

    // testConfig
    //
    inline
    ::CUTS::XML::datagraphLink const& testConfig::
    datagraph () const
    {
      return *datagraph_;
    }

    inline
    void testConfig::
    datagraph (::CUTS::XML::datagraphLink const& e)
    {
      *datagraph_ = e;
    }

    // testConfig
    //
    inline
    bool testConfig::
    grouping_p () const
    {
      return grouping_.get () != 0;
    }

    inline
    ::CUTS::XML::groupingType const& testConfig::
    grouping () const
    {
      return *grouping_;
    }

    inline
    void testConfig::
    grouping (::CUTS::XML::groupingType const& e)
    {
      if (grouping_.get ())
      {
        *grouping_ = e;
      }

      else
      {
        grouping_ = ::std::auto_ptr< ::CUTS::XML::groupingType > (new ::CUTS::XML::groupingType (e));
        grouping_->container (this);
      }
    }

    // testConfig
    //
    inline
    bool testConfig::
    services_p () const
    {
      return services_.get () != 0;
    }

    inline
    ::CUTS::XML::serviceList const& testConfig::
    services () const
    {
      return *services_;
    }

    inline
    void testConfig::
    services (::CUTS::XML::serviceList const& e)
    {
      if (services_.get ())
      {
        *services_ = e;
      }

      else
      {
        services_ = ::std::auto_ptr< ::CUTS::XML::serviceList > (new ::CUTS::XML::serviceList (e));
        services_->container (this);
      }
    }


    // logformatType
    //

    inline
    logformatType::
    logformatType (::XMLSchema::string< char > const& value__,
                   ::XMLSchema::ID< char > const& id__)
    :
    value_ (new ::XMLSchema::string< char > (value__)),
    id_ (new ::XMLSchema::ID< char > (id__)),
    regulator__ ()
    {
      value_->container (this);
      id_->container (this);
    }

    inline
    logformatType::
    logformatType (logformatType const& s)
    :
    ::XSCRT::Type (),
    value_ (new ::XMLSchema::string< char > (*s.value_)),
    relations_ (s.relations_.get () ? new ::CUTS::XML::relationList (*s.relations_) : 0),
    id_ (new ::XMLSchema::ID< char > (*s.id_)),
    regulator__ ()
    {
      value_->container (this);
      if (relations_.get ()) relations_->container (this);
      id_->container (this);
    }

    inline
    logformatType& logformatType::
    operator= (logformatType const& s)
    {
      value (*s.value_);

      if (s.relations_.get ())
        relations (*(s.relations_));
      else
        relations_.reset (0);

      id (s.id ());

      return *this;
    }


    // logformatType
    //
    inline
    ::XMLSchema::string< char > const& logformatType::
    value () const
    {
      return *value_;
    }

    inline
    void logformatType::
    value (::XMLSchema::string< char > const& e)
    {
      *value_ = e;
    }

    // logformatType
    //
    inline
    bool logformatType::
    relations_p () const
    {
      return relations_.get () != 0;
    }

    inline
    ::CUTS::XML::relationList const& logformatType::
    relations () const
    {
      return *relations_;
    }

    inline
    void logformatType::
    relations (::CUTS::XML::relationList const& e)
    {
      if (relations_.get ())
      {
        *relations_ = e;
      }

      else
      {
        relations_ = ::std::auto_ptr< ::CUTS::XML::relationList > (new ::CUTS::XML::relationList (e));
        relations_->container (this);
      }
    }

    // logformatType
    //
    inline
    ::XMLSchema::ID< char > const& logformatType::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::ID< char >& logformatType::
    id ()
    {
      return *id_;
    }

    inline
    void logformatType::
    id (::XMLSchema::ID< char > const& e)
    {
      *id_ = e;
    }


    // relationList
    //

    inline
    relationList::
    relationList ()
    :
    regulator__ ()
    {
    }

    inline
    relationList::
    relationList (relationList const& s)
    :
    ::XSCRT::Type (),
    relation_ (s.relation_),
    regulator__ ()
    {
    }

    inline
    relationList& relationList::
    operator= (relationList const& s)
    {
      relation_ = s.relation_;

      return *this;
    }


    // relationList
    //
    inline
    relationList::relation_iterator relationList::
    begin_relation ()
    {
      return relation_.begin ();
    }

    inline
    relationList::relation_iterator relationList::
    end_relation ()
    {
      return relation_.end ();
    }

    inline
    relationList::relation_const_iterator relationList::
    begin_relation () const
    {
      return relation_.begin ();
    }

    inline
    relationList::relation_const_iterator relationList::
    end_relation () const
    {
      return relation_.end ();
    }

    inline
    void relationList::
    add_relation (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::relationType, ACE_Null_Mutex >  const& e)
    {
      relation_.push_back (e);
    }

    inline
    size_t relationList::
    count_relation(void) const
    {
      return relation_.size ();
    }


    // causalityType
    //

    inline
    causalityType::
    causalityType (::XMLSchema::string< char > const& cause__,
                   ::XMLSchema::string< char > const& effect__)
    :
    cause_ (new ::XMLSchema::string< char > (cause__)),
    effect_ (new ::XMLSchema::string< char > (effect__)),
    regulator__ ()
    {
      cause_->container (this);
      effect_->container (this);
    }

    inline
    causalityType::
    causalityType (causalityType const& s)
    :
    cause_ (new ::XMLSchema::string< char > (*s.cause_)),
    effect_ (new ::XMLSchema::string< char > (*s.effect_)),
    regulator__ ()
    {
      cause_->container (this);
      effect_->container (this);
    }

    inline
    causalityType& causalityType::
    operator= (causalityType const& s)
    {
      cause (s.cause ());

      effect (s.effect ());

      return *this;
    }


    // causalityType
    //
    inline
    ::XMLSchema::string< char > const& causalityType::
    cause () const
    {
      return *cause_;
    }

    inline
    ::XMLSchema::string< char >& causalityType::
    cause ()
    {
      return *cause_;
    }

    inline
    void causalityType::
    cause (::XMLSchema::string< char > const& e)
    {
      *cause_ = e;
    }

    // causalityType
    //
    inline
    ::XMLSchema::string< char > const& causalityType::
    effect () const
    {
      return *effect_;
    }

    inline
    ::XMLSchema::string< char >& causalityType::
    effect ()
    {
      return *effect_;
    }

    inline
    void causalityType::
    effect (::XMLSchema::string< char > const& e)
    {
      *effect_ = e;
    }


    // relationType
    //

    inline
    relationType::
    relationType (::XMLSchema::NCName< char > const& effectref__)
    :
    effectref_ (new ::XMLSchema::NCName< char > (effectref__)),
    regulator__ ()
    {
      effectref_->container (this);
    }

    inline
    relationType::
    relationType (relationType const& s)
    :
    ::XSCRT::Type (),
    causality_ (s.causality_),
    effectref_ (new ::XMLSchema::NCName< char > (*s.effectref_)),
    regulator__ ()
    {
      effectref_->container (this);
    }

    inline
    relationType& relationType::
    operator= (relationType const& s)
    {
      causality_ = s.causality_;

      effectref (s.effectref ());

      return *this;
    }


    // relationType
    //
    inline
    relationType::causality_iterator relationType::
    begin_causality ()
    {
      return causality_.begin ();
    }

    inline
    relationType::causality_iterator relationType::
    end_causality ()
    {
      return causality_.end ();
    }

    inline
    relationType::causality_const_iterator relationType::
    begin_causality () const
    {
      return causality_.begin ();
    }

    inline
    relationType::causality_const_iterator relationType::
    end_causality () const
    {
      return causality_.end ();
    }

    inline
    void relationType::
    add_causality (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::causalityType, ACE_Null_Mutex >  const& e)
    {
      causality_.push_back (e);
    }

    inline
    size_t relationType::
    count_causality(void) const
    {
      return causality_.size ();
    }

    // relationType
    //
    inline
    ::XMLSchema::NCName< char > const& relationType::
    effectref () const
    {
      return *effectref_;
    }

    inline
    ::XMLSchema::NCName< char >& relationType::
    effectref ()
    {
      return *effectref_;
    }

    inline
    void relationType::
    effectref (::XMLSchema::NCName< char > const& e)
    {
      *effectref_ = e;
    }


    // logformatList
    //

    inline
    logformatList::
    logformatList ()
    :
    regulator__ ()
    {
    }

    inline
    logformatList::
    logformatList (logformatList const& s)
    :
    ::XSCRT::Type (),
    logformat_ (s.logformat_),
    regulator__ ()
    {
    }

    inline
    logformatList& logformatList::
    operator= (logformatList const& s)
    {
      logformat_ = s.logformat_;

      return *this;
    }


    // logformatList
    //
    inline
    logformatList::logformat_iterator logformatList::
    begin_logformat ()
    {
      return logformat_.begin ();
    }

    inline
    logformatList::logformat_iterator logformatList::
    end_logformat ()
    {
      return logformat_.end ();
    }

    inline
    logformatList::logformat_const_iterator logformatList::
    begin_logformat () const
    {
      return logformat_.begin ();
    }

    inline
    logformatList::logformat_const_iterator logformatList::
    end_logformat () const
    {
      return logformat_.end ();
    }

    inline
    void logformatList::
    add_logformat (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::logformatType, ACE_Null_Mutex >  const& e)
    {
      logformat_.push_back (e);
    }

    inline
    size_t logformatList::
    count_logformat(void) const
    {
      return logformat_.size ();
    }


    // groupitemType
    //

    inline
    groupitemType::
    groupitemType (::XMLSchema::string< char > const& name__)
    :
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      name_->container (this);
    }

    inline
    groupitemType::
    groupitemType (groupitemType const& s)
    :
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    regulator__ ()
    {
      name_->container (this);
    }

    inline
    groupitemType& groupitemType::
    operator= (groupitemType const& s)
    {
      name (s.name ());

      return *this;
    }


    // groupitemType
    //
    inline
    ::XMLSchema::string< char > const& groupitemType::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& groupitemType::
    name ()
    {
      return *name_;
    }

    inline
    void groupitemType::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }


    // groupingType
    //

    inline
    groupingType::
    groupingType (::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::XML::groupitemType, ACE_Null_Mutex > > const& groupitem__)
    :
    groupitem_ (groupitem__),
    regulator__ ()
    {
    }

    inline
    groupingType::
    groupingType (groupingType const& s)
    :
    ::XSCRT::Type (),
    groupitem_ (s.groupitem_),
    regulator__ ()
    {
    }

    inline
    groupingType& groupingType::
    operator= (groupingType const& s)
    {
      groupitem_ = s.groupitem_;

      return *this;
    }


    // groupingType
    //
    inline
    groupingType::groupitem_iterator groupingType::
    begin_groupitem ()
    {
      return groupitem_.begin ();
    }

    inline
    groupingType::groupitem_iterator groupingType::
    end_groupitem ()
    {
      return groupitem_.end ();
    }

    inline
    groupingType::groupitem_const_iterator groupingType::
    begin_groupitem () const
    {
      return groupitem_.begin ();
    }

    inline
    groupingType::groupitem_const_iterator groupingType::
    end_groupitem () const
    {
      return groupitem_.end ();
    }

    inline
    void groupingType::
    add_groupitem (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::groupitemType, ACE_Null_Mutex >  const& e)
    {
      groupitem_.push_back (e);
    }

    inline
    size_t groupingType::
    count_groupitem(void) const
    {
      return groupitem_.size ();
    }


    // datagraphType
    //

    inline
    datagraphType::
    datagraphType (::XMLSchema::string< char > const& name__)
    :
    name_ (new ::XMLSchema::string< char > (name__)),
    regulator__ ()
    {
      name_->container (this);
    }

    inline
    datagraphType::
    datagraphType (datagraphType const& s)
    :
    ::XSCRT::Type (),
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    adapter_ (s.adapter_.get () ? new ::XMLSchema::string< char > (*s.adapter_) : 0),
    interpreter_ (s.interpreter_.get () ? new ::XMLSchema::string< char > (*s.interpreter_) : 0),
    logformats_ (s.logformats_.get () ? new ::CUTS::XML::logformatList (*s.logformats_) : 0),
    regulator__ ()
    {
      name_->container (this);
      if (adapter_.get ()) adapter_->container (this);
      if (interpreter_.get ()) interpreter_->container (this);
      if (logformats_.get ()) logformats_->container (this);
    }

    inline
    datagraphType& datagraphType::
    operator= (datagraphType const& s)
    {
      name (*s.name_);

      if (s.adapter_.get ())
        adapter (*(s.adapter_));
      else
        adapter_.reset (0);

      if (s.interpreter_.get ())
        interpreter (*(s.interpreter_));
      else
        interpreter_.reset (0);

      if (s.logformats_.get ())
        logformats (*(s.logformats_));
      else
        logformats_.reset (0);

      return *this;
    }


    // datagraphType
    //
    inline
    ::XMLSchema::string< char > const& datagraphType::
    name () const
    {
      return *name_;
    }

    inline
    void datagraphType::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }

    // datagraphType
    //
    inline
    bool datagraphType::
    adapter_p () const
    {
      return adapter_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& datagraphType::
    adapter () const
    {
      return *adapter_;
    }

    inline
    void datagraphType::
    adapter (::XMLSchema::string< char > const& e)
    {
      if (adapter_.get ())
      {
        *adapter_ = e;
      }

      else
      {
        adapter_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        adapter_->container (this);
      }
    }

    // datagraphType
    //
    inline
    bool datagraphType::
    interpreter_p () const
    {
      return interpreter_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& datagraphType::
    interpreter () const
    {
      return *interpreter_;
    }

    inline
    void datagraphType::
    interpreter (::XMLSchema::string< char > const& e)
    {
      if (interpreter_.get ())
      {
        *interpreter_ = e;
      }

      else
      {
        interpreter_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        interpreter_->container (this);
      }
    }

    // datagraphType
    //
    inline
    bool datagraphType::
    logformats_p () const
    {
      return logformats_.get () != 0;
    }

    inline
    ::CUTS::XML::logformatList const& datagraphType::
    logformats () const
    {
      return *logformats_;
    }

    inline
    void datagraphType::
    logformats (::CUTS::XML::logformatList const& e)
    {
      if (logformats_.get ())
      {
        *logformats_ = e;
      }

      else
      {
        logformats_ = ::std::auto_ptr< ::CUTS::XML::logformatList > (new ::CUTS::XML::logformatList (e));
        logformats_->container (this);
      }
    }


    // datagraphLink
    //

    inline
    datagraphLink::
    datagraphLink (::XMLSchema::anyURI< char > const& location__)
    :
    location_ (new ::XMLSchema::anyURI< char > (location__)),
    regulator__ ()
    {
      location_->container (this);
    }

    inline
    datagraphLink::
    datagraphLink (datagraphLink const& s)
    :
    location_ (new ::XMLSchema::anyURI< char > (*s.location_)),
    regulator__ ()
    {
      location_->container (this);
    }

    inline
    datagraphLink& datagraphLink::
    operator= (datagraphLink const& s)
    {
      location (s.location ());

      return *this;
    }


    // datagraphLink
    //
    inline
    ::XMLSchema::anyURI< char > const& datagraphLink::
    location () const
    {
      return *location_;
    }

    inline
    ::XMLSchema::anyURI< char >& datagraphLink::
    location ()
    {
      return *location_;
    }

    inline
    void datagraphLink::
    location (::XMLSchema::anyURI< char > const& e)
    {
      *location_ = e;
    }


    // filterList
    //

    inline
    filterList::
    filterList ()
    :
    regulator__ ()
    {
    }

    inline
    filterList::
    filterList (filterList const& s)
    :
    ::XSCRT::Type (),
    filter_ (s.filter_),
    regulator__ ()
    {
    }

    inline
    filterList& filterList::
    operator= (filterList const& s)
    {
      filter_ = s.filter_;

      return *this;
    }


    // filterList
    //
    inline
    filterList::filter_iterator filterList::
    begin_filter ()
    {
      return filter_.begin ();
    }

    inline
    filterList::filter_iterator filterList::
    end_filter ()
    {
      return filter_.end ();
    }

    inline
    filterList::filter_const_iterator filterList::
    begin_filter () const
    {
      return filter_.begin ();
    }

    inline
    filterList::filter_const_iterator filterList::
    end_filter () const
    {
      return filter_.end ();
    }

    inline
    void filterList::
    add_filter (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::filterType, ACE_Null_Mutex >  const& e)
    {
      filter_.push_back (e);
    }

    inline
    size_t filterList::
    count_filter(void) const
    {
      return filter_.size ();
    }


    // filterType
    //

    inline
    filterType::
    filterType (::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::XML::filterVariableType, ACE_Null_Mutex > > const& variable__,
                ::XMLSchema::ID< char > const& id__,
                ::XMLSchema::string< char > const& target__)
    :
    variable_ (variable__),
    id_ (new ::XMLSchema::ID< char > (id__)),
    target_ (new ::XMLSchema::string< char > (target__)),
    regulator__ ()
    {
      id_->container (this);
      target_->container (this);
    }

    inline
    filterType::
    filterType (filterType const& s)
    :
    ::XSCRT::Type (),
    variable_ (s.variable_),
    id_ (new ::XMLSchema::ID< char > (*s.id_)),
    target_ (new ::XMLSchema::string< char > (*s.target_)),
    regulator__ ()
    {
      id_->container (this);
      target_->container (this);
    }

    inline
    filterType& filterType::
    operator= (filterType const& s)
    {
      variable_ = s.variable_;

      id (s.id ());

      target (s.target ());

      return *this;
    }


    // filterType
    //
    inline
    filterType::variable_iterator filterType::
    begin_variable ()
    {
      return variable_.begin ();
    }

    inline
    filterType::variable_iterator filterType::
    end_variable ()
    {
      return variable_.end ();
    }

    inline
    filterType::variable_const_iterator filterType::
    begin_variable () const
    {
      return variable_.begin ();
    }

    inline
    filterType::variable_const_iterator filterType::
    end_variable () const
    {
      return variable_.end ();
    }

    inline
    void filterType::
    add_variable (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::filterVariableType, ACE_Null_Mutex >  const& e)
    {
      variable_.push_back (e);
    }

    inline
    size_t filterType::
    count_variable(void) const
    {
      return variable_.size ();
    }

    // filterType
    //
    inline
    ::XMLSchema::ID< char > const& filterType::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::ID< char >& filterType::
    id ()
    {
      return *id_;
    }

    inline
    void filterType::
    id (::XMLSchema::ID< char > const& e)
    {
      *id_ = e;
    }

    // filterType
    //
    inline
    ::XMLSchema::string< char > const& filterType::
    target () const
    {
      return *target_;
    }

    inline
    ::XMLSchema::string< char >& filterType::
    target ()
    {
      return *target_;
    }

    inline
    void filterType::
    target (::XMLSchema::string< char > const& e)
    {
      *target_ = e;
    }


    // filterVariableType
    //

    inline
    filterVariableType::
    filterVariableType ()
    :
    regulator__ ()
    {
    }

    inline
    filterVariableType::
    filterVariableType (filterVariableType const& s)
    :
    name_ (s.name_.get () ? new ::XMLSchema::string< char > (*s.name_) : 0),
    when_ (s.when_.get () ? new ::XMLSchema::string< char > (*s.when_) : 0),
    regulator__ ()
    {
      if (name_.get ()) name_->container (this);
      if (when_.get ()) when_->container (this);
    }

    inline
    filterVariableType& filterVariableType::
    operator= (filterVariableType const& s)
    {
      if (s.name_.get ()) name (*(s.name_));
      else name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (0);

      if (s.when_.get ()) when (*(s.when_));
      else when_ = ::std::auto_ptr< ::XMLSchema::string< char > > (0);

      return *this;
    }


    // filterVariableType
    //
    inline
    bool filterVariableType::
    name_p () const
    {
      return name_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& filterVariableType::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& filterVariableType::
    name ()
    {
      return *name_;
    }

    inline
    void filterVariableType::
    name (::XMLSchema::string< char > const& e)
    {
      if (name_.get ())
      {
        *name_ = e;
      }

      else
      {
        name_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        name_->container (this);
      }
    }

    // filterVariableType
    //
    inline
    bool filterVariableType::
    when_p () const
    {
      return when_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& filterVariableType::
    when () const
    {
      return *when_;
    }

    inline
    ::XMLSchema::string< char >& filterVariableType::
    when ()
    {
      return *when_;
    }

    inline
    void filterVariableType::
    when (::XMLSchema::string< char > const& e)
    {
      if (when_.get ())
      {
        *when_ = e;
      }

      else
      {
        when_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        when_->container (this);
      }
    }


    // serviceType
    //

    inline
    serviceType::
    serviceType (::XMLSchema::string< char > const& location__,
                 ::XMLSchema::string< char > const& classname__,
                 ::XMLSchema::ID< char > const& id__)
    :
    location_ (new ::XMLSchema::string< char > (location__)),
    classname_ (new ::XMLSchema::string< char > (classname__)),
    id_ (new ::XMLSchema::ID< char > (id__)),
    regulator__ ()
    {
      location_->container (this);
      classname_->container (this);
      id_->container (this);
    }

    inline
    serviceType::
    serviceType (serviceType const& s)
    :
    ::XSCRT::Type (),
    location_ (new ::XMLSchema::string< char > (*s.location_)),
    classname_ (new ::XMLSchema::string< char > (*s.classname_)),
    params_ (s.params_.get () ? new ::XMLSchema::string< char > (*s.params_) : 0),
    id_ (new ::XMLSchema::ID< char > (*s.id_)),
    regulator__ ()
    {
      location_->container (this);
      classname_->container (this);
      if (params_.get ()) params_->container (this);
      id_->container (this);
    }

    inline
    serviceType& serviceType::
    operator= (serviceType const& s)
    {
      location (*s.location_);

      classname (*s.classname_);

      if (s.params_.get ())
        params (*(s.params_));
      else
        params_.reset (0);

      id (s.id ());

      return *this;
    }


    // serviceType
    //
    inline
    ::XMLSchema::string< char > const& serviceType::
    location () const
    {
      return *location_;
    }

    inline
    void serviceType::
    location (::XMLSchema::string< char > const& e)
    {
      *location_ = e;
    }

    // serviceType
    //
    inline
    ::XMLSchema::string< char > const& serviceType::
    classname () const
    {
      return *classname_;
    }

    inline
    void serviceType::
    classname (::XMLSchema::string< char > const& e)
    {
      *classname_ = e;
    }

    // serviceType
    //
    inline
    bool serviceType::
    params_p () const
    {
      return params_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& serviceType::
    params () const
    {
      return *params_;
    }

    inline
    void serviceType::
    params (::XMLSchema::string< char > const& e)
    {
      if (params_.get ())
      {
        *params_ = e;
      }

      else
      {
        params_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        params_->container (this);
      }
    }

    // serviceType
    //
    inline
    ::XMLSchema::ID< char > const& serviceType::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::ID< char >& serviceType::
    id ()
    {
      return *id_;
    }

    inline
    void serviceType::
    id (::XMLSchema::ID< char > const& e)
    {
      *id_ = e;
    }


    // serviceList
    //

    inline
    serviceList::
    serviceList (::std::list< ACE_Refcounted_Auto_Ptr < ::CUTS::XML::serviceType, ACE_Null_Mutex > > const& service__)
    :
    service_ (service__),
    regulator__ ()
    {
    }

    inline
    serviceList::
    serviceList (serviceList const& s)
    :
    ::XSCRT::Type (),
    service_ (s.service_),
    regulator__ ()
    {
    }

    inline
    serviceList& serviceList::
    operator= (serviceList const& s)
    {
      service_ = s.service_;

      return *this;
    }


    // serviceList
    //
    inline
    serviceList::service_iterator serviceList::
    begin_service ()
    {
      return service_.begin ();
    }

    inline
    serviceList::service_iterator serviceList::
    end_service ()
    {
      return service_.end ();
    }

    inline
    serviceList::service_const_iterator serviceList::
    begin_service () const
    {
      return service_.begin ();
    }

    inline
    serviceList::service_const_iterator serviceList::
    end_service () const
    {
      return service_.end ();
    }

    inline
    void serviceList::
    add_service (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::serviceType, ACE_Null_Mutex >  const& e)
    {
      service_.push_back (e);
    }

    inline
    size_t serviceList::
    count_service(void) const
    {
      return service_.size ();
    }


    // joinType
    //

    inline
    joinType::Value joinType::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::CUTS::XML::joinType const& a, ::CUTS::XML::joinType const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::CUTS::XML::joinType const& a, ::CUTS::XML::joinType const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    joinType::
    joinType (joinType::Value v)
    : v_ (v)
    {
    }

    // expressionType
    //

    inline
    expressionType::
    expressionType (::XMLSchema::string< char > const& format__,
                    ::XMLSchema::string< char > const& variable__,
                    ::XMLSchema::string< char > const& value__)
    :
    format_ (new ::XMLSchema::string< char > (format__)),
    variable_ (new ::XMLSchema::string< char > (variable__)),
    value_ (new ::XMLSchema::string< char > (value__)),
    regulator__ ()
    {
      format_->container (this);
      variable_->container (this);
      value_->container (this);
    }

    inline
    expressionType::
    expressionType (expressionType const& s)
    :
    format_ (new ::XMLSchema::string< char > (*s.format_)),
    variable_ (new ::XMLSchema::string< char > (*s.variable_)),
    value_ (new ::XMLSchema::string< char > (*s.value_)),
    negate_ (s.negate_.get () ? new ::XMLSchema::boolean (*s.negate_) : 0),
    regulator__ ()
    {
      format_->container (this);
      variable_->container (this);
      value_->container (this);
      if (negate_.get ()) negate_->container (this);
    }

    inline
    expressionType& expressionType::
    operator= (expressionType const& s)
    {
      format (s.format ());

      variable (s.variable ());

      value (s.value ());

      if (s.negate_.get ()) negate (*(s.negate_));
      else negate_ = ::std::auto_ptr< ::XMLSchema::boolean > (0);

      return *this;
    }


    // expressionType
    //
    inline
    ::XMLSchema::string< char > const& expressionType::
    format () const
    {
      return *format_;
    }

    inline
    ::XMLSchema::string< char >& expressionType::
    format ()
    {
      return *format_;
    }

    inline
    void expressionType::
    format (::XMLSchema::string< char > const& e)
    {
      *format_ = e;
    }

    // expressionType
    //
    inline
    ::XMLSchema::string< char > const& expressionType::
    variable () const
    {
      return *variable_;
    }

    inline
    ::XMLSchema::string< char >& expressionType::
    variable ()
    {
      return *variable_;
    }

    inline
    void expressionType::
    variable (::XMLSchema::string< char > const& e)
    {
      *variable_ = e;
    }

    // expressionType
    //
    inline
    ::XMLSchema::string< char > const& expressionType::
    value () const
    {
      return *value_;
    }

    inline
    ::XMLSchema::string< char >& expressionType::
    value ()
    {
      return *value_;
    }

    inline
    void expressionType::
    value (::XMLSchema::string< char > const& e)
    {
      *value_ = e;
    }

    // expressionType
    //
    inline
    bool expressionType::
    negate_p () const
    {
      return negate_.get () != 0;
    }

    inline
    ::XMLSchema::boolean const& expressionType::
    negate () const
    {
      return *negate_;
    }

    inline
    ::XMLSchema::boolean& expressionType::
    negate ()
    {
      return *negate_;
    }

    inline
    void expressionType::
    negate (::XMLSchema::boolean const& e)
    {
      if (negate_.get ())
      {
        *negate_ = e;
      }

      else
      {
        negate_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
        negate_->container (this);
      }
    }


    // aspectType
    //

    inline
    aspectType::
    aspectType (::XMLSchema::string< char > const& condition__)
    :
    condition_ (new ::XMLSchema::string< char > (condition__)),
    regulator__ ()
    {
      condition_->container (this);
    }

    inline
    aspectType::
    aspectType (aspectType const& s)
    :
    ::XSCRT::Type (),
    name_ (s.name_.get () ? new ::XMLSchema::ID< char > (*s.name_) : 0),
    viewpoint_ (s.viewpoint_.get () ? new ::CUTS::XML::viewpointType (*s.viewpoint_) : 0),
    condition_ (new ::XMLSchema::string< char > (*s.condition_)),
    regulator__ ()
    {
      if (name_.get ()) name_->container (this);
      if (viewpoint_.get ()) viewpoint_->container (this);
      condition_->container (this);
    }

    inline
    aspectType& aspectType::
    operator= (aspectType const& s)
    {
      if (s.name_.get ())
        name (*(s.name_));
      else
        name_.reset (0);

      if (s.viewpoint_.get ())
        viewpoint (*(s.viewpoint_));
      else
        viewpoint_.reset (0);

      condition (*s.condition_);

      return *this;
    }


    // aspectType
    //
    inline
    bool aspectType::
    name_p () const
    {
      return name_.get () != 0;
    }

    inline
    ::XMLSchema::ID< char > const& aspectType::
    name () const
    {
      return *name_;
    }

    inline
    void aspectType::
    name (::XMLSchema::ID< char > const& e)
    {
      if (name_.get ())
      {
        *name_ = e;
      }

      else
      {
        name_ = ::std::auto_ptr< ::XMLSchema::ID< char > > (new ::XMLSchema::ID< char > (e));
        name_->container (this);
      }
    }

    // aspectType
    //
    inline
    bool aspectType::
    viewpoint_p () const
    {
      return viewpoint_.get () != 0;
    }

    inline
    ::CUTS::XML::viewpointType const& aspectType::
    viewpoint () const
    {
      return *viewpoint_;
    }

    inline
    void aspectType::
    viewpoint (::CUTS::XML::viewpointType const& e)
    {
      if (viewpoint_.get ())
      {
        *viewpoint_ = e;
      }

      else
      {
        viewpoint_ = ::std::auto_ptr< ::CUTS::XML::viewpointType > (new ::CUTS::XML::viewpointType (e));
        viewpoint_->container (this);
      }
    }

    // aspectType
    //
    inline
    ::XMLSchema::string< char > const& aspectType::
    condition () const
    {
      return *condition_;
    }

    inline
    void aspectType::
    condition (::XMLSchema::string< char > const& e)
    {
      *condition_ = e;
    }


    // viewpointType
    //

    inline
    viewpointType::
    viewpointType ()
    :
    regulator__ ()
    {
    }

    inline
    viewpointType::
    viewpointType (viewpointType const& s)
    :
    before_ (s.before_.get () ? new ::XMLSchema::unsignedInt (*s.before_) : 0),
    after_ (s.after_.get () ? new ::XMLSchema::unsignedInt (*s.after_) : 0),
    regulator__ ()
    {
      if (before_.get ()) before_->container (this);
      if (after_.get ()) after_->container (this);
    }

    inline
    viewpointType& viewpointType::
    operator= (viewpointType const& s)
    {
      if (s.before_.get ()) before (*(s.before_));
      else before_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (0);

      if (s.after_.get ()) after (*(s.after_));
      else after_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (0);

      return *this;
    }


    // viewpointType
    //
    inline
    bool viewpointType::
    before_p () const
    {
      return before_.get () != 0;
    }

    inline
    ::XMLSchema::unsignedInt const& viewpointType::
    before () const
    {
      return *before_;
    }

    inline
    ::XMLSchema::unsignedInt& viewpointType::
    before ()
    {
      return *before_;
    }

    inline
    void viewpointType::
    before (::XMLSchema::unsignedInt const& e)
    {
      if (before_.get ())
      {
        *before_ = e;
      }

      else
      {
        before_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (new ::XMLSchema::unsignedInt (e));
        before_->container (this);
      }
    }

    // viewpointType
    //
    inline
    bool viewpointType::
    after_p () const
    {
      return after_.get () != 0;
    }

    inline
    ::XMLSchema::unsignedInt const& viewpointType::
    after () const
    {
      return *after_;
    }

    inline
    ::XMLSchema::unsignedInt& viewpointType::
    after ()
    {
      return *after_;
    }

    inline
    void viewpointType::
    after (::XMLSchema::unsignedInt const& e)
    {
      if (after_.get ())
      {
        *after_ = e;
      }

      else
      {
        after_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (new ::XMLSchema::unsignedInt (e));
        after_->container (this);
      }
    }


    // stateType
    //

    inline
    stateType::
    stateType (::XMLSchema::string< char > const& condition__,
               ::XMLSchema::ID< char > const& name__,
               ::XMLSchema::unsignedInt const& priority__)
    :
    condition_ (new ::XMLSchema::string< char > (condition__)),
    name_ (new ::XMLSchema::ID< char > (name__)),
    priority_ (new ::XMLSchema::unsignedInt (priority__)),
    regulator__ ()
    {
      condition_->container (this);
      name_->container (this);
      priority_->container (this);
    }

    inline
    stateType::
    stateType (stateType const& s)
    :
    ::XSCRT::Type (),
    condition_ (new ::XMLSchema::string< char > (*s.condition_)),
    name_ (new ::XMLSchema::ID< char > (*s.name_)),
    priority_ (new ::XMLSchema::unsignedInt (*s.priority_)),
    minoccurs_ (s.minoccurs_.get () ? new ::XMLSchema::unsignedInt (*s.minoccurs_) : 0),
    maxoccurs_ (s.maxoccurs_.get () ? new ::XMLSchema::string< char > (*s.maxoccurs_) : 0),
    isvalid_ (s.isvalid_.get () ? new ::XMLSchema::boolean (*s.isvalid_) : 0),
    regulator__ ()
    {
      condition_->container (this);
      name_->container (this);
      priority_->container (this);
      if (minoccurs_.get ()) minoccurs_->container (this);
      if (maxoccurs_.get ()) maxoccurs_->container (this);
      if (isvalid_.get ()) isvalid_->container (this);
    }

    inline
    stateType& stateType::
    operator= (stateType const& s)
    {
      condition (*s.condition_);

      name (s.name ());

      priority (s.priority ());

      if (s.minoccurs_.get ()) minoccurs (*(s.minoccurs_));
      else minoccurs_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (0);

      if (s.maxoccurs_.get ()) maxoccurs (*(s.maxoccurs_));
      else maxoccurs_ = ::std::auto_ptr< ::XMLSchema::string< char > > (0);

      if (s.isvalid_.get ()) isvalid (*(s.isvalid_));
      else isvalid_ = ::std::auto_ptr< ::XMLSchema::boolean > (0);

      return *this;
    }


    // stateType
    //
    inline
    ::XMLSchema::string< char > const& stateType::
    condition () const
    {
      return *condition_;
    }

    inline
    void stateType::
    condition (::XMLSchema::string< char > const& e)
    {
      *condition_ = e;
    }

    // stateType
    //
    inline
    ::XMLSchema::ID< char > const& stateType::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::ID< char >& stateType::
    name ()
    {
      return *name_;
    }

    inline
    void stateType::
    name (::XMLSchema::ID< char > const& e)
    {
      *name_ = e;
    }

    // stateType
    //
    inline
    ::XMLSchema::unsignedInt const& stateType::
    priority () const
    {
      return *priority_;
    }

    inline
    ::XMLSchema::unsignedInt& stateType::
    priority ()
    {
      return *priority_;
    }

    inline
    void stateType::
    priority (::XMLSchema::unsignedInt const& e)
    {
      *priority_ = e;
    }

    // stateType
    //
    inline
    bool stateType::
    minoccurs_p () const
    {
      return minoccurs_.get () != 0;
    }

    inline
    ::XMLSchema::unsignedInt const& stateType::
    minoccurs () const
    {
      return *minoccurs_;
    }

    inline
    ::XMLSchema::unsignedInt& stateType::
    minoccurs ()
    {
      return *minoccurs_;
    }

    inline
    void stateType::
    minoccurs (::XMLSchema::unsignedInt const& e)
    {
      if (minoccurs_.get ())
      {
        *minoccurs_ = e;
      }

      else
      {
        minoccurs_ = ::std::auto_ptr< ::XMLSchema::unsignedInt > (new ::XMLSchema::unsignedInt (e));
        minoccurs_->container (this);
      }
    }

    // stateType
    //
    inline
    bool stateType::
    maxoccurs_p () const
    {
      return maxoccurs_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& stateType::
    maxoccurs () const
    {
      return *maxoccurs_;
    }

    inline
    ::XMLSchema::string< char >& stateType::
    maxoccurs ()
    {
      return *maxoccurs_;
    }

    inline
    void stateType::
    maxoccurs (::XMLSchema::string< char > const& e)
    {
      if (maxoccurs_.get ())
      {
        *maxoccurs_ = e;
      }

      else
      {
        maxoccurs_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        maxoccurs_->container (this);
      }
    }

    // stateType
    //
    inline
    bool stateType::
    isvalid_p () const
    {
      return isvalid_.get () != 0;
    }

    inline
    ::XMLSchema::boolean const& stateType::
    isvalid () const
    {
      return *isvalid_;
    }

    inline
    ::XMLSchema::boolean& stateType::
    isvalid ()
    {
      return *isvalid_;
    }

    inline
    void stateType::
    isvalid (::XMLSchema::boolean const& e)
    {
      if (isvalid_.get ())
      {
        *isvalid_ = e;
      }

      else
      {
        isvalid_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
        isvalid_->container (this);
      }
    }


    // validationType
    //

    inline
    validationType::
    validationType (::XMLSchema::string< char > const& datagraph__)
    :
    datagraph_ (new ::XMLSchema::string< char > (datagraph__)),
    regulator__ ()
    {
      datagraph_->container (this);
    }

    inline
    validationType::
    validationType (validationType const& s)
    :
    ::XSCRT::Type (),
    datagraph_ (new ::XMLSchema::string< char > (*s.datagraph_)),
    state_ (s.state_),
    regulator__ ()
    {
      datagraph_->container (this);
    }

    inline
    validationType& validationType::
    operator= (validationType const& s)
    {
      datagraph (*s.datagraph_);

      state_ = s.state_;

      return *this;
    }


    // validationType
    //
    inline
    ::XMLSchema::string< char > const& validationType::
    datagraph () const
    {
      return *datagraph_;
    }

    inline
    void validationType::
    datagraph (::XMLSchema::string< char > const& e)
    {
      *datagraph_ = e;
    }

    // validationType
    //
    inline
    validationType::state_iterator validationType::
    begin_state ()
    {
      return state_.begin ();
    }

    inline
    validationType::state_iterator validationType::
    end_state ()
    {
      return state_.end ();
    }

    inline
    validationType::state_const_iterator validationType::
    begin_state () const
    {
      return state_.begin ();
    }

    inline
    validationType::state_const_iterator validationType::
    end_state () const
    {
      return state_.end ();
    }

    inline
    void validationType::
    add_state (ACE_Refcounted_Auto_Ptr < ::CUTS::XML::stateType, ACE_Null_Mutex >  const& e)
    {
      state_.push_back (e);
    }

    inline
    size_t validationType::
    count_state(void) const
    {
      return state_.size ();
    }
  }
}

