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
  ::Components::TCPIP::EventConsumerBase_var consumer =
    ::Components::TCPIP::EventConsumerBase::_narrow (ptr);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::Components::InvalidConnection ();

  // Get the remote endpoint from the consumer.
  ::Components::TCPIP::Endpoint_var endpoint = consumer->remote_endpoint ();

  int retval =
    CUTS_TCPIP_Remote_Endpoint::connect (endpoint->address.in (),
                                         endpoint->UUID.in (),
                                         endpoint->event);

  if (0 != retval)
    throw ::Components::InvalidConnection ();
}
