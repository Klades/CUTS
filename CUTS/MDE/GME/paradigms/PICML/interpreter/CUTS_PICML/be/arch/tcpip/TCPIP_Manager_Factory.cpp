// $Id$

#include "TCPIP_Manager_Factory.h"
#include "TCPIP_Manager.h"

//
// CUTS_BE_TCPIP_Manager_Factory
//
CUTS_BE_TCPIP_Manager_Factory::CUTS_BE_TCPIP_Manager_Factory (void)
{

}

//
// ~CUTS_BE_TCPIP_Manager_Factory
//
CUTS_BE_TCPIP_Manager_Factory::~CUTS_BE_TCPIP_Manager_Factory (void)
{

}

//
// create_manager
//
CUTS_BE_Manager *
CUTS_BE_TCPIP_Manager_Factory::create_manager (void)
{
  return new CUTS_BE_TCPIP_Manager ();
}

//
// name
//
const char * CUTS_BE_TCPIP_Manager_Factory::name (void) const
{
  static const char * str = "TCP/IP (SPEC architecture)";
  return str;
}

//
// description
//
const char * CUTS_BE_TCPIP_Manager_Factory::description (void) const
{
  static const char * str = "TCP/IP (SPEC architecture)";
  return str;
}

CUTS_BE_CREATE_MANAGER_FACTORY_IMPLEMENT (CUTS_BE_TCPIP_Manager_Factory);

