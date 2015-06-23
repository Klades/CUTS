namespace CUTS
{
  namespace schemas
  {
    // ProcessOptions
    // 

    inline
    ProcessOptions::
    ProcessOptions (::XMLSchema::string< char > const& executable__,
                    ::XMLSchema::ID< char > const& id__)
    : 
    ::XSCRT::Type (), 
    executable_ (new ::XMLSchema::string< char > (executable__)),
    id_ (new ::XMLSchema::ID< char > (id__)),
    regulator__ ()
    {
      executable_->container (this);
      id_->container (this);
    }

    inline
    ProcessOptions::
    ProcessOptions (ProcessOptions const& s)
    :
    ::XSCRT::Type (),
    executable_ (new ::XMLSchema::string< char > (*s.executable_)),
    arguments_ (s.arguments_.get () ? new ::XMLSchema::string< char > (*s.arguments_) : 0),
    workingdirectory_ (s.workingdirectory_.get () ? new ::XMLSchema::string< char > (*s.workingdirectory_) : 0),
    output_ (s.output_.get () ? new ::XMLSchema::string< char > (*s.output_) : 0),
    error_ (s.error_.get () ? new ::XMLSchema::string< char > (*s.error_) : 0),
    id_ (new ::XMLSchema::ID< char > (*s.id_)),
    delay_ (s.delay_.get () ? new ::XMLSchema::double_ (*s.delay_) : 0),
    waitforcompletion_ (s.waitforcompletion_.get () ? new ::XMLSchema::boolean (*s.waitforcompletion_) : 0),
    regulator__ ()
    {
      executable_->container (this);
      if (arguments_.get ()) arguments_->container (this);
      if (workingdirectory_.get ()) workingdirectory_->container (this);
      if (output_.get ()) output_->container (this);
      if (error_.get ()) error_->container (this);
      id_->container (this);
      if (delay_.get ()) delay_->container (this);
      if (waitforcompletion_.get ()) waitforcompletion_->container (this);
    }

    inline
    ProcessOptions& ProcessOptions::
    operator= (ProcessOptions const& s)
    {
      if (&s != this)
      {
        executable (*s.executable_);

        if (s.arguments_.get ())
          arguments (*(s.arguments_));
        else
          arguments_.reset (0);

        if (s.workingdirectory_.get ())
          workingdirectory (*(s.workingdirectory_));
        else
          workingdirectory_.reset (0);

        if (s.output_.get ())
          output (*(s.output_));
        else
          output_.reset (0);

        if (s.error_.get ())
          error (*(s.error_));
        else
          error_.reset (0);

        id (s.id ());

        if (s.delay_.get ()) delay (*(s.delay_));
        else delay_ = ::std::auto_ptr< ::XMLSchema::double_ > (0);

        if (s.waitforcompletion_.get ()) waitforcompletion (*(s.waitforcompletion_));
        else waitforcompletion_ = ::std::auto_ptr< ::XMLSchema::boolean > (0);
      }

      return *this;
    }


    // ProcessOptions
    // 
    inline
    ::XMLSchema::string< char > const& ProcessOptions::
    executable () const
    {
      return *executable_;
    }

    inline
    void ProcessOptions::
    executable (::XMLSchema::string< char > const& e)
    {
      *executable_ = e;
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    arguments_p () const
    {
      return arguments_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& ProcessOptions::
    arguments () const
    {
      return *arguments_;
    }

    inline
    void ProcessOptions::
    arguments (::XMLSchema::string< char > const& e)
    {
      if (arguments_.get ())
      {
        *arguments_ = e;
      }

      else
      {
        arguments_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        arguments_->container (this);
      }
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    workingdirectory_p () const
    {
      return workingdirectory_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& ProcessOptions::
    workingdirectory () const
    {
      return *workingdirectory_;
    }

    inline
    void ProcessOptions::
    workingdirectory (::XMLSchema::string< char > const& e)
    {
      if (workingdirectory_.get ())
      {
        *workingdirectory_ = e;
      }

      else
      {
        workingdirectory_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        workingdirectory_->container (this);
      }
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    output_p () const
    {
      return output_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& ProcessOptions::
    output () const
    {
      return *output_;
    }

    inline
    void ProcessOptions::
    output (::XMLSchema::string< char > const& e)
    {
      if (output_.get ())
      {
        *output_ = e;
      }

      else
      {
        output_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        output_->container (this);
      }
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    error_p () const
    {
      return error_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& ProcessOptions::
    error () const
    {
      return *error_;
    }

    inline
    void ProcessOptions::
    error (::XMLSchema::string< char > const& e)
    {
      if (error_.get ())
      {
        *error_ = e;
      }

      else
      {
        error_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        error_->container (this);
      }
    }

    // ProcessOptions
    // 
    inline
    ::XMLSchema::ID< char > const& ProcessOptions::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::ID< char >& ProcessOptions::
    id ()
    {
      return *id_;
    }

    inline
    void ProcessOptions::
    id (::XMLSchema::ID< char > const& e)
    {
      *id_ = e;
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    delay_p () const
    {
      return delay_.get () != 0;
    }

    inline
    ::XMLSchema::double_ const& ProcessOptions::
    delay () const
    {
      return *delay_;
    }

    inline
    ::XMLSchema::double_& ProcessOptions::
    delay ()
    {
      return *delay_;
    }

    inline
    void ProcessOptions::
    delay (::XMLSchema::double_ const& e)
    {
      if (delay_.get ())
      {
        *delay_ = e;
      }

      else
      {
        delay_ = ::std::auto_ptr< ::XMLSchema::double_ > (new ::XMLSchema::double_ (e));
        delay_->container (this);
      }
    }

    // ProcessOptions
    // 
    inline
    bool ProcessOptions::
    waitforcompletion_p () const
    {
      return waitforcompletion_.get () != 0;
    }

    inline
    ::XMLSchema::boolean const& ProcessOptions::
    waitforcompletion () const
    {
      return *waitforcompletion_;
    }

    inline
    ::XMLSchema::boolean& ProcessOptions::
    waitforcompletion ()
    {
      return *waitforcompletion_;
    }

    inline
    void ProcessOptions::
    waitforcompletion (::XMLSchema::boolean const& e)
    {
      if (waitforcompletion_.get ())
      {
        *waitforcompletion_ = e;
      }

      else
      {
        waitforcompletion_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
        waitforcompletion_->container (this);
      }
    }


    // ProcessList
    // 

    inline
    ProcessList::
    ProcessList ()
    : 
    regulator__ ()
    {
    }

    inline
    ProcessList::
    ProcessList (ProcessList const& s)
    :
    ::XSCRT::Type (),
    process_ (s.process_),
    regulator__ ()
    {
    }

    inline
    ProcessList& ProcessList::
    operator= (ProcessList const& s)
    {
      if (&s != this)
      {
        process_ = s.process_;
      }

      return *this;
    }


    // ProcessList
    // 
    inline
    ProcessList::process_iterator ProcessList::
    begin_process ()
    {
      return process_.begin ();
    }

    inline
    ProcessList::process_iterator ProcessList::
    end_process ()
    {
      return process_.end ();
    }

    inline
    ProcessList::process_const_iterator ProcessList::
    begin_process () const
    {
      return process_.begin ();
    }

    inline
    ProcessList::process_const_iterator ProcessList::
    end_process () const
    {
      return process_.end ();
    }

    inline
    void ProcessList::
    add_process (ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::ProcessOptions, ACE_Null_Mutex >  const& e)
    {
      process_.push_back (e);
    }

    inline
    size_t ProcessList::
    count_process(void) const
    {
      return process_.size ();
    }


    // NodeConfig
    // 

    inline
    NodeConfig::
    NodeConfig ()
    : 
    regulator__ ()
    {
    }

    inline
    NodeConfig::
    NodeConfig (NodeConfig const& s)
    :
    ::XSCRT::Type (),
    environment_ (s.environment_),
    regulator__ ()
    {
    }

    inline
    NodeConfig& NodeConfig::
    operator= (NodeConfig const& s)
    {
      if (&s != this)
      {
        environment_ = s.environment_;
      }

      return *this;
    }


    // NodeConfig
    // 
    inline
    NodeConfig::environment_iterator NodeConfig::
    begin_environment ()
    {
      return environment_.begin ();
    }

    inline
    NodeConfig::environment_iterator NodeConfig::
    end_environment ()
    {
      return environment_.end ();
    }

    inline
    NodeConfig::environment_const_iterator NodeConfig::
    begin_environment () const
    {
      return environment_.begin ();
    }

    inline
    NodeConfig::environment_const_iterator NodeConfig::
    end_environment () const
    {
      return environment_.end ();
    }

    inline
    void NodeConfig::
    add_environment (ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::EnvConfig, ACE_Null_Mutex >  const& e)
    {
      environment_.push_back (e);
    }

    inline
    size_t NodeConfig::
    count_environment(void) const
    {
      return environment_.size ();
    }


    // DependsItem
    // 

    inline
    DependsItem::
    DependsItem (::XMLSchema::IDREF< char > const& id__)
    : 
    id_ (new ::XMLSchema::IDREF< char > (id__)),
    regulator__ ()
    {
      id_->container (this);
    }

    inline
    DependsItem::
    DependsItem (DependsItem const& s)
    :
    id_ (new ::XMLSchema::IDREF< char > (*s.id_)),
    regulator__ ()
    {
      id_->container (this);
    }

    inline
    DependsItem& DependsItem::
    operator= (DependsItem const& s)
    {
      if (&s != this)
      {
        id (s.id ());
      }

      return *this;
    }


    // DependsItem
    // 
    inline
    ::XMLSchema::IDREF< char > const& DependsItem::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::IDREF< char >& DependsItem::
    id ()
    {
      return *id_;
    }

    inline
    ::XSCRT::Type* DependsItem::get_id_ptr ()
    {
        std::basic_string<char> temp (id().id());
      return this->get_idref(temp.c_str());
    }


    inline
    void DependsItem::set_id_ptr (std::basic_string<ACE_TCHAR> idref)
    {
        ID_Map::TSS_ID_Map* TSS_ID_Map (ACE_Singleton<ID_Map::TSS_ID_Map, ACE_Null_Mutex>::instance());
        (*TSS_ID_Map)->resolve_single_idref(idref, this);
    }


    inline
    void DependsItem::
    id (::XMLSchema::IDREF< char > const& e)
    {
      *id_ = e;
    }


    // EnvConfig
    // 

    inline
    EnvConfig::
    EnvConfig (::XMLSchema::ID< char > const& id__)
    : 
    id_ (new ::XMLSchema::ID< char > (id__)),
    regulator__ ()
    {
      id_->container (this);
    }

    inline
    EnvConfig::
    EnvConfig (EnvConfig const& s)
    :
    ::XSCRT::Type (),
    variables_ (s.variables_.get () ? new ::CUTS::schemas::VariableList (*s.variables_) : 0),
    startup_ (s.startup_.get () ? new ::CUTS::schemas::ProcessList (*s.startup_) : 0),
    shutdown_ (s.shutdown_.get () ? new ::CUTS::schemas::ProcessList (*s.shutdown_) : 0),
    id_ (new ::XMLSchema::ID< char > (*s.id_)),
    inherit_ (s.inherit_.get () ? new ::XMLSchema::boolean (*s.inherit_) : 0),
    active_ (s.active_.get () ? new ::XMLSchema::boolean (*s.active_) : 0),
    regulator__ ()
    {
      if (variables_.get ()) variables_->container (this);
      if (startup_.get ()) startup_->container (this);
      if (shutdown_.get ()) shutdown_->container (this);
      id_->container (this);
      if (inherit_.get ()) inherit_->container (this);
      if (active_.get ()) active_->container (this);
    }

    inline
    EnvConfig& EnvConfig::
    operator= (EnvConfig const& s)
    {
      if (&s != this)
      {
        if (s.variables_.get ())
          variables (*(s.variables_));
        else
          variables_.reset (0);

        if (s.startup_.get ())
          startup (*(s.startup_));
        else
          startup_.reset (0);

        if (s.shutdown_.get ())
          shutdown (*(s.shutdown_));
        else
          shutdown_.reset (0);

        id (s.id ());

        if (s.inherit_.get ()) inherit (*(s.inherit_));
        else inherit_ = ::std::auto_ptr< ::XMLSchema::boolean > (0);

        if (s.active_.get ()) active (*(s.active_));
        else active_ = ::std::auto_ptr< ::XMLSchema::boolean > (0);
      }

      return *this;
    }


    // EnvConfig
    // 
    inline
    bool EnvConfig::
    variables_p () const
    {
      return variables_.get () != 0;
    }

    inline
    ::CUTS::schemas::VariableList const& EnvConfig::
    variables () const
    {
      return *variables_;
    }

    inline
    void EnvConfig::
    variables (::CUTS::schemas::VariableList const& e)
    {
      if (variables_.get ())
      {
        *variables_ = e;
      }

      else
      {
        variables_ = ::std::auto_ptr< ::CUTS::schemas::VariableList > (new ::CUTS::schemas::VariableList (e));
        variables_->container (this);
      }
    }

    // EnvConfig
    // 
    inline
    bool EnvConfig::
    startup_p () const
    {
      return startup_.get () != 0;
    }

    inline
    ::CUTS::schemas::ProcessList const& EnvConfig::
    startup () const
    {
      return *startup_;
    }

    inline
    void EnvConfig::
    startup (::CUTS::schemas::ProcessList const& e)
    {
      if (startup_.get ())
      {
        *startup_ = e;
      }

      else
      {
        startup_ = ::std::auto_ptr< ::CUTS::schemas::ProcessList > (new ::CUTS::schemas::ProcessList (e));
        startup_->container (this);
      }
    }

    // EnvConfig
    // 
    inline
    bool EnvConfig::
    shutdown_p () const
    {
      return shutdown_.get () != 0;
    }

    inline
    ::CUTS::schemas::ProcessList const& EnvConfig::
    shutdown () const
    {
      return *shutdown_;
    }

    inline
    void EnvConfig::
    shutdown (::CUTS::schemas::ProcessList const& e)
    {
      if (shutdown_.get ())
      {
        *shutdown_ = e;
      }

      else
      {
        shutdown_ = ::std::auto_ptr< ::CUTS::schemas::ProcessList > (new ::CUTS::schemas::ProcessList (e));
        shutdown_->container (this);
      }
    }

    // EnvConfig
    // 
    inline
    ::XMLSchema::ID< char > const& EnvConfig::
    id () const
    {
      return *id_;
    }

    inline
    ::XMLSchema::ID< char >& EnvConfig::
    id ()
    {
      return *id_;
    }

    inline
    void EnvConfig::
    id (::XMLSchema::ID< char > const& e)
    {
      *id_ = e;
    }

    // EnvConfig
    // 
    inline
    bool EnvConfig::
    inherit_p () const
    {
      return inherit_.get () != 0;
    }

    inline
    ::XMLSchema::boolean const& EnvConfig::
    inherit () const
    {
      return *inherit_;
    }

    inline
    ::XMLSchema::boolean& EnvConfig::
    inherit ()
    {
      return *inherit_;
    }

    inline
    void EnvConfig::
    inherit (::XMLSchema::boolean const& e)
    {
      if (inherit_.get ())
      {
        *inherit_ = e;
      }

      else
      {
        inherit_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
        inherit_->container (this);
      }
    }

    // EnvConfig
    // 
    inline
    bool EnvConfig::
    active_p () const
    {
      return active_.get () != 0;
    }

    inline
    ::XMLSchema::boolean const& EnvConfig::
    active () const
    {
      return *active_;
    }

    inline
    ::XMLSchema::boolean& EnvConfig::
    active ()
    {
      return *active_;
    }

    inline
    void EnvConfig::
    active (::XMLSchema::boolean const& e)
    {
      if (active_.get ())
      {
        *active_ = e;
      }

      else
      {
        active_ = ::std::auto_ptr< ::XMLSchema::boolean > (new ::XMLSchema::boolean (e));
        active_->container (this);
      }
    }


    // Variable
    // 

    inline
    Variable::
    Variable (::XMLSchema::string< char > const& name__,
              ::XMLSchema::string< char > const& value__)
    : 
    name_ (new ::XMLSchema::string< char > (name__)),
    value_ (new ::XMLSchema::string< char > (value__)),
    regulator__ ()
    {
      name_->container (this);
      value_->container (this);
    }

    inline
    Variable::
    Variable (Variable const& s)
    :
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    value_ (new ::XMLSchema::string< char > (*s.value_)),
    regulator__ ()
    {
      name_->container (this);
      value_->container (this);
    }

    inline
    Variable& Variable::
    operator= (Variable const& s)
    {
      if (&s != this)
      {
        name (s.name ());

        value (s.value ());
      }

      return *this;
    }


    // Variable
    // 
    inline
    ::XMLSchema::string< char > const& Variable::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& Variable::
    name ()
    {
      return *name_;
    }

    inline
    void Variable::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }

    // Variable
    // 
    inline
    ::XMLSchema::string< char > const& Variable::
    value () const
    {
      return *value_;
    }

    inline
    ::XMLSchema::string< char >& Variable::
    value ()
    {
      return *value_;
    }

    inline
    void Variable::
    value (::XMLSchema::string< char > const& e)
    {
      *value_ = e;
    }


    // VariableList
    // 

    inline
    VariableList::
    VariableList ()
    : 
    regulator__ ()
    {
    }

    inline
    VariableList::
    VariableList (VariableList const& s)
    :
    ::XSCRT::Type (),
    import_ (s.import_),
    variable_ (s.variable_),
    regulator__ ()
    {
    }

    inline
    VariableList& VariableList::
    operator= (VariableList const& s)
    {
      if (&s != this)
      {
        import_ = s.import_;

        variable_ = s.variable_;
      }

      return *this;
    }


    // VariableList
    // 
    inline
    VariableList::import_iterator VariableList::
    begin_import ()
    {
      return import_.begin ();
    }

    inline
    VariableList::import_iterator VariableList::
    end_import ()
    {
      return import_.end ();
    }

    inline
    VariableList::import_const_iterator VariableList::
    begin_import () const
    {
      return import_.begin ();
    }

    inline
    VariableList::import_const_iterator VariableList::
    end_import () const
    {
      return import_.end ();
    }

    inline
    void VariableList::
    add_import (ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::VariableImport, ACE_Null_Mutex >  const& e)
    {
      import_.push_back (e);
    }

    inline
    size_t VariableList::
    count_import(void) const
    {
      return import_.size ();
    }

    // VariableList
    // 
    inline
    VariableList::variable_iterator VariableList::
    begin_variable ()
    {
      return variable_.begin ();
    }

    inline
    VariableList::variable_iterator VariableList::
    end_variable ()
    {
      return variable_.end ();
    }

    inline
    VariableList::variable_const_iterator VariableList::
    begin_variable () const
    {
      return variable_.begin ();
    }

    inline
    VariableList::variable_const_iterator VariableList::
    end_variable () const
    {
      return variable_.end ();
    }

    inline
    void VariableList::
    add_variable (ACE_Refcounted_Auto_Ptr < ::CUTS::schemas::Variable, ACE_Null_Mutex >  const& e)
    {
      variable_.push_back (e);
    }

    inline
    size_t VariableList::
    count_variable(void) const
    {
      return variable_.size ();
    }


    // VariableImport
    // 

    inline
    VariableImport::
    VariableImport (::XMLSchema::anyURI< char > const& location__,
                    ::CUTS::schemas::FileType const& type__)
    : 
    location_ (new ::XMLSchema::anyURI< char > (location__)),
    type_ (new ::CUTS::schemas::FileType (type__)),
    regulator__ ()
    {
      location_->container (this);
      type_->container (this);
    }

    inline
    VariableImport::
    VariableImport (VariableImport const& s)
    :
    location_ (new ::XMLSchema::anyURI< char > (*s.location_)),
    type_ (new ::CUTS::schemas::FileType (*s.type_)),
    regulator__ ()
    {
      location_->container (this);
      type_->container (this);
    }

    inline
    VariableImport& VariableImport::
    operator= (VariableImport const& s)
    {
      if (&s != this)
      {
        location (s.location ());

        type (s.type ());
      }

      return *this;
    }


    // VariableImport
    // 
    inline
    ::XMLSchema::anyURI< char > const& VariableImport::
    location () const
    {
      return *location_;
    }

    inline
    ::XMLSchema::anyURI< char >& VariableImport::
    location ()
    {
      return *location_;
    }

    inline
    void VariableImport::
    location (::XMLSchema::anyURI< char > const& e)
    {
      *location_ = e;
    }

    // VariableImport
    // 
    inline
    ::CUTS::schemas::FileType const& VariableImport::
    type () const
    {
      return *type_;
    }

    inline
    ::CUTS::schemas::FileType& VariableImport::
    type ()
    {
      return *type_;
    }

    inline
    void VariableImport::
    type (::CUTS::schemas::FileType const& e)
    {
      *type_ = e;
    }


    // FileType
    // 

    inline
    FileType::Value FileType::
    integral () const
    {
      return v_;
    }

    inline
    bool
    operator== (::CUTS::schemas::FileType const& a, ::CUTS::schemas::FileType const& b)
    {
      return a.v_ == b.v_;
    }

    inline
    bool
    operator!= (::CUTS::schemas::FileType const& a, ::CUTS::schemas::FileType const& b)
    {
      return a.v_ != b.v_;
    }

    inline
    FileType::
    FileType (FileType::Value v)
    : v_ (v)
    {
    }
  }
}

