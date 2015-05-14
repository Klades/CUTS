// $IdQpidPB_Publisher_Table_T.cpp 3289 2012-02-10 03:05:18Z hillj $

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_Table_T.inl"
#endif

#include "cuts/iccm/servant/Cookie.h"

namespace iCCM
{

//
// allocate_event
//
template <typename EVENT>
EVENT * QpidPB_Publisher_Table_T <EVENT>::allocate_event (void)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place here whould allocate an event of type EVENT.
  // The allocated event will be a wrapper class that implements the EVENT
  // interface, but set values for the corresponding event type in the
  // QpidPB architecture.
  //===========================================================================

  return 0;
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
QpidPB_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  // Make sure this is a valid consumer.
  ::Components::QpidPB::EventConsumer_var consumer =
    ::Components::QpidPB::EventConsumer::_narrow (consumer_base);

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
QpidPB_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
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
  ::Components::QpidPB::EventConsumer_var consumer =
    ::Components::QpidPB::EventConsumer::_narrow (consumer_base);

  return consumer_base;
}

//
// send_event
//
template <typename EVENT>
void QpidPB_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  //===========================================================================
  // INSERT CODE HERE
  //
  // The code that you place should cast the CORBA event to its corresponding
  // wrapper in the QpidPB architecture. It should then be sent using
  // the QpidPB mechanisms for sending an event.
  //===========================================================================
}

}
