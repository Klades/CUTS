// $Id$

///////////////////////////////////////////////////////////////////////////////
// @@ CUTS_Port_Summary_Base

//
// CUTS_Port_Summary_Base
//
CUTS_INLINE
CUTS_Port_Summary_Base::CUTS_Port_Summary_Base (void)
{

}

//
// CUTS_Port_Summary_Base
//
CUTS_INLINE
CUTS_Port_Summary_Base::
CUTS_Port_Summary_Base (const CUTS_Port_Summary_Base & copy)
: queuing_time_ (copy.queuing_time_),
  service_time_ (copy.service_time_),
  endpoints_ (copy.endpoints_)
{

}

//
// ~CUTS_Port_Summary_Base
//
CUTS_INLINE
CUTS_Port_Summary_Base::~CUTS_Port_Summary_Base (void)
{

}

//
// queuing_time
//
CUTS_INLINE
const CUTS_Time_Measurement &
CUTS_Port_Summary_Base::queuing_time (void) const
{
  return this->queuing_time_;
}

//
// service_time
//
CUTS_INLINE
const CUTS_Time_Measurement &
CUTS_Port_Summary_Base::service_time (void) const
{
  return this->service_time_;
}

//
// endpoints
//
CUTS_INLINE
const CUTS_Endpoint_Log_Summary &
CUTS_Port_Summary_Base::endpoints (void) const
{
  return this->endpoints_;
}

///////////////////////////////////////////////////////////////////////////////
// @@ CUTS_Port_Summary

//
// CUTS_Port_Summary
//
CUTS_INLINE
CUTS_Port_Summary::CUTS_Port_Summary (void)
{

}

//
// senders
//
CUTS_INLINE
const CUTS_Sender_Port_Summary & CUTS_Port_Summary::senders (void) const
{
  return this->ssp_;
}
