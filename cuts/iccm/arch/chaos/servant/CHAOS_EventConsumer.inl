// -*- C++ -*-
// $IdCHAOS_CCM_EventConsumer.inl 2687 2009-06-02 21:20:04Z hillj $

namespace iCCM
{

//
// CHAOS_EventConsumer
//
CUTS_INLINE
CHAOS_EventConsumer::CHAOS_EventConsumer (void)
: impl_ (0)
{

}

//
// ~CHAOS_EventConsumer
//
CUTS_INLINE
CHAOS_EventConsumer::~CHAOS_EventConsumer (void)
{

}

//
// impl
//
CUTS_INLINE
void CHAOS_EventConsumer::impl (iCCM::EventConsumer * impl)
{
  this->impl_ = impl;
}

//
// activate
//
CUTS_INLINE
void CHAOS_EventConsumer::activate (void)
{
  if (this->impl_ != 0)
    this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void CHAOS_EventConsumer::passivate (void)
{
  if (this->impl_ != 0)
    this->impl_->passivate ();
}

//
// push_event
//
CUTS_INLINE
void CHAOS_EventConsumer::push_event (::Components::EventBase * ev)
{
  if (this->impl_ != 0)
    this->impl_->push_event (ev);
}

}
