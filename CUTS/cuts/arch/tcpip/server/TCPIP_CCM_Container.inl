// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::
CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_ComponentServer & parent,
                          const Components::ConfigValues & config,
                          ::PortableServer::POA_ptr poa)
: parent_ (parent),
  poa_ (::PortableServer::POA::_duplicate (poa))
{
  this->init (config);
}

//
// ~CUTS_TCPIP_CCM_Container
//
CUTS_INLINE
CUTS_TCPIP_CCM_Container::~CUTS_TCPIP_CCM_Container (void)
{

}
