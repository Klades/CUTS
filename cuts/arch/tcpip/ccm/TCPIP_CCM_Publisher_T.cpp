// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Publisher_T.inl"
#endif

#include "ace/OS_NS_unistd.h"

//
// connect
//
template <typename T>
void CUTS_TCPIP_CCM_Publisher_T <T>::
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
    this->endpoint_.connect (endpoint->address.in (),
                             endpoint->UUID.in (),
                             endpoint->event);

  if (0 != retval)
    throw ::Components::InvalidConnection ();

  // Save the consumer for this publisher.
  this->consumer_ = consumer._retn ();
}

//
// disconnect
//
template <typename T>
::Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Publisher_T <T>::disconnect (void)
{
  if (this->endpoint_.is_connected ())
    this->endpoint_.disconnect ();

  return this->consumer_._retn ();
}
