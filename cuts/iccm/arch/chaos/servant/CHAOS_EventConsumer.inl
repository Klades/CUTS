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

CUTS_INLINE
void CHAOS_EventConsumer::
impl (iCCM::EventConsumer * impl,  ::Components::EventConsumerBase_ptr obj)
{
  this->impl_ = impl;
  this->obj_ = ::Components::EventConsumerBase::_duplicate (obj);
}

CUTS_INLINE
iCCM::EventConsumer * CHAOS_EventConsumer::impl (void)
{
  return this->impl_;
}

::Components::EventConsumerBase_ptr CHAOS_EventConsumer::get_consumer (void)
{
  return ::Components::EventConsumerBase::_duplicate (this->obj_.in ());
}

CUTS_INLINE
void CHAOS_EventConsumer::allocate (ptrdiff_t & symbol)
{

};

CUTS_INLINE
void CHAOS_EventConsumer::activate (void)
{
  if (this->impl_ != 0)
    this->impl_->activate ();
}

CUTS_INLINE
void CHAOS_EventConsumer::passivate (void)
{
  if (this->impl_ != 0)
    this->impl_->passivate ();
}

CUTS_INLINE
void CHAOS_EventConsumer::push_event (::Components::EventBase * ev)
{
  if (this->impl_ != 0)
    this->impl_->push_event (ev);
}

}
