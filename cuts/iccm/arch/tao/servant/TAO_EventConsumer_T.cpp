// $Id$

#if !defined (__CUTS_INLINE__)
#include "TAO_EventConsumer_T.inl"
#endif

namespace iCCM
{

//
// push_event
//
template <typename SERVANT, typename EVENT>
void TAO_EventConsumer_T <SERVANT, EVENT>::
push_event (::Components::EventBase * base)
{
  EVENT * ev = dynamic_cast < EVENT * > (base);

  if (0 == ev)
    throw ::Components::BadEventType ();

  this->push_event (ev);

  // Pass control to the base class.
  TAO_EventConsumer::push_event (ev);
}

}
