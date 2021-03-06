// $Id$

#include "Manager_Factory.h"
#include "Manager.h"

//
// CUTS_BE_RTIDDS_Manager_Factory
//
CUTS_BE_RTIDDS_Manager_Factory::CUTS_BE_RTIDDS_Manager_Factory (void)
{

}

//
// ~CUTS_BE_RTIDDS_Manager_Factory
//
CUTS_BE_RTIDDS_Manager_Factory::~CUTS_BE_RTIDDS_Manager_Factory (void)
{

}

//
// create_manager
//
CUTS_BE_Manager * CUTS_BE_RTIDDS_Manager_Factory::create_manager (void)
{
  return new CUTS_BE_RTIDDS_Manager ();
}

//
// name
//
const char * CUTS_BE_RTIDDS_Manager_Factory::name (void) const
{
  return "RTI-DDS (CORBA Compatibility Kit)";
}

//
// description
//
const char * CUTS_BE_RTIDDS_Manager_Factory::description (void) const
{
  return
    "This implementation of iCCM uses CORBA\r\n"
    "data types.";
}

CUTS_BE_CREATE_MANAGER_FACTORY_IMPLEMENT (CUTS_BE_RTIDDS_Manager_Factory);
