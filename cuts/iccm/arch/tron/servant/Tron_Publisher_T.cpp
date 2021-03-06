// $Id$

#if !defined (__CUTS_INLINE__)
#include "Tron_Publisher_T.inl"
#endif

#include "Tron_Event.h"

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void Tron_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  ::Components::Tron::EventConsumer_var consumer =
      ::Components::Tron::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should use the <consumer> object
  // to extract information for establishing a connection and sending
  // data to this consumer event point via Tron architecture.
  //===========================================================================

  // Pass control the base class.
  Tron_Publisher::connect (p);
}

//
// allocate_event
//
template <typename EVENT>
EVENT * Tron_Publisher_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // Tron architecture.
  //===========================================================================

  return 0;
}

//
// send_event
//
template <typename EVENT>
void Tron_Publisher_T <EVENT>::send_event (EVENT * ev)
{
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
