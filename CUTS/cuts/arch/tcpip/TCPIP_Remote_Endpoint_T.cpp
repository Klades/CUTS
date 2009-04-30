// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Remote_Endpoint_T.inl"
#endif

#include "ace/CDR_Stream.h"

//
// send_event
//
template <typename T>
int CUTS_TCPIP_Remote_Endpoint_T <T>::send_event (T * ev)
{
  // Reset the header size.
  this->header_.data_size_ = 0;

  char * ph_datasize = 0;
  ACE_OutputCDR packet;

  ph_datasize = (packet << this->header_);

  if ((packet << *ev))
  {
    // Update the data size of the packet.
    size_t datasize = packet.total_length () - CUTS_TCPIP_SPEC::BINARY_SIZE;
    packet.replace (static_cast <ACE_CDR::Long> (datasize), ph_datasize);

    // Send the packet.
    this->handler_->peer ().send_n (packet.begin ());
    return 0;
  }
  else
    return -1;
}
