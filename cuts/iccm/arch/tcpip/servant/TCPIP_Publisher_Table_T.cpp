// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Publisher_Table_T.inl"
#endif

#include "cuts/iccm/servant/Cookie.h"

namespace iCCM
{

//
// allocate_event
//
template <typename EVENT>
EVENT * TCPIP_Publisher_Table_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // TCPIP architecture.
  //===========================================================================
  return 0;
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
TCPIP_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  // Make sure this is a valid consumer.
  ::Components::TCPIP::EventConsumer_var consumer =
    ::Components::TCPIP::EventConsumer::_narrow (consumer_base);

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
TCPIP_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
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
  ::Components::TCPIP::EventConsumer_var consumer =
    ::Components::TCPIP::EventConsumer::_narrow (consumer_base);

  return consumer_base;
}

//
// send_event
//
template <typename EVENT>
void TCPIP_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the TCPIP architecture. It should then be sent using
  // the TCPIP mechanisms for sending an event.
  //===========================================================================
  typename consumer_table_t::ITERATOR iter (this->table_);

  for ( ; !iter.done (); ++ iter)
    iter->item ()->send_event (ev);
}

}
