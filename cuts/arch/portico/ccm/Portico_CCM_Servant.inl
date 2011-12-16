// -*- C++ -*-
// $Id$

//
// Portico_CCM_Servant
//
CUTS_INLINE
Portico_CCM_Servant::Portico_CCM_Servant (const char * name)
: CUTS_CCM_Servant (name),
  federate_time_ (0.0),
  federate_lookahead_ (1.0),
  is_advancing_ (false),
  obj_discovery_ (obj_discovery_mutex_)
{

}

//
// ~Portico_CCM_Servant
//
CUTS_INLINE
Portico_CCM_Servant::~Portico_CCM_Servant (void)
{

}

//
// ambassador
//
CUTS_INLINE
RTI::RTIambassador & Portico_CCM_Servant::rti_ambassador (void)
{
  return this->rtiamb_;
}

//
// ambassador
//
CUTS_INLINE
const RTI::RTIambassador & Portico_CCM_Servant::rti_ambassador (void) const
{
  return this->rtiamb_;
}

//
// federate_time
//
CUTS_INLINE
const RTIfedTime & Portico_CCM_Servant::federate_time (void) const
{
  return this->federate_time_;
}
