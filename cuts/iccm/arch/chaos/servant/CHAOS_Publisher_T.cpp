// $IdCHAOS_Publisher_T.cpp 3086 2011-01-22 05:53:51Z hillj $

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Publisher_T.inl"
#endif

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void CHAOS_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  ::Components::CHAOS::EventConsumer_var consumer =
      ::Components::CHAOS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here should use the <consumer> object
  // to extract information for establishing a connection and sending
  // data to this consumer event point via CHAOS architecture.
  //===========================================================================

  // Pass control the base class.
  CHAOS_Publisher::connect (p);
}

//
// allocate_event
//
template <typename EVENT>
EVENT * CHAOS_Publisher_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // CHAOS architecture.
  //===========================================================================

  return 0;
}

//
// send_event
//
template <typename EVENT>
void CHAOS_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the CHAOS architecture. It should then be sent using
  // the CHAOS mechanisms for sending an event.
  //===========================================================================
}

}
