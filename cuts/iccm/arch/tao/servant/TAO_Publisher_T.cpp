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
  ::Components::TAO_iCCM::EventConsumer_var consumer =
      ::Components::TAO_iCCM::EventConsumer::_narrow (p);

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
  typedef typename TAO_Event_Traits < EVENT >::tao_event_type event_type;

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
void TAO_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the TAO architecture. It should then be sent using
  // the TAO mechanisms for sending an event.
  //===========================================================================
  try
  {
    if (!::CORBA::is_nil (this->consumer_.in ()))
      this->consumer_->push_event (ev);
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("%T (%t) - %M - Error sending event\n")));
  }
}

//
// send_event
//
template <typename EVENT>
void TAO_Publisher_T <EVENT>::send_event (::Components::EventBase * base)
{
  EVENT * ev = dynamic_cast < EVENT * > (base);
  return this->send_event (ev);
}


}
