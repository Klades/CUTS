namespace CUTS
{
  // serviceDescription
  // 

  inline
  serviceDescription::
  serviceDescription (::XMLSchema::string< char > const& location__,
                      ::XMLSchema::string< char > const& entryPoint__,
                      ::XMLSchema::ID< char > const& id__)
  : 
  ::XSCRT::Type (), 
  location_ (new ::XMLSchema::string< char > (location__)),
  entryPoint_ (new ::XMLSchema::string< char > (entryPoint__)),
  id_ (new ::XMLSchema::ID< char > (id__)),
  regulator__ ()
  {
    location_->container (this);
    entryPoint_->container (this);
    id_->container (this);
  }

  inline
  serviceDescription::
  serviceDescription (serviceDescription const& s)
  :
  ::XSCRT::Type (),
  location_ (new ::XMLSchema::string< char > (*s.location_)),
  entryPoint_ (new ::XMLSchema::string< char > (*s.entryPoint_)),
  params_ (s.params_.get () ? new ::XMLSchema::string< char > (*s.params_) : 0),
  id_ (new ::XMLSchema::ID< char > (*s.id_)),
  regulator__ ()
  {
    location_->container (this);
    entryPoint_->container (this);
    if (params_.get ()) params_->container (this);
    id_->container (this);
  }

  inline
  serviceDescription& serviceDescription::
  operator= (serviceDescription const& s)
  {
    if (&s != this)
    {
      location (*s.location_);

      entryPoint (*s.entryPoint_);

      if (s.params_.get ())
        params (*(s.params_));
      else
        params_.reset (0);

      id (s.id ());
    }

    return *this;
  }


  // serviceDescription
  // 
  inline
  ::XMLSchema::string< char > const& serviceDescription::
  location () const
  {
    return *location_;
  }

  inline
  void serviceDescription::
  location (::XMLSchema::string< char > const& e)
  {
    *location_ = e;
  }

  // serviceDescription
  // 
  inline
  ::XMLSchema::string< char > const& serviceDescription::
  entryPoint () const
  {
    return *entryPoint_;
  }

  inline
  void serviceDescription::
  entryPoint (::XMLSchema::string< char > const& e)
  {
    *entryPoint_ = e;
  }

  // serviceDescription
  // 
  inline
  bool serviceDescription::
  params_p () const
  {
    return params_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& serviceDescription::
  params () const
  {
    return *params_;
  }

  inline
  void serviceDescription::
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

  // serviceDescription
  // 
  inline
  ::XMLSchema::ID< char > const& serviceDescription::
  id () const
  {
    return *id_;
  }

  inline
  ::XMLSchema::ID< char >& serviceDescription::
  id ()
  {
    return *id_;
  }

  inline
  void serviceDescription::
  id (::XMLSchema::ID< char > const& e)
  {
    *id_ = e;
  }


  // serviceList
  // 

  inline
  serviceList::
  serviceList ()
  : 
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
    if (&s != this)
    {
      service_ = s.service_;
    }

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
  add_service (ACE_Refcounted_Auto_Ptr < ::CUTS::serviceDescription, ACE_Null_Mutex >  const& e)
  {
    service_.push_back (e);
  }

  inline
  size_t serviceList::
  count_service(void) const
  {
    return service_.size ();
  }


  // testFile
  // 

  inline
  testFile::
  testFile ()
  : 
  regulator__ ()
  {
  }

  inline
  testFile::
  testFile (testFile const& s)
  :
  ::XSCRT::Type (),
  startup_ (s.startup_.get () ? new ::CUTS::processOptions (*s.startup_) : 0),
  testops_ (s.testops_.get () ? new ::CUTS::CommandList (*s.testops_) : 0),
  shutdown_ (s.shutdown_.get () ? new ::CUTS::processOptions (*s.shutdown_) : 0),
  services_ (s.services_.get () ? new ::CUTS::serviceList (*s.services_) : 0),
  regulator__ ()
  {
    if (startup_.get ()) startup_->container (this);
    if (testops_.get ()) testops_->container (this);
    if (shutdown_.get ()) shutdown_->container (this);
    if (services_.get ()) services_->container (this);
  }

  inline
  testFile& testFile::
  operator= (testFile const& s)
  {
    if (&s != this)
    {
      if (s.startup_.get ())
        startup (*(s.startup_));
      else
        startup_.reset (0);

      if (s.testops_.get ())
        testops (*(s.testops_));
      else
        testops_.reset (0);

      if (s.shutdown_.get ())
        shutdown (*(s.shutdown_));
      else
        shutdown_.reset (0);

      if (s.services_.get ())
        services (*(s.services_));
      else
        services_.reset (0);
    }

    return *this;
  }


  // testFile
  // 
  inline
  bool testFile::
  startup_p () const
  {
    return startup_.get () != 0;
  }

  inline
  ::CUTS::processOptions const& testFile::
  startup () const
  {
    return *startup_;
  }

  inline
  void testFile::
  startup (::CUTS::processOptions const& e)
  {
    if (startup_.get ())
    {
      *startup_ = e;
    }

    else
    {
      startup_ = ::std::auto_ptr< ::CUTS::processOptions > (new ::CUTS::processOptions (e));
      startup_->container (this);
    }
  }

  // testFile
  // 
  inline
  bool testFile::
  testops_p () const
  {
    return testops_.get () != 0;
  }

  inline
  ::CUTS::CommandList const& testFile::
  testops () const
  {
    return *testops_;
  }

  inline
  void testFile::
  testops (::CUTS::CommandList const& e)
  {
    if (testops_.get ())
    {
      *testops_ = e;
    }

    else
    {
      testops_ = ::std::auto_ptr< ::CUTS::CommandList > (new ::CUTS::CommandList (e));
      testops_->container (this);
    }
  }

  // testFile
  // 
  inline
  bool testFile::
  shutdown_p () const
  {
    return shutdown_.get () != 0;
  }

  inline
  ::CUTS::processOptions const& testFile::
  shutdown () const
  {
    return *shutdown_;
  }

  inline
  void testFile::
  shutdown (::CUTS::processOptions const& e)
  {
    if (shutdown_.get ())
    {
      *shutdown_ = e;
    }

    else
    {
      shutdown_ = ::std::auto_ptr< ::CUTS::processOptions > (new ::CUTS::processOptions (e));
      shutdown_->container (this);
    }
  }

  // testFile
  // 
  inline
  bool testFile::
  services_p () const
  {
    return services_.get () != 0;
  }

  inline
  ::CUTS::serviceList const& testFile::
  services () const
  {
    return *services_;
  }

  inline
  void testFile::
  services (::CUTS::serviceList const& e)
  {
    if (services_.get ())
    {
      *services_ = e;
    }

    else
    {
      services_ = ::std::auto_ptr< ::CUTS::serviceList > (new ::CUTS::serviceList (e));
      services_->container (this);
    }
  }


  // processOptions
  // 

  inline
  processOptions::
  processOptions (::XMLSchema::string< char > const& executable__)
  : 
  executable_ (new ::XMLSchema::string< char > (executable__)),
  regulator__ ()
  {
    executable_->container (this);
  }

  inline
  processOptions::
  processOptions (processOptions const& s)
  :
  ::XSCRT::Type (),
  executable_ (new ::XMLSchema::string< char > (*s.executable_)),
  arguments_ (s.arguments_.get () ? new ::XMLSchema::string< char > (*s.arguments_) : 0),
  workingdirectory_ (s.workingdirectory_.get () ? new ::XMLSchema::string< char > (*s.workingdirectory_) : 0),
  output_ (s.output_.get () ? new ::XMLSchema::string< char > (*s.output_) : 0),
  error_ (s.error_.get () ? new ::XMLSchema::string< char > (*s.error_) : 0),
  regulator__ ()
  {
    executable_->container (this);
    if (arguments_.get ()) arguments_->container (this);
    if (workingdirectory_.get ()) workingdirectory_->container (this);
    if (output_.get ()) output_->container (this);
    if (error_.get ()) error_->container (this);
  }

  inline
  processOptions& processOptions::
  operator= (processOptions const& s)
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
    }

    return *this;
  }


  // processOptions
  // 
  inline
  ::XMLSchema::string< char > const& processOptions::
  executable () const
  {
    return *executable_;
  }

  inline
  void processOptions::
  executable (::XMLSchema::string< char > const& e)
  {
    *executable_ = e;
  }

  // processOptions
  // 
  inline
  bool processOptions::
  arguments_p () const
  {
    return arguments_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& processOptions::
  arguments () const
  {
    return *arguments_;
  }

  inline
  void processOptions::
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

  // processOptions
  // 
  inline
  bool processOptions::
  workingdirectory_p () const
  {
    return workingdirectory_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& processOptions::
  workingdirectory () const
  {
    return *workingdirectory_;
  }

  inline
  void processOptions::
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

  // processOptions
  // 
  inline
  bool processOptions::
  output_p () const
  {
    return output_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& processOptions::
  output () const
  {
    return *output_;
  }

  inline
  void processOptions::
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

  // processOptions
  // 
  inline
  bool processOptions::
  error_p () const
  {
    return error_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& processOptions::
  error () const
  {
    return *error_;
  }

  inline
  void processOptions::
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


  // CommandOptions
  // 

  inline
  CommandOptions::
  CommandOptions (::XMLSchema::string< char > const& executable__,
                  ::XMLSchema::ID< char > const& id__)
  : 
  executable_ (new ::XMLSchema::string< char > (executable__)),
  id_ (new ::XMLSchema::ID< char > (id__)),
  regulator__ ()
  {
    executable_->container (this);
    id_->container (this);
  }

  inline
  CommandOptions::
  CommandOptions (CommandOptions const& s)
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
  CommandOptions& CommandOptions::
  operator= (CommandOptions const& s)
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


  // CommandOptions
  // 
  inline
  ::XMLSchema::string< char > const& CommandOptions::
  executable () const
  {
    return *executable_;
  }

  inline
  void CommandOptions::
  executable (::XMLSchema::string< char > const& e)
  {
    *executable_ = e;
  }

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  arguments_p () const
  {
    return arguments_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& CommandOptions::
  arguments () const
  {
    return *arguments_;
  }

  inline
  void CommandOptions::
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

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  workingdirectory_p () const
  {
    return workingdirectory_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& CommandOptions::
  workingdirectory () const
  {
    return *workingdirectory_;
  }

  inline
  void CommandOptions::
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

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  output_p () const
  {
    return output_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& CommandOptions::
  output () const
  {
    return *output_;
  }

  inline
  void CommandOptions::
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

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  error_p () const
  {
    return error_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& CommandOptions::
  error () const
  {
    return *error_;
  }

  inline
  void CommandOptions::
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

  // CommandOptions
  // 
  inline
  ::XMLSchema::ID< char > const& CommandOptions::
  id () const
  {
    return *id_;
  }

  inline
  ::XMLSchema::ID< char >& CommandOptions::
  id ()
  {
    return *id_;
  }

  inline
  void CommandOptions::
  id (::XMLSchema::ID< char > const& e)
  {
    *id_ = e;
  }

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  delay_p () const
  {
    return delay_.get () != 0;
  }

  inline
  ::XMLSchema::double_ const& CommandOptions::
  delay () const
  {
    return *delay_;
  }

  inline
  ::XMLSchema::double_& CommandOptions::
  delay ()
  {
    return *delay_;
  }

  inline
  void CommandOptions::
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

  // CommandOptions
  // 
  inline
  bool CommandOptions::
  waitforcompletion_p () const
  {
    return waitforcompletion_.get () != 0;
  }

  inline
  ::XMLSchema::boolean const& CommandOptions::
  waitforcompletion () const
  {
    return *waitforcompletion_;
  }

  inline
  ::XMLSchema::boolean& CommandOptions::
  waitforcompletion ()
  {
    return *waitforcompletion_;
  }

  inline
  void CommandOptions::
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


  // CommandList
  // 

  inline
  CommandList::
  CommandList ()
  : 
  regulator__ ()
  {
  }

  inline
  CommandList::
  CommandList (CommandList const& s)
  :
  ::XSCRT::Type (),
  command_ (s.command_),
  regulator__ ()
  {
  }

  inline
  CommandList& CommandList::
  operator= (CommandList const& s)
  {
    if (&s != this)
    {
      command_ = s.command_;
    }

    return *this;
  }


  // CommandList
  // 
  inline
  CommandList::command_iterator CommandList::
  begin_command ()
  {
    return command_.begin ();
  }

  inline
  CommandList::command_iterator CommandList::
  end_command ()
  {
    return command_.end ();
  }

  inline
  CommandList::command_const_iterator CommandList::
  begin_command () const
  {
    return command_.begin ();
  }

  inline
  CommandList::command_const_iterator CommandList::
  end_command () const
  {
    return command_.end ();
  }

  inline
  void CommandList::
  add_command (ACE_Refcounted_Auto_Ptr < ::CUTS::CommandOptions, ACE_Null_Mutex >  const& e)
  {
    command_.push_back (e);
  }

  inline
  size_t CommandList::
  count_command(void) const
  {
    return command_.size ();
  }
}

