// $Id$

#include "TCPIP_ComponentServer.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_ComponentServer.inl"
#endif

//
// install_component
//
int CUTS_TCPIP_ComponentServer::
install_component (const ACE_CString & name, CUTS_TCPIP_Servant * servant)
{
  return this->orb_.the_OM ().activate_object (servant);
}

//
// uninstall_component
//
int CUTS_TCPIP_ComponentServer::
uninstall_component (const ACE_CString & name)
{
  return 0;
}
