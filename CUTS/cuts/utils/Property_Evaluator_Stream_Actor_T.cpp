// $Id$

//
// append
//
template <typename IteratorT>
void CUTS_Property_Evaluator_Stream_Actor::
append (IteratorT begin, IteratorT end) const
{
  std::string str (begin, end);
  this->out_ << str;
}

//
// expand
//
template <typename IteratorT>
void CUTS_Property_Evaluator_Stream_Actor::
expand (IteratorT begin,
        IteratorT end,
        const CUTS_Property_Map & map,
        const CUTS_Property_Evaluator_Config & config) const
{
  // Store the name of the property.
  std::string name (begin, end);

  // Locate the value of the property.
  ACE_CString value;

  if (map.get (name.c_str (), value) == 0)
  {
    // Write the value of the property.
    this->out_ << value.c_str ();
  }
  else
  {
    if (config.use_env_)
    {
      // Try and locate the name in the environment variables.
      char * val = ACE_OS::getenv (name.c_str ());

      if (val != 0)
        this->out_ << val;
      else
        this->out_ << config.open_tag_.c_str ()
                    << name
                    << config.close_tag_.c_str ();
    }
    else
    {
      this->out_ << config.open_tag_.c_str ()
                  << name
                  << config.close_tag_.c_str ();
    }
  }
}
