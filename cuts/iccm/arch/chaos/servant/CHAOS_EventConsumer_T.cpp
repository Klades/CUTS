// $Id$

#if !defined (__CUTS_INLINE__)
#include "CHAOS_EventConsumer_T.inl"
#endif

namespace iCCM
{
template <typename SERVANT, typename EVENT>
void CHAOS_EventConsumer_T <SERVANT, EVENT>::
impl (iCCM::EventConsumer * impl, ::Components::EventConsumerBase_ptr obj)
{
  // Unregister the current listener.
  if (this->impl_ != 0)
    this->impl_->listener (0);

  // Pass control to the base class.
  CHAOS_EventConsumer::impl (impl, obj);

  // Register the listener with the new implementation.
  this->impl_->listener (this);
}

template <typename SERVANT, typename EVENT>
void CHAOS_EventConsumer_T <SERVANT, EVENT>::
handle_event (::Components::EventBase * base)
{
  EVENT * ev = dynamic_cast < EVENT * > (base);

  if (0 == ev)
    throw ::Components::BadEventType ();

  if (0 != this->servant_)
    (*this->servant_.*this->callback_) (ev);
}

}
