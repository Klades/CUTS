namespace CUTS
{
  // loggingClients
  // 

  inline
  loggingClients::
  loggingClients ()
  : 
  ::XSCRT::Type (), 
  regulator__ ()
  {
  }

  inline
  loggingClients::
  loggingClients (loggingClients const& s)
  :
  ::XSCRT::Type (),
  client_ (s.client_),
  regulator__ ()
  {
  }

  inline
  loggingClients& loggingClients::
  operator= (loggingClients const& s)
  {
    client_ = s.client_;

    return *this;
  }


  // loggingClients
  // 
  inline
  loggingClients::client_iterator loggingClients::
  begin_client ()
  {
    return client_.begin ();
  }

  inline
  loggingClients::client_iterator loggingClients::
  end_client ()
  {
    return client_.end ();
  }

  inline
  loggingClients::client_const_iterator loggingClients::
  begin_client () const
  {
    return client_.begin ();
  }

  inline
  loggingClients::client_const_iterator loggingClients::
  end_client () const
  {
    return client_.end ();
  }

  inline
  void loggingClients::
  add_client (::XMLSchema::string< char > const& e)
  {
    client_.push_back (e);
  }

  inline
  size_t loggingClients::
  count_client(void) const
  {
    return client_.size ();
  }
}

