// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_EventConsumer_T.inl"
#endif

#include "ccm/CCM_ContextC.h"
#include "cuts/iccm/arch/tcpip/stub/TCPIP_ORB.h"
#include <sstream>


namespace iCCM
{

//
// remote_endpoint
//
template <typename SERVANT, typename EVENT>
CUTS_INLINE
::Components::TCPIP::Endpoint *
TCPIP_EventConsumer_T <SERVANT, EVENT>::remote_endpoint (void)
{
  ::Components::TCPIP::Endpoint * temp = 0;

  ACE_NEW_THROW_EX (temp,
                    ::Components::TCPIP::Endpoint (),
                    ::CORBA::NO_MEMORY ());

  const TCPIP_ORB * orb = this->servant_->the_ORB ();

  if (0 == orb)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to locate TCP/IP ORB\n")));

    throw ::Components::IllegalState ();
  }

  const CUTS_TCPIP_Acceptor::PEER_ADDR & addr = orb->listen_addr ();

  std::ostringstream address;

  if (addr.is_any ())
    address << addr.get_host_name ();
  else
    address << addr.get_host_addr ();

  address << ":" << addr.get_port_number ();

  ::Components::TCPIP::Endpoint_var endpoint (temp);
  endpoint->address = ::CORBA::string_dup (address.str ().c_str ());
  endpoint->UUID = ::CORBA::string_dup (this->servant_->the_UUID ().to_string ()->c_str ());
  endpoint->event = this->event_id_;

  return endpoint._retn ();
}

}
