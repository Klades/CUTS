// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Remote_Endpoint_T.inl"
#endif

#include "TCPIP_CCM_EventConsumer.h"

//
// connect
//
template <typename T>
void CUTS_TCPIP_CCM_Remote_Endpoint_T <T>::
connect (::Components::EventConsumerBase_ptr ptr)
{
  // Narrow the object to a TCPIP EventConsumerBase object.
  this->consumer_ = ::Components::TCPIP::EventConsumerBase::_narrow (ptr);

  if (::CORBA::is_nil (this->consumer_.in ()))
    throw ::Components::InvalidConnection ();

  // Get the remote endpoint from the consumer.
  ::Components::TCPIP::Endpoint_var endpoint = this->consumer_->remote_endpoint ();

  int retval =
    CUTS_TCPIP_Remote_Endpoint::connect (endpoint->address.in (),
                                         endpoint->UUID.in (),
                                         endpoint->event);

  if (0 != retval)
    throw ::Components::InvalidConnection ();
}

//
// disconnect
//
template <typename T>
::Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Remote_Endpoint_T <T>::disconnect (void)
{
  CUTS_TCPIP_Remote_Endpoint::disconnect ();
  return this->consumer_._retn ();
}
