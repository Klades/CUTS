// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Publisher_T.inl"
#endif

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void TCPIP_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  ::Components::TCPIP::EventConsumer_var consumer =
      ::Components::TCPIP::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  // Get the remote endpoint from the consumer.
  ::Components::TCPIP::Endpoint_var endpoint = consumer->remote_endpoint ();

  int retval =
    this->endpoint_.connect (endpoint->address.in (),
                             endpoint->UUID.in (),
                             endpoint->event);

  if (0 != retval)
    throw ::Components::InvalidConnection ();

  // Pass control the base class.
  TCPIP_Publisher::connect (p);
}

//
// allocate_event
//
template <typename EVENT>
EVENT * TCPIP_Publisher_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // TCPIP architecture.
  //===========================================================================
  typedef typename TCPIP_Event_Traits < EVENT >::tcpip_event_type event_type;

  event_type * ev = 0;
  ACE_NEW_THROW_EX (ev,
                    event_type (),
                    ::CORBA::NO_MEMORY ());

  return ev;
}

//
// send_event
//
template <typename EVENT>
void TCPIP_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the TCPIP architecture. It should then be sent using
  // the TCPIP mechanisms for sending an event.
  //===========================================================================
  this->endpoint_.send_event (ev);
}

//
// disconnect
//
template <typename EVENT>
::Components::EventConsumerBase_ptr TCPIP_Publisher_T <EVENT>::disconnect (void)
{
  if (this->endpoint_.is_connected ())
    this->endpoint_.disconnect ();

  return this->consumer_._retn ();
}

}
