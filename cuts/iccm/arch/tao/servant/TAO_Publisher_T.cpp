// $Id$

#if !defined (__CUTS_INLINE__)
#include "TAO_Publisher_T.inl"
#endif

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void TAO_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  ::Components::TAO::EventConsumer_var consumer =
      ::Components::TAO::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should use the <consumer> object
  // to extract information for establishing a connection and sending
  // data to this consumer event point via TAO architecture.
  //===========================================================================

  // Pass control the base class.
  TAO_Publisher::connect (p);
}

//
// allocate_event
//
template <typename EVENT>
EVENT * TAO_Publisher_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // TAO architecture.
  //===========================================================================

  return 0;
}

//
// send_event
//
template <typename EVENT>
void TAO_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the TAO architecture. It should then be sent using
  // the TAO mechanisms for sending an event.
  //===========================================================================
  if (!::CORBA::is_nil (this->consumer_.in ()))
    this->consumer_->push_event (ev);
}

}
