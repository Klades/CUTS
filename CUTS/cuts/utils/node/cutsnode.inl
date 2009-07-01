namespace CUTS
{
  // taskDescription
  // 

  inline
  taskDescription::
  taskDescription (::XMLSchema::string< char > const& executable__,
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
  taskDescription::
  taskDescription (taskDescription const& s)
  :
  ::XSCRT::Type (),
  executable_ (new ::XMLSchema::string< char > (*s.executable_)),
  arguments_ (s.arguments_.get () ? new ::XMLSchema::string< char > (*s.arguments_) : 0),
  workingdirectory_ (s.workingdirectory_.get () ? new ::XMLSchema::string< char > (*s.workingdirectory_) : 0),
  output_ (s.output_.get () ? new ::XMLSchema::string< char > (*s.output_) : 0),
  error_ (s.error_.get () ? new ::XMLSchema::string< char > (*s.error_) : 0),
  id_ (new ::XMLSchema::ID< char > (*s.id_)),
  delay_ (s.delay_.get () ? new ::XMLSchema::double_ (*s.delay_) : 0),
  regulator__ ()
  {
    executable_->container (this);
    if (arguments_.get ()) arguments_->container (this);
    if (workingdirectory_.get ()) workingdirectory_->container (this);
    if (output_.get ()) output_->container (this);
    if (error_.get ()) error_->container (this);
    id_->container (this);
    if (delay_.get ()) delay_->container (this);
  }

  inline
  taskDescription& taskDescription::
  operator= (taskDescription const& s)
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

    return *this;
  }


  // taskDescription
  // 
  inline
  ::XMLSchema::string< char > const& taskDescription::
  executable () const
  {
    return *executable_;
  }

  inline
  void taskDescription::
  executable (::XMLSchema::string< char > const& e)
  {
    *executable_ = e;
  }

  // taskDescription
  // 
  inline
  bool taskDescription::
  arguments_p () const
  {
    return arguments_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& taskDescription::
  arguments () const
  {
    return *arguments_;
  }

  inline
  void taskDescription::
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

  // taskDescription
  // 
  inline
  bool taskDescription::
  workingdirectory_p () const
  {
    return workingdirectory_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& taskDescription::
  workingdirectory () const
  {
    return *workingdirectory_;
  }

  inline
  void taskDescription::
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

  // taskDescription
  // 
  inline
  bool taskDescription::
  output_p () const
  {
    return output_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& taskDescription::
  output () const
  {
    return *output_;
  }

  inline
  void taskDescription::
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

  // taskDescription
  // 
  inline
  bool taskDescription::
  error_p () const
  {
    return error_.get () != 0;
  }

  inline
  ::XMLSchema::string< char > const& taskDescription::
  error () const
  {
    return *error_;
  }

  inline
  void taskDescription::
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

  // taskDescription
  // 
  inline
  ::XMLSchema::ID< char > const& taskDescription::
  id () const
  {
    return *id_;
  }

  inline
  ::XMLSchema::ID< char >& taskDescription::
  id ()
  {
    return *id_;
  }

  inline
  void taskDescription::
  id (::XMLSchema::ID< char > const& e)
  {
    *id_ = e;
  }

  // taskDescription
  // 
  inline
  bool taskDescription::
  delay_p () const
  {
    return delay_.get () != 0;
  }

  inline
  ::XMLSchema::double_ const& taskDescription::
  delay () const
  {
    return *delay_;
  }

  inline
  ::XMLSchema::double_& taskDescription::
  delay ()
  {
    return *delay_;
  }

  inline
  void taskDescription::
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


  // taskList
  // 

  inline
  taskList::
  taskList ()
  : 
  regulator__ ()
  {
  }

  inline
  taskList::
  taskList (taskList const& s)
  :
  ::XSCRT::Type (),
  task_ (s.task_),
  regulator__ ()
  {
  }

  inline
  taskList& taskList::
  operator= (taskList const& s)
  {
    task_ = s.task_;

    return *this;
  }


  // taskList
  // 
  inline
  taskList::task_iterator taskList::
  begin_task ()
  {
    return task_.begin ();
  }

  inline
  taskList::task_iterator taskList::
  end_task ()
  {
    return task_.end ();
  }

  inline
  taskList::task_const_iterator taskList::
  begin_task () const
  {
    return task_.begin ();
  }

  inline
  taskList::task_const_iterator taskList::
  end_task () const
  {
    return task_.end ();
  }

  inline
  void taskList::
  add_task (::CUTS::taskDescription const& e)
  {
    task_.push_back (e);
  }

  inline
  size_t taskList::
  count_task(void) const
  {
    return task_.size ();
  }


  // nodeConfig
  // 

  inline
  nodeConfig::
  nodeConfig ()
  : 
  regulator__ ()
  {
  }

  inline
  nodeConfig::
  nodeConfig (nodeConfig const& s)
  :
  ::XSCRT::Type (),
  tasklist_ (s.tasklist_.get () ? new ::CUTS::taskList (*s.tasklist_) : 0),
  regulator__ ()
  {
    if (tasklist_.get ()) tasklist_->container (this);
  }

  inline
  nodeConfig& nodeConfig::
  operator= (nodeConfig const& s)
  {
    if (s.tasklist_.get ())
      tasklist (*(s.tasklist_));
    else
      tasklist_.reset (0);

    return *this;
  }


  // nodeConfig
  // 
  inline
  bool nodeConfig::
  tasklist_p () const
  {
    return tasklist_.get () != 0;
  }

  inline
  ::CUTS::taskList const& nodeConfig::
  tasklist () const
  {
    return *tasklist_;
  }

  inline
  void nodeConfig::
  tasklist (::CUTS::taskList const& e)
  {
    if (tasklist_.get ())
    {
      *tasklist_ = e;
    }

    else
    {
      tasklist_ = ::std::auto_ptr< ::CUTS::taskList > (new ::CUTS::taskList (e));
      tasklist_->container (this);
    }
  }
}

