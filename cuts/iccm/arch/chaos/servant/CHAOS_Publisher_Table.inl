// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// CHAOS_Publisher_Table
//
CUTS_INLINE
CHAOS_Publisher_Table::CHAOS_Publisher_Table (void)
: impl_ (0)
{

}

//
// ~CHAOS_Publisher_Table
//
CUTS_INLINE
CHAOS_Publisher_Table::~CHAOS_Publisher_Table (void)
{

}

//
// impl
//
CUTS_INLINE
void CHAOS_Publisher_Table::impl (Publisher_Table * impl)
{
  this->impl_ = impl;
}

//
// subscribe
//
CUTS_INLINE
::Components::Cookie *
CHAOS_Publisher_Table::subscribe (::Components::EventConsumerBase_ptr consumer)
{
  if (this->impl_ != 0)
    return this->impl_->subscribe (consumer);

  return 0;
}

//
// unsubscribe
//
CUTS_INLINE
::Components::EventConsumerBase_ptr
CHAOS_Publisher_Table::unsubscribe (::Components::Cookie * c)
{
  if (this->impl_ != 0)
    return this->impl_->unsubscribe (c);

  return 0;
}

//
// activate
//
CUTS_INLINE
void
CHAOS_Publisher_Table::activate (void)
{
  if (this->impl_ != 0)
    this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void
CHAOS_Publisher_Table::passivate (void)
{
  if (this->impl_ != 0)
    this->impl_->passivate ();
}

//
// send_event
//
CUTS_INLINE
void
CHAOS_Publisher_Table::send_event (::Components::EventBase * ev)
{
  if (this->impl_ != 0)
    this->impl_->send_event (ev);
}

//
// allocate_event
//
CUTS_INLINE
::Components::EventBase *
CHAOS_Publisher_Table::allocate_event (void)
{
  if (this->impl_ != 0)
    return this->impl_->allocate_event ();
  return 0;
}

}
