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
  id_ (new ::XMLSchema::ID< char > (*s.id_)),
  regulator__ ()
  {
    executable_->container (this);
    if (arguments_.get ()) arguments_->container (this);
    if (workingdirectory_.get ()) workingdirectory_->container (this);
    id_->container (this);
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

    id (s.id ());

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


  // taskList
  // 

  inline
  taskList::
  taskList ()
  : 
  ::XSCRT::Type (), 
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
  ::XSCRT::Type (), 
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

