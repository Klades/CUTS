namespace CUTS
{
  // antispamConfig
  // 

  inline
  antispamConfig::
  antispamConfig ()
  : 
  ::XSCRT::Type (), 
  regulator__ ()
  {
  }

  inline
  antispamConfig::
  antispamConfig (antispamConfig const& s)
  :
  ::XSCRT::Type (),
  components_ (s.components_.get () ? new ::CUTS::componentList (*s.components_) : 0),
  assembly_ (s.assembly_.get () ? new ::CUTS::assemblyType (*s.assembly_) : 0),
  deployment_ (s.deployment_.get () ? new ::CUTS::deploymentType (*s.deployment_) : 0),
  regulator__ ()
  {
    if (components_.get ()) components_->container (this);
    if (assembly_.get ()) assembly_->container (this);
    if (deployment_.get ()) deployment_->container (this);
  }

  inline
  antispamConfig& antispamConfig::
  operator= (antispamConfig const& s)
  {
    if (s.components_.get ())
      components (*(s.components_));
    else
      components_.reset (0);

    if (s.assembly_.get ())
      assembly (*(s.assembly_));
    else
      assembly_.reset (0);

    if (s.deployment_.get ())
      deployment (*(s.deployment_));
    else
      deployment_.reset (0);

    return *this;
  }


  // antispamConfig
  // 
  inline
  bool antispamConfig::
  components_p () const
  {
    return components_.get () != 0;
  }

  inline
  ::CUTS::componentList const& antispamConfig::
  components () const
  {
    return *components_;
  }

  inline
  void antispamConfig::
  components (::CUTS::componentList const& e)
  {
    if (components_.get ())
    {
      *components_ = e;
    }

    else
    {
      components_ = ::std::auto_ptr< ::CUTS::componentList > (new ::CUTS::componentList (e));
      components_->container (this);
    }
  }

  // antispamConfig
  // 
  inline
  bool antispamConfig::
  assembly_p () const
  {
    return assembly_.get () != 0;
  }

  inline
  ::CUTS::assemblyType const& antispamConfig::
  assembly () const
  {
    return *assembly_;
  }

  inline
  void antispamConfig::
  assembly (::CUTS::assemblyType const& e)
  {
    if (assembly_.get ())
    {
      *assembly_ = e;
    }

    else
    {
      assembly_ = ::std::auto_ptr< ::CUTS::assemblyType > (new ::CUTS::assemblyType (e));
      assembly_->container (this);
    }
  }

  // antispamConfig
  // 
  inline
  bool antispamConfig::
  deployment_p () const
  {
    return deployment_.get () != 0;
  }

  inline
  ::CUTS::deploymentType const& antispamConfig::
  deployment () const
  {
    return *deployment_;
  }

  inline
  void antispamConfig::
  deployment (::CUTS::deploymentType const& e)
  {
    if (deployment_.get ())
    {
      *deployment_ = e;
    }

    else
    {
      deployment_ = ::std::auto_ptr< ::CUTS::deploymentType > (new ::CUTS::deploymentType (e));
      deployment_->container (this);
    }
  }


  // componentList
  // 

  inline
  componentList::
  componentList ()
  : 
  regulator__ ()
  {
  }

  inline
  componentList::
  componentList (componentList const& s)
  :
  ::XSCRT::Type (),
  component_ (s.component_),
  regulator__ ()
  {
  }

  inline
  componentList& componentList::
  operator= (componentList const& s)
  {
    component_ = s.component_;

    return *this;
  }


  // componentList
  // 
  inline
  componentList::component_iterator componentList::
  begin_component ()
  {
    return component_.begin ();
  }

  inline
  componentList::component_iterator componentList::
  end_component ()
  {
    return component_.end ();
  }

  inline
  componentList::component_const_iterator componentList::
  begin_component () const
  {
    return component_.begin ();
  }

  inline
  componentList::component_const_iterator componentList::
  end_component () const
  {
    return component_.end ();
  }

  inline
  void componentList::
  add_component (::CUTS::componentType const& e)
  {
    component_.push_back (e);
  }

  inline
  size_t componentList::
  count_component(void) const
  {
    return component_.size ();
  }


  // inputType
  // 

  inline
  inputType::
  inputType (::XMLSchema::string< char > const& name__)
  : 
  name_ (new ::XMLSchema::string< char > (name__)),
  regulator__ ()
  {
    name_->container (this);
  }

  inline
  inputType::
  inputType (inputType const& s)
  :
  ::XSCRT::Type (),
  output_ (s.output_),
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  regulator__ ()
  {
    name_->container (this);
  }

  inline
  inputType& inputType::
  operator= (inputType const& s)
  {
    output_ = s.output_;

    name (s.name ());

    return *this;
  }


  // inputType
  // 
  inline
  inputType::output_iterator inputType::
  begin_output ()
  {
    return output_.begin ();
  }

  inline
  inputType::output_iterator inputType::
  end_output ()
  {
    return output_.end ();
  }

  inline
  inputType::output_const_iterator inputType::
  begin_output () const
  {
    return output_.begin ();
  }

  inline
  inputType::output_const_iterator inputType::
  end_output () const
  {
    return output_.end ();
  }

  inline
  void inputType::
  add_output (::XMLSchema::string< char > const& e)
  {
    output_.push_back (e);
  }

  inline
  size_t inputType::
  count_output(void) const
  {
    return output_.size ();
  }

  // inputType
  // 
  inline
  ::XMLSchema::string< char > const& inputType::
  name () const
  {
    return *name_;
  }

  inline
  ::XMLSchema::string< char >& inputType::
  name ()
  {
    return *name_;
  }

  inline
  void inputType::
  name (::XMLSchema::string< char > const& e)
  {
    *name_ = e;
  }


  // componentType
  // 

  inline
  componentType::
  componentType (::XMLSchema::string< char > const& type__)
  : 
  type_ (new ::XMLSchema::string< char > (type__)),
  regulator__ ()
  {
    type_->container (this);
  }

  inline
  componentType::
  componentType (componentType const& s)
  :
  ::XSCRT::Type (),
  input_ (s.input_),
  type_ (new ::XMLSchema::string< char > (*s.type_)),
  regulator__ ()
  {
    type_->container (this);
  }

  inline
  componentType& componentType::
  operator= (componentType const& s)
  {
    input_ = s.input_;

    type (s.type ());

    return *this;
  }


  // componentType
  // 
  inline
  componentType::input_iterator componentType::
  begin_input ()
  {
    return input_.begin ();
  }

  inline
  componentType::input_iterator componentType::
  end_input ()
  {
    return input_.end ();
  }

  inline
  componentType::input_const_iterator componentType::
  begin_input () const
  {
    return input_.begin ();
  }

  inline
  componentType::input_const_iterator componentType::
  end_input () const
  {
    return input_.end ();
  }

  inline
  void componentType::
  add_input (::CUTS::inputType const& e)
  {
    input_.push_back (e);
  }

  inline
  size_t componentType::
  count_input(void) const
  {
    return input_.size ();
  }

  // componentType
  // 
  inline
  ::XMLSchema::string< char > const& componentType::
  type () const
  {
    return *type_;
  }

  inline
  ::XMLSchema::string< char >& componentType::
  type ()
  {
    return *type_;
  }

  inline
  void componentType::
  type (::XMLSchema::string< char > const& e)
  {
    *type_ = e;
  }


  // assemblyType
  // 

  inline
  assemblyType::
  assemblyType ()
  : 
  regulator__ ()
  {
  }

  inline
  assemblyType::
  assemblyType (assemblyType const& s)
  :
  ::XSCRT::Type (),
  instance_ (s.instance_),
  connection_ (s.connection_),
  regulator__ ()
  {
  }

  inline
  assemblyType& assemblyType::
  operator= (assemblyType const& s)
  {
    instance_ = s.instance_;

    connection_ = s.connection_;

    return *this;
  }


  // assemblyType
  // 
  inline
  assemblyType::instance_iterator assemblyType::
  begin_instance ()
  {
    return instance_.begin ();
  }

  inline
  assemblyType::instance_iterator assemblyType::
  end_instance ()
  {
    return instance_.end ();
  }

  inline
  assemblyType::instance_const_iterator assemblyType::
  begin_instance () const
  {
    return instance_.begin ();
  }

  inline
  assemblyType::instance_const_iterator assemblyType::
  end_instance () const
  {
    return instance_.end ();
  }

  inline
  void assemblyType::
  add_instance (::CUTS::instanceType const& e)
  {
    instance_.push_back (e);
  }

  inline
  size_t assemblyType::
  count_instance(void) const
  {
    return instance_.size ();
  }

  // assemblyType
  // 
  inline
  assemblyType::connection_iterator assemblyType::
  begin_connection ()
  {
    return connection_.begin ();
  }

  inline
  assemblyType::connection_iterator assemblyType::
  end_connection ()
  {
    return connection_.end ();
  }

  inline
  assemblyType::connection_const_iterator assemblyType::
  begin_connection () const
  {
    return connection_.begin ();
  }

  inline
  assemblyType::connection_const_iterator assemblyType::
  end_connection () const
  {
    return connection_.end ();
  }

  inline
  void assemblyType::
  add_connection (::CUTS::connectionType const& e)
  {
    connection_.push_back (e);
  }

  inline
  size_t assemblyType::
  count_connection(void) const
  {
    return connection_.size ();
  }


  // instanceInputType
  // 

  inline
  instanceInputType::
  instanceInputType (::XMLSchema::string< char > const& name__,
                     ::XMLSchema::double_ const& baseline__)
  : 
  name_ (new ::XMLSchema::string< char > (name__)),
  baseline_ (new ::XMLSchema::double_ (baseline__)),
  regulator__ ()
  {
    name_->container (this);
    baseline_->container (this);
  }

  inline
  instanceInputType::
  instanceInputType (instanceInputType const& s)
  :
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  baseline_ (new ::XMLSchema::double_ (*s.baseline_)),
  arrival_ (s.arrival_.get () ? new ::XMLSchema::double_ (*s.arrival_) : 0),
  regulator__ ()
  {
    name_->container (this);
    baseline_->container (this);
    if (arrival_.get ()) arrival_->container (this);
  }

  inline
  instanceInputType& instanceInputType::
  operator= (instanceInputType const& s)
  {
    name (s.name ());

    baseline (s.baseline ());

    if (s.arrival_.get ()) arrival (*(s.arrival_));
    else arrival_ = ::std::auto_ptr< ::XMLSchema::double_ > (0);

    return *this;
  }


  // instanceInputType
  // 
  inline
  ::XMLSchema::string< char > const& instanceInputType::
  name () const
  {
    return *name_;
  }

  inline
  ::XMLSchema::string< char >& instanceInputType::
  name ()
  {
    return *name_;
  }

  inline
  void instanceInputType::
  name (::XMLSchema::string< char > const& e)
  {
    *name_ = e;
  }

  // instanceInputType
  // 
  inline
  ::XMLSchema::double_ const& instanceInputType::
  baseline () const
  {
    return *baseline_;
  }

  inline
  ::XMLSchema::double_& instanceInputType::
  baseline ()
  {
    return *baseline_;
  }

  inline
  void instanceInputType::
  baseline (::XMLSchema::double_ const& e)
  {
    *baseline_ = e;
  }

  // instanceInputType
  // 
  inline
  bool instanceInputType::
  arrival_p () const
  {
    return arrival_.get () != 0;
  }

  inline
  ::XMLSchema::double_ const& instanceInputType::
  arrival () const
  {
    return *arrival_;
  }

  inline
  ::XMLSchema::double_& instanceInputType::
  arrival ()
  {
    return *arrival_;
  }

  inline
  void instanceInputType::
  arrival (::XMLSchema::double_ const& e)
  {
    if (arrival_.get ())
    {
      *arrival_ = e;
    }

    else
    {
      arrival_ = ::std::auto_ptr< ::XMLSchema::double_ > (new ::XMLSchema::double_ (e));
      arrival_->container (this);
    }
  }


  // instanceType
  // 

  inline
  instanceType::
  instanceType (::XMLSchema::string< char > const& type__,
                ::XMLSchema::string< char > const& name__)
  : 
  type_ (new ::XMLSchema::string< char > (type__)),
  name_ (new ::XMLSchema::string< char > (name__)),
  regulator__ ()
  {
    type_->container (this);
    name_->container (this);
  }

  inline
  instanceType::
  instanceType (instanceType const& s)
  :
  ::XSCRT::Type (),
  input_ (s.input_),
  type_ (new ::XMLSchema::string< char > (*s.type_)),
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  regulator__ ()
  {
    type_->container (this);
    name_->container (this);
  }

  inline
  instanceType& instanceType::
  operator= (instanceType const& s)
  {
    input_ = s.input_;

    type (s.type ());

    name (s.name ());

    return *this;
  }


  // instanceType
  // 
  inline
  instanceType::input_iterator instanceType::
  begin_input ()
  {
    return input_.begin ();
  }

  inline
  instanceType::input_iterator instanceType::
  end_input ()
  {
    return input_.end ();
  }

  inline
  instanceType::input_const_iterator instanceType::
  begin_input () const
  {
    return input_.begin ();
  }

  inline
  instanceType::input_const_iterator instanceType::
  end_input () const
  {
    return input_.end ();
  }

  inline
  void instanceType::
  add_input (::CUTS::instanceInputType const& e)
  {
    input_.push_back (e);
  }

  inline
  size_t instanceType::
  count_input(void) const
  {
    return input_.size ();
  }

  // instanceType
  // 
  inline
  ::XMLSchema::string< char > const& instanceType::
  type () const
  {
    return *type_;
  }

  inline
  ::XMLSchema::string< char >& instanceType::
  type ()
  {
    return *type_;
  }

  inline
  void instanceType::
  type (::XMLSchema::string< char > const& e)
  {
    *type_ = e;
  }

  // instanceType
  // 
  inline
  ::XMLSchema::string< char > const& instanceType::
  name () const
  {
    return *name_;
  }

  inline
  ::XMLSchema::string< char >& instanceType::
  name ()
  {
    return *name_;
  }

  inline
  void instanceType::
  name (::XMLSchema::string< char > const& e)
  {
    *name_ = e;
  }


  // connectionType
  // 

  inline
  connectionType::
  connectionType (::XMLSchema::string< char > const& src__,
                  ::XMLSchema::string< char > const& dst__)
  : 
  src_ (new ::XMLSchema::string< char > (src__)),
  dst_ (new ::XMLSchema::string< char > (dst__)),
  regulator__ ()
  {
    src_->container (this);
    dst_->container (this);
  }

  inline
  connectionType::
  connectionType (connectionType const& s)
  :
  src_ (new ::XMLSchema::string< char > (*s.src_)),
  dst_ (new ::XMLSchema::string< char > (*s.dst_)),
  regulator__ ()
  {
    src_->container (this);
    dst_->container (this);
  }

  inline
  connectionType& connectionType::
  operator= (connectionType const& s)
  {
    src (s.src ());

    dst (s.dst ());

    return *this;
  }


  // connectionType
  // 
  inline
  ::XMLSchema::string< char > const& connectionType::
  src () const
  {
    return *src_;
  }

  inline
  ::XMLSchema::string< char >& connectionType::
  src ()
  {
    return *src_;
  }

  inline
  void connectionType::
  src (::XMLSchema::string< char > const& e)
  {
    *src_ = e;
  }

  // connectionType
  // 
  inline
  ::XMLSchema::string< char > const& connectionType::
  dst () const
  {
    return *dst_;
  }

  inline
  ::XMLSchema::string< char >& connectionType::
  dst ()
  {
    return *dst_;
  }

  inline
  void connectionType::
  dst (::XMLSchema::string< char > const& e)
  {
    *dst_ = e;
  }


  // deploymentType
  // 

  inline
  deploymentType::
  deploymentType ()
  : 
  regulator__ ()
  {
  }

  inline
  deploymentType::
  deploymentType (deploymentType const& s)
  :
  ::XSCRT::Type (),
  host_ (s.host_),
  regulator__ ()
  {
  }

  inline
  deploymentType& deploymentType::
  operator= (deploymentType const& s)
  {
    host_ = s.host_;

    return *this;
  }


  // deploymentType
  // 
  inline
  deploymentType::host_iterator deploymentType::
  begin_host ()
  {
    return host_.begin ();
  }

  inline
  deploymentType::host_iterator deploymentType::
  end_host ()
  {
    return host_.end ();
  }

  inline
  deploymentType::host_const_iterator deploymentType::
  begin_host () const
  {
    return host_.begin ();
  }

  inline
  deploymentType::host_const_iterator deploymentType::
  end_host () const
  {
    return host_.end ();
  }

  inline
  void deploymentType::
  add_host (::CUTS::hostType const& e)
  {
    host_.push_back (e);
  }

  inline
  size_t deploymentType::
  count_host(void) const
  {
    return host_.size ();
  }


  // hostType
  // 

  inline
  hostType::
  hostType (::XMLSchema::string< char > const& name__)
  : 
  name_ (new ::XMLSchema::string< char > (name__)),
  regulator__ ()
  {
    name_->container (this);
  }

  inline
  hostType::
  hostType (hostType const& s)
  :
  ::XSCRT::Type (),
  instance_ (s.instance_),
  name_ (new ::XMLSchema::string< char > (*s.name_)),
  regulator__ ()
  {
    name_->container (this);
  }

  inline
  hostType& hostType::
  operator= (hostType const& s)
  {
    instance_ = s.instance_;

    name (s.name ());

    return *this;
  }


  // hostType
  // 
  inline
  hostType::instance_iterator hostType::
  begin_instance ()
  {
    return instance_.begin ();
  }

  inline
  hostType::instance_iterator hostType::
  end_instance ()
  {
    return instance_.end ();
  }

  inline
  hostType::instance_const_iterator hostType::
  begin_instance () const
  {
    return instance_.begin ();
  }

  inline
  hostType::instance_const_iterator hostType::
  end_instance () const
  {
    return instance_.end ();
  }

  inline
  void hostType::
  add_instance (::XMLSchema::string< char > const& e)
  {
    instance_.push_back (e);
  }

  inline
  size_t hostType::
  count_instance(void) const
  {
    return instance_.size ();
  }

  // hostType
  // 
  inline
  ::XMLSchema::string< char > const& hostType::
  name () const
  {
    return *name_;
  }

  inline
  ::XMLSchema::string< char >& hostType::
  name ()
  {
    return *name_;
  }

  inline
  void hostType::
  name (::XMLSchema::string< char > const& e)
  {
    *name_ = e;
  }
}

