// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_EventConsumer_T.inl"
#endif

//
// push_event
//
template <typename T, typename SERVANT>
void CUTS_CCM_EventConsumer_T <T, SERVANT>::
push_event (::Components::EventBase *ev)
{
  T * event = T::_downcast (ev);

  if (0 != event)
  {
    this->push_event (event);
    return;
  }

  throw ::Components::BadEventType ();
}
