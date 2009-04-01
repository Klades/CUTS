namespace CUTS
{
  // uniteConfig
  // 

  inline
  uniteConfig::
  uniteConfig (::XMLSchema::string< char > const& name__,
               ::XMLSchema::string< char > const& evaluation__,
               ::XMLSchema::string< char > const& aggregation__,
               ::CUTS::datagraphLink const& datagraph__)
  : 
  ::XSCRT::Type (), 
  name_ (new ::XMLSchema::string< char > (name__)),
  evaluation_ (new ::XMLSchema::string< char > (evaluation__)),
  aggregation_ (new ::XMLSchema::string< char > (aggregation__)),
  datagraph_ (new ::CUTS::datagraphLink (datagraph__)),
  regulator__ ()
  {
    name_->container (this);
    evaluation_->container (this);
    aggregation_->container (this);
    datagraph_->container (this);
  }

  inline
  uniteConfig::
  uniteConfig (uniteConfig const& s)
  :
  ::XSCRT::Type (),
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  description_ (s.description_.get () ? new ::XMLSchema::string< char > (*s.description_) : 0),
  evaluation_ (new ::XMLSchema::string< char > (*s.evaluation_)),
  aggregation_ (new ::XMLSchema::string< char > (*s.aggregation_)),
  datagraph_ (new ::CUTS::datagraphLink (*s.datagraph_)),
  grouping_ (s.grouping_.get () ? new ::CUTS::groupingType (*s.grouping_) : 0),
  regulator__ ()
  {
    name_->container (this);
    if (description_.get ()) description_->container (this);
    evaluation_->container (this);
    aggregation_->container (this);
    datagraph_->container (this);
    if (grouping_.get ()) grouping_->container (this);
  }

  inline
  uniteConfig& uniteConfig::
  operator= (uniteConfig const& s)
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

    return *this;
  }


  // uniteConfig
  // 
  inline
  ::XMLSchema::string< char > const& uniteConfig::
  name () const
  {
    return *name_;
  }

  inline
  void uniteConfig::
  name (::XMLSchema::string< char > const& e)
  {
    *name_ = e;
  }

  // uniteConfig
  // 
  inline
  bool uniteConfig::
  description_p () const
  {
    return description_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& uniteConfig::
  description () const
  {
    return *description_;
  }

  inline
  void uniteConfig::
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

  // uniteConfig
  // 
  inline
  ::XMLSchema::string< char > const& uniteConfig::
  evaluation () const
  {
    return *evaluation_;
  }

  inline
  void uniteConfig::
  evaluation (::XMLSchema::string< char > const& e)
  {
    *evaluation_ = e;
  }

  // uniteConfig
  // 
  inline
  ::XMLSchema::string< char > const& uniteConfig::
  aggregation () const
  {
    return *aggregation_;
  }

  inline
  void uniteConfig::
  aggregation (::XMLSchema::string< char > const& e)
  {
    *aggregation_ = e;
  }

  // uniteConfig
  // 
  inline
  ::CUTS::datagraphLink const& uniteConfig::
  datagraph () const
  {
    return *datagraph_;
  }

  inline
  void uniteConfig::
  datagraph (::CUTS::datagraphLink const& e)
  {
    *datagraph_ = e;
  }

  // uniteConfig
  // 
  inline
  bool uniteConfig::
  grouping_p () const
  {
    return grouping_.get () != 0;
  }

  inline
  ::CUTS::groupingType const& uniteConfig::
  grouping () const
  {
    return *grouping_;
  }

  inline
  void uniteConfig::
  grouping (::CUTS::groupingType const& e)
  {
    if (grouping_.get ())
    {
      *grouping_ = e;
    }

    else
    {
      grouping_ = ::std::auto_ptr< ::CUTS::groupingType > (new ::CUTS::groupingType (e));
      grouping_->container (this);
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
  relations_ (s.relations_.get () ? new ::CUTS::relationList (*s.relations_) : 0),
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
  ::CUTS::relationList const& logformatType::
  relations () const
  {
    return *relations_;
  }

  inline
  void logformatType::
  relations (::CUTS::relationList const& e)
  {
    if (relations_.get ())
    {
      *relations_ = e;
    }

    else
    {
      relations_ = ::std::auto_ptr< ::CUTS::relationList > (new ::CUTS::relationList (e));
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
  add_relation (::CUTS::relationType const& e)
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
  add_causality (::CUTS::causalityType const& e)
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
  logformatList (::std::list< ::CUTS::logformatType > const& logformat__)
  : 
  logformat_ (logformat__),
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
  add_logformat (::CUTS::logformatType const& e)
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
  groupingType (::std::list< ::CUTS::groupitemType > const& groupitem__)
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
  add_groupitem (::CUTS::groupitemType const& e)
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
  datagraphType (::XMLSchema::string< char > const& name__,
                 ::CUTS::logformatList const& logformats__)
  : 
  name_ (new ::XMLSchema::string< char > (name__)),
  logformats_ (new ::CUTS::logformatList (logformats__)),
  regulator__ ()
  {
    name_->container (this);
    logformats_->container (this);
  }

  inline
  datagraphType::
  datagraphType (datagraphType const& s)
  :
  ::XSCRT::Type (),
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  logformats_ (new ::CUTS::logformatList (*s.logformats_)),
  regulator__ ()
  {
    name_->container (this);
    logformats_->container (this);
  }

  inline
  datagraphType& datagraphType::
  operator= (datagraphType const& s)
  {
    name (*s.name_);

    logformats (*s.logformats_);

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
  ::CUTS::logformatList const& datagraphType::
  logformats () const
  {
    return *logformats_;
  }

  inline
  void datagraphType::
  logformats (::CUTS::logformatList const& e)
  {
    *logformats_ = e;
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
}

