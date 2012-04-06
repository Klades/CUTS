// $Id$

#if !defined (__CUTS_INLINE__)
#include "Tron_Publisher_Table_T.inl"
#endif

#include "cuts/iccm/servant/Cookie.h"
#include "Tron_Event.h"

namespace iCCM
{

//
// allocate_event
//
template <typename EVENT>
EVENT * Tron_Publisher_Table_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // Tron architecture.
  //===========================================================================
  typedef typename Tron_Event_Traits <EVENT>::tron_event_type tron_event_type;
  return new tron_event_type ();
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
Tron_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  // Make sure this is a valid consumer.
  ::Components::Tron::EventConsumer_var consumer =
    ::Components::Tron::EventConsumer::_narrow (consumer_base);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  // Pass control to the base class.
  ::Components::Cookie_var cookie = this->base_type::subscribe (consumer_base);

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should finish the subscription process
  // for this connection. This can include getting information from the
  // consumer or sending it information.
  //===========================================================================

  return cookie._retn ();
}

//
// unsubscribe
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
Tron_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should finish the unsubscribe process
  // for this connection. This can include getting information from the
  // consumer or sending it information.
  //===========================================================================

  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer_base = this->base_type::unsubscribe (c);

  // Notify the event consumer they no longer need to observe
  // events from this publisher.
  ::Components::Tron::EventConsumer_var consumer =
    ::Components::Tron::EventConsumer::_narrow (consumer_base);

  return consumer_base;
}

//
// send_event
//
template <typename EVENT>
void Tron_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - sending event via Tron_Publisher_Table\n")));

  // Convert the CORBA event into a Tron event.
  Tron_Event * tron_event = dynamic_cast < Tron_Event *> (ev);

  if (0 != ev)
  {
    tron_event->__tron_write_attributes (this->reporter_, this->channel_);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - invalid event type\n")));
  }
}

}
