// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Portico_EventConsumer
//
CUTS_INLINE
Portico_EventConsumer::Portico_EventConsumer (void)
: rtiamb_ (0)
{

}

//
// ~Portico_EventConsumer
//
CUTS_INLINE
Portico_EventConsumer::~Portico_EventConsumer (void)
{

}

//
// is_observed
//
CUTS_INLINE
bool Portico_EventConsumer::is_observed (RTI::ObjectHandle handle) const
{
  return 0 == this->handles_.find (handle);
}

}
