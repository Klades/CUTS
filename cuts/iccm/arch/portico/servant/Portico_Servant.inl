// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Portico_Servant
//
CUTS_INLINE
Portico_Servant::Portico_Servant (const char * name)
: Servant (name),
  federate_time_ (0.0),
  federate_lookahead_ (1.0),
  is_advancing_ (false),
  obj_discovery_ (obj_discovery_mutex_)

{

}

//
// ~Portico_Servant
//
CUTS_INLINE
Portico_Servant::~Portico_Servant (void)
{

}

//
// ambassador
//
CUTS_INLINE
RTI::RTIambassador & Portico_Servant::rti_ambassador (void)
{
  return this->rtiamb_;
}

//
// ambassador
//
CUTS_INLINE
const RTI::RTIambassador & Portico_Servant::rti_ambassador (void) const
{
  return this->rtiamb_;
}

//
// federate_time
//
CUTS_INLINE
const RTIfedTime & Portico_Servant::federate_time (void) const
{
  return this->federate_time_;
}

//
// null_ambassador
//
CUTS_INLINE
NullFederateAmbassador & Portico_Servant::null_ambassador (void)
{
  return this->nfamb_;
}

}
