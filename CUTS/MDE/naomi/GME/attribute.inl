namespace naomi
{
  namespace attributes
  {
    // attributeType
    //

    inline
    attributeType::
    attributeType (::XMLSchema::string< char > const& owner__,
                   ::XMLSchema::string< char > const& value__)
    :
    ::XSCRT::Type (),
    owner_ (new ::XMLSchema::string< char > (owner__)),
    value_ (new ::XMLSchema::string< char > (value__)),
    regulator__ ()
    {
      owner_->container (this);
      value_->container (this);
    }

    inline
    attributeType::
    attributeType (attributeType const& s)
    :
    ::XSCRT::Type (),
    owner_ (new ::XMLSchema::string< char > (*s.owner_)),
    value_ (s.value_.get () ? new ::XMLSchema::string< char > (*s.value_) : 0),
    resource_ (s.resource_),
    units_ (s.units_.get () ? new ::XMLSchema::string< char > (*s.units_) : 0),
    documentation_ (s.documentation_.get () ? new ::XMLSchema::string< char > (*s.documentation_) : 0),
    regulator__ ()
    {
      owner_->container (this);

      if (value_.get ())
        value_->container (this);

      if (units_.get ()) units_->container (this);
      if (documentation_.get ()) documentation_->container (this);
    }

    inline
    attributeType& attributeType::
    operator= (attributeType const& s)
    {
      owner (*s.owner_);

      if (s.value_.get ())
        value (*s.value_);

      resource_ = s.resource_;

      if (s.units_.get ())
        units (*(s.units_));
      else
        units_.reset (0);

      if (s.documentation_.get ())
        documentation (*(s.documentation_));
      else
        documentation_.reset (0);

      return *this;
    }


    // attributeType
    //
    inline
    ::XMLSchema::string< char > const& attributeType::
    owner () const
    {
      return *owner_;
    }

    inline
    void attributeType::
    owner (::XMLSchema::string< char > const& e)
    {
      *owner_ = e;
    }

    // attributeType
    //
    inline
    ::XMLSchema::string< char > const& attributeType::
    value () const
    {
      if (value_.get () == 0)
        value_.reset (new ::XMLSchema::string< char > (""));

      return *value_;
    }

    inline
    void attributeType::
    value (::XMLSchema::string< char > const& e)
    {
      if (value_.get ())
        *value_ = e;
      else
        value_.reset (new ::XMLSchema::string< char > (e));
    }

    // attributeType::resourceType
    //

    inline
    attributeType::resourceType::
    resourceType (::XMLSchema::string< char > const& name__,
                  ::XMLSchema::anyURI< char > const& uri__)
    :
    name_ (new ::XMLSchema::string< char > (name__)),
    uri_ (new ::XMLSchema::anyURI< char > (uri__)),
    regulator__ ()
    {
      name_->container (this);
      uri_->container (this);
    }

    inline
    attributeType::resourceType::
    resourceType (resourceType const& s)
    :
    name_ (new ::XMLSchema::string< char > (*s.name_)),
    uri_ (new ::XMLSchema::anyURI< char > (*s.uri_)),
    checksum_ (s.checksum_.get () ? new ::XMLSchema::string< char > (*s.checksum_) : 0),
    regulator__ ()
    {
      name_->container (this);
      uri_->container (this);
      if (checksum_.get ()) checksum_->container (this);
    }

    inline
    attributeType::resourceType& attributeType::resourceType::
    operator= (resourceType const& s)
    {
      name (s.name ());

      uri (s.uri ());

      if (s.checksum_.get ()) checksum (*(s.checksum_));
      else checksum_ = ::std::auto_ptr< ::XMLSchema::string< char > > (0);

      return *this;
    }


    // attributeType::resourceType
    //
    inline
    ::XMLSchema::string< char > const& attributeType::resourceType::
    name () const
    {
      return *name_;
    }

    inline
    ::XMLSchema::string< char >& attributeType::resourceType::
    name ()
    {
      return *name_;
    }

    inline
    void attributeType::resourceType::
    name (::XMLSchema::string< char > const& e)
    {
      *name_ = e;
    }

    // attributeType::resourceType
    //
    inline
    ::XMLSchema::anyURI< char > const& attributeType::resourceType::
    uri () const
    {
      return *uri_;
    }

    inline
    ::XMLSchema::anyURI< char >& attributeType::resourceType::
    uri ()
    {
      return *uri_;
    }

    inline
    void attributeType::resourceType::
    uri (::XMLSchema::anyURI< char > const& e)
    {
      *uri_ = e;
    }

    // attributeType::resourceType
    //
    inline
    bool attributeType::resourceType::
    checksum_p () const
    {
      return checksum_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& attributeType::resourceType::
    checksum () const
    {
      return *checksum_;
    }

    inline
    ::XMLSchema::string< char >& attributeType::resourceType::
    checksum ()
    {
      return *checksum_;
    }

    inline
    void attributeType::resourceType::
    checksum (::XMLSchema::string< char > const& e)
    {
      if (checksum_.get ())
      {
        *checksum_ = e;
      }

      else
      {
        checksum_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        checksum_->container (this);
      }
    }


    // attributeType
    //
    inline
    attributeType::resource_iterator attributeType::
    begin_resource ()
    {
      return resource_.begin ();
    }

    inline
    attributeType::resource_iterator attributeType::
    end_resource ()
    {
      return resource_.end ();
    }

    inline
    attributeType::resource_const_iterator attributeType::
    begin_resource () const
    {
      return resource_.begin ();
    }

    inline
    attributeType::resource_const_iterator attributeType::
    end_resource () const
    {
      return resource_.end ();
    }

    inline
    void attributeType::
    add_resource (resourceType const& e)
    {
      resource_.push_back (e);
    }

    inline
    size_t attributeType::
    count_resource(void) const
    {
      return resource_.size ();
    }

    // attributeType
    //
    inline
    bool attributeType::
    units_p () const
    {
      return units_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& attributeType::
    units () const
    {
      return *units_;
    }

    inline
    void attributeType::
    units (::XMLSchema::string< char > const& e)
    {
      if (units_.get ())
      {
        *units_ = e;
      }

      else
      {
        units_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        units_->container (this);
      }
    }

    // attributeType
    //
    inline
    bool attributeType::
    documentation_p () const
    {
      return documentation_.get () != 0;
    }

    inline
    ::XMLSchema::string< char > const& attributeType::
    documentation () const
    {
      return *documentation_;
    }

    inline
    void attributeType::
    documentation (::XMLSchema::string< char > const& e)
    {
      if (documentation_.get ())
      {
        *documentation_ = e;
      }

      else
      {
        documentation_ = ::std::auto_ptr< ::XMLSchema::string< char > > (new ::XMLSchema::string< char > (e));
        documentation_->container (this);
      }
    }
  }
}

