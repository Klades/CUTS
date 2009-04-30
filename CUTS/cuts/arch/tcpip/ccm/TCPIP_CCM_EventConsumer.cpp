// $Id$

#include "TCPIP_CCM_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_EventConsumer.inl"
#endif

#include "cuts/arch/tcpip/TCPIP_ORB.h"
#include "cuts/arch/tcpip/TCPIP_Servant.h"
#include <sstream>

//
// remote_endpoint
//
::Components::TCPIP::Endpoint *
CUTS_TCPIP_CCM_EventConsumer::remote_endpoint (void)
{
  ::Components::TCPIP::Endpoint * temp = 0;

  ACE_NEW_THROW_EX (temp,
                    ::Components::TCPIP::Endpoint (),
                    CORBA::NO_MEMORY ());

  const CUTS_TCPIP_ORB * orb = this->parent_->the_ORB ();
  const CUTS_TCPIP_Acceptor::PEER_ADDR & addr = orb->listen_addr ();

  std::ostringstream address;

  if (addr.is_any ())
    address << addr.get_host_name ();
  else
    address << addr.get_host_addr ();

  address << ":" << addr.get_port_number ();

  ::Components::TCPIP::Endpoint_var endpoint (temp);
  endpoint->address = ::CORBA::string_dup (address.str ().c_str ());
  endpoint->UUID = ::CORBA::string_dup (this->parent_->the_UUID ().to_string ()->c_str ());
  endpoint->event = this->event_;

  return endpoint._retn ();
}
