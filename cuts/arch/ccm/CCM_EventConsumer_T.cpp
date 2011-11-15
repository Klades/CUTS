// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_EventConsumer_T.inl"
#endif

//
// push_event
//
template <typename T, typename SERVANT>
void CUTS_CCM_EventConsumer_T <T, SERVANT>::
push_event (::Components::EventBase * base)
{
  T * ev = T::_downcast (base);
  if (0 == ev)
    throw ::Components::BadEventType ();

  this->push_event (ev);
}
