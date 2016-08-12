// -*- C++ -*-
// $Id$

namespace iCCM
{

CUTS_INLINE
EventConsumer_Listener::EventConsumer_Listener (void)
{

}

CUTS_INLINE
EventConsumer_Listener::~EventConsumer_Listener (void)
{

}

CUTS_INLINE
EventConsumer::EventConsumer (void)
{

}

CUTS_INLINE
EventConsumer::~EventConsumer (void)
{
}

CUTS_INLINE
void EventConsumer::push_event (Components::EventBase * ev)
{
  if (0 != this->listener_)
    this->listener_->handle_event (ev);
}

CUTS_INLINE
void
EventConsumer::activate (void)
{

}

CUTS_INLINE
void
EventConsumer::passivate (void)
{

}

CUTS_INLINE
void EventConsumer::configure_task (PortProperties props)
{
  
}

CUTS_INLINE
void EventConsumer::listener (EventConsumer_Listener * listener)
{
  this->listener_ = listener;
}

}
