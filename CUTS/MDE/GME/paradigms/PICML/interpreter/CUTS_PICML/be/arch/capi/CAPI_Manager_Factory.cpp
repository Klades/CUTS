// $Id$

#include "CAPI_Manager_Factory.h"
#include "CAPI_Manager.h"

//
// CUTS_BE_CAPI_Manager_Factory
//
CUTS_BE_CAPI_Manager_Factory::CUTS_BE_CAPI_Manager_Factory (void)
{

}

//
// ~CUTS_BE_CAPI_Manager_Factory
//
CUTS_BE_CAPI_Manager_Factory::~CUTS_BE_CAPI_Manager_Factory (void)
{

}

//
// create_manager
//
CUTS_BE_Manager * CUTS_BE_CAPI_Manager_Factory::create_manager (void)
{
  return new CUTS_BE_CAPI_Manager ();
}

//
// name
//
const char * CUTS_BE_CAPI_Manager_Factory::name (void) const
{
  return "JBI CAPI 1.0 (Java)";
}

//
// description
//
const char * CUTS_BE_CAPI_Manager_Factory::description (void) const
{
  return "JBI CAPI 1.0 (Java)";
}

CUTS_BE_CREATE_MANAGER_FACTORY_IMPLEMENT (CUTS_BE_CAPI_Manager_Factory);
