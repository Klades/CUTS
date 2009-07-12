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
    location (*s.location_);

    entryPoint (*s.entryPoint_);

    if (s.params_.get ())
      params (*(s.params_));
    else
      params_.reset (0);

    id (s.id ());

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
  shutdown_ (s.shutdown_.get () ? new ::CUTS::processOptions (*s.shutdown_) : 0),
  services_ (s.services_.get () ? new ::CUTS::serviceList (*s.services_) : 0),
  regulator__ ()
  {
    if (startup_.get ()) startup_->container (this);
    if (shutdown_.get ()) shutdown_->container (this);
    if (services_.get ()) services_->container (this);
  }

  inline
  testFile& testFile::
  operator= (testFile const& s)
  {
    if (s.startup_.get ())
      startup (*(s.startup_));
    else
      startup_.reset (0);

    if (s.shutdown_.get ())
      shutdown (*(s.shutdown_));
    else
      shutdown_.reset (0);

    if (s.services_.get ())
      services (*(s.services_));
    else
      services_.reset (0);

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
}

