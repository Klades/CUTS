// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Remote_Endpoint_T.inl"
#endif

#include "TCPIP_OutputCDR.h"

//
// send_event
//
template <typename T>
int CUTS_TCPIP_Remote_Endpoint_T <T>::send_event (T * ev)
{
  ACE_READ_GUARD_RETURN (ACE_RW_Thread_Mutex, guard, this->lock_, -1);

  if (0 == this->handler_)
    return -1;

  CUTS_TCPIP_OutputCDR packet;
  packet << this->header_;

  CUTS_TCPIP_OutputCDR payload;

  if (!(payload << *ev))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write event payload\n")),
                       -1);

  // Write the payload size and payload to the packet.
  packet.write_ulong (payload.total_length ());
  packet.write_octet_array_mb (payload.begin ());

  if (!packet.good_bit ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to construct packet\n")),
                       -1);

  // Send the packet to the receiver.
  ssize_t retval = this->handler_->peer ().send_n (packet.begin ());
  return retval == packet.total_length () ? 0 : -1;
}
