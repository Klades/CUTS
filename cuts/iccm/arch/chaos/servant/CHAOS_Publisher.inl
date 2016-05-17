// -*- C++ -*-
// $IdCHAOS_Publisher.inl 3086 2011-01-22 05:53:51Z hillj $

namespace iCCM
{

//
// CHAOS_Publisher
//
CUTS_INLINE
CHAOS_Publisher::CHAOS_Publisher (void)
: impl_ (0)
{

}

//
// ~CHAOS_Publisher
//
CUTS_INLINE
CHAOS_Publisher::~CHAOS_Publisher (void)
{

}

//
// impl
//
CUTS_INLINE
void
CHAOS_Publisher::impl (Publisher * publisher)
{
  this->impl_ = publisher;
}

//
// disconnect
//
CUTS_INLINE
::Components::EventConsumerBase_ptr
CHAOS_Publisher::disconnect (void)
{
  if (this->impl_ != 0)
    return this->impl_->disconnect ();

  return 0;
}

//
// activate
//
CUTS_INLINE
void
CHAOS_Publisher::activate (void)
{
  if (this->impl_ != 0)
    this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void
CHAOS_Publisher::passivate (void)
{
  if (this->impl_ != 0)
    this->impl_->passivate ();
}

//
// send_event
//
CUTS_INLINE
void
CHAOS_Publisher::send_event (::Components::EventBase * ev)
{
  if (this->impl_ != 0)
    this->impl_->send_event (ev);
}

//
// allocate_event
//
CUTS_INLINE
::Components::EventBase *
CHAOS_Publisher::allocate_event (void)
{
  if (this->impl_ != 0)
    return this->impl_->allocate_event ();

  return 0;
}

}
