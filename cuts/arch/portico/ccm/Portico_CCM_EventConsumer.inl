// -*- C++ -*-
// Id: CCM_EventConsumer.inl.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_CCM_EventConsumer.inl 2687 2009-06-02 21:20:04Z hillj

//
// Portico_CCM_EventConsumer
//
CUTS_INLINE
Portico_CCM_EventConsumer::Portico_CCM_EventConsumer (void)
: rtiamb_ (0)
{

}

//
// ~Portico_CCM_EventConsumer
//
CUTS_INLINE
Portico_CCM_EventConsumer::~Portico_CCM_EventConsumer (void)
{

}

//
// is_observed
//
CUTS_INLINE
bool Portico_CCM_EventConsumer::is_observed (RTI::ObjectHandle handle) const
{
  return 0 == this->handles_.find (handle);
}
