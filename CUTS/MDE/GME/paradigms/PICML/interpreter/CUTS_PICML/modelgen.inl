namespace CUTS
{
  // Generator_Description
  // 

  inline
  Generator_Description::
  Generator_Description (::XMLSchema::string< char > const& location__,
                         ::XMLSchema::ID< char > const& id__)
  : 
  ::XSCRT::Type (), 
  location_ (new ::XMLSchema::string< char > (location__)),
  id_ (new ::XMLSchema::ID< char > (id__)),
  regulator__ ()
  {
    location_->container (this);
    id_->container (this);
  }

  inline
  Generator_Description::
  Generator_Description (Generator_Description const& s)
  :
  ::XSCRT::Type (),
  location_ (new ::XMLSchema::string< char > (*s.location_)),
  id_ (new ::XMLSchema::ID< char > (*s.id_)),
  regulator__ ()
  {
    location_->container (this);
    id_->container (this);
  }

  inline
  Generator_Description& Generator_Description::
  operator= (Generator_Description const& s)
  {
    location (*s.location_);

    id (s.id ());

    return *this;
  }


  // Generator_Description
  // 
  inline
  ::XMLSchema::string< char > const& Generator_Description::
  location () const
  {
    return *location_;
  }

  inline
  void Generator_Description::
  location (::XMLSchema::string< char > const& e)
  {
    *location_ = e;
  }

  // Generator_Description
  // 
  inline
  ::XMLSchema::ID< char > const& Generator_Description::
  id () const
  {
    return *id_;
  }

  inline
  ::XMLSchema::ID< char >& Generator_Description::
  id ()
  {
    return *id_;
  }

  inline
  void Generator_Description::
  id (::XMLSchema::ID< char > const& e)
  {
    *id_ = e;
  }


  // Configuration
  // 

  inline
  Configuration::
  Configuration ()
  : 
  regulator__ ()
  {
  }

  inline
  Configuration::
  Configuration (Configuration const& s)
  :
  ::XSCRT::Type (),
  backend_ (s.backend_.get () ? new ::CUTS::Generators (*s.backend_) : 0),
  regulator__ ()
  {
    if (backend_.get ()) backend_->container (this);
  }

  inline
  Configuration& Configuration::
  operator= (Configuration const& s)
  {
    if (s.backend_.get ())
      backend (*(s.backend_));
    else
      backend_.reset (0);

    return *this;
  }


  // Configuration
  // 
  inline
  bool Configuration::
  backend_p () const
  {
    return backend_.get () != 0;
  }

  inline
  ::CUTS::Generators const& Configuration::
  backend () const
  {
    return *backend_;
  }

  inline
  void Configuration::
  backend (::CUTS::Generators const& e)
  {
    if (backend_.get ())
    {
      *backend_ = e;
    }

    else
    {
      backend_ = ::std::auto_ptr< ::CUTS::Generators > (new ::CUTS::Generators (e));
      backend_->container (this);
    }
  }


  // Generators
  // 

  inline
  Generators::
  Generators ()
  : 
  regulator__ ()
  {
  }

  inline
  Generators::
  Generators (Generators const& s)
  :
  ::XSCRT::Type (),
  generator_ (s.generator_),
  regulator__ ()
  {
  }

  inline
  Generators& Generators::
  operator= (Generators const& s)
  {
    generator_ = s.generator_;

    return *this;
  }


  // Generators
  // 
  inline
  Generators::generator_iterator Generators::
  begin_generator ()
  {
    return generator_.begin ();
  }

  inline
  Generators::generator_iterator Generators::
  end_generator ()
  {
    return generator_.end ();
  }

  inline
  Generators::generator_const_iterator Generators::
  begin_generator () const
  {
    return generator_.begin ();
  }

  inline
  Generators::generator_const_iterator Generators::
  end_generator () const
  {
    return generator_.end ();
  }

  inline
  void Generators::
  add_generator (ACE_Refcounted_Auto_Ptr < ::CUTS::Generator_Description, ACE_Null_Mutex >  const& e)
  {
    generator_.push_back (e);
  }

  inline
  size_t Generators::
  count_generator(void) const
  {
    return generator_.size ();
  }
}

