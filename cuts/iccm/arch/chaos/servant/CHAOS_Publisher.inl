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
// connect
//
CUTS_INLINE
void
CHAOS_Publisher::connect (::Components::EventConsumerBase_ptr consumer)
{
  this->impl_->connect (consumer);
}

//
// disconnect
//
CUTS_INLINE
::Components::EventConsumerBase_ptr
CHAOS_Publisher::disconnect (void)
{
  return this->impl_->disconnect ();
}

//
// activate
//
CUTS_INLINE
void
CHAOS_Publisher::activate (void)
{
  this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void
CHAOS_Publisher::passivate (void)
{
  this->impl_->passivate ();
}

}
