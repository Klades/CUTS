// $Id$

#if !defined (__CUTS_INLINE__)
#include "Tron_EventConsumer_T.inl"
#endif

#include "../deployment/Tron_Consumer_List_T.h"

namespace iCCM
{

//
// register_channel
//
template <typename SERVANT, typename EVENT>
void Tron_EventConsumer_T <SERVANT, EVENT>::
register_channel (Reporter * reporter,
                  const ACE_CString & name,
                  tron_consumer_map_type & tron_consumer_map)
{
  // Call base class
  Tron_EventConsumer::register_channel (reporter, name, tron_consumer_map);

  Tron_Consumer_List * consumer_list = 0;
  if (0 != tron_consumer_map.find (this->channel_, consumer_list))
  {
    // Channel is not registered with the consumer list
    consumer_list = new Tron_Consumer_List_T < EVENT > ();
    tron_consumer_map.bind (this->channel_, consumer_list);
  }

  // Add this class to the consumer map
  consumer_list->add (this);
}

//
// push_event
//
template <typename SERVANT, typename EVENT>
void Tron_EventConsumer_T <SERVANT, EVENT>::
push_event (Tron_Event * base)
{
  EVENT * ev = dynamic_cast < EVENT * > (base);

  if (0 == ev)
    throw ::Components::BadEventType ();

  (*this->servant_.*this->callback_) (ev);
}

}
