// -*- C++ -*-
// $Id$

//
// probability
//
template <typename COMPONENT>
CUTS_INLINE
void CUTS_Periodic_Trigger_T <COMPONENT>::
init (Component_Type * component, Method_Pointer method)
{
  this->component_ = component;
  this->method_ = method;
}

//
// probability
//
template <typename COMPONENT>
CUTS_INLINE
double CUTS_Periodic_Trigger_T <COMPONENT>::probability (void) const
{
  return this->probability_;
}

//
// probability
//
template <typename COMPONENT>
CUTS_INLINE
void CUTS_Periodic_Trigger_T <COMPONENT>::probability (double p)
{
  this->probability_ = p;
}

//
// timeout
//
template <typename COMPONENT>
CUTS_INLINE
long CUTS_Periodic_Trigger_T <COMPONENT>::timeout (void) const
{
  return this->timeout_;
}

//
// timeout
//
template <typename COMPONENT>
CUTS_INLINE
void CUTS_Periodic_Trigger_T <COMPONENT>::timeout (long msec)
{
  this->timeout_ = msec;
}

//
// cancel_timeout
//
template <typename COMPONENT>
CUTS_INLINE
void CUTS_Periodic_Trigger_T <COMPONENT>::cancel_timeout (void)
{
  if (this->timer_ != -1)
  {
    this->timer_queue_.cancel (this->timer_);
    this->timer_ = -1;
  }
}
