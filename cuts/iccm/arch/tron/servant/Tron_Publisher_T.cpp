// $Id$

#if !defined (__CUTS_INLINE__)
#include "Tron_Publisher_T.inl"
#endif

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void Tron_CCM_Publisher_T <EVENT>::
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
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the Tron architecture. It should then be sent using
  // the Tron mechanisms for sending an event.
  //===========================================================================
}

}
