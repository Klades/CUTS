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
// subscribe
//
CUTS_INLINE
::Components::Cookie *
CHAOS_Publisher_Table::subscribe (::Components::EventConsumerBase_ptr consumer)
{
  return this->impl_->subscribe (consumer);
}

//
// unsubscribe
//
CUTS_INLINE
::Components::EventConsumerBase_ptr
CHAOS_Publisher_Table::unsubscribe (::Components::Cookie * c)
{
  return this->impl_->unsubscribe (c);
}

//
// activate
//
CUTS_INLINE
void
CHAOS_Publisher_Table::activate (void)
{
  this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void
CHAOS_Publisher_Table::passivate (void)
{
  this->impl_->passivate ();
}

//
// send_event
//
CUTS_INLINE
void
CHAOS_Publisher_Table::send_event (::Components::EventBase * ev)
{
  this->impl_->send_event (ev);
}

//
// allocate_event
//
CUTS_INLINE
::Components::EventBase *
CHAOS_Publisher_Table::allocate_event (void)
{
  return this->impl_->allocate_event ();
}

}
