// $Id$

#include "Manager_Factory.h"
#include "Manager.h"

static const char * __description__ =
  "Generate project and source\r\n"
  "files for EISA compliant\r\n"
  "Component Integrated ACE\r\n"
  "ORB (CIAO)";

//
// CUTS_BE_EISA_Manager_Factory
//
CUTS_BE_EISA_Manager_Factory::CUTS_BE_EISA_Manager_Factory (void)
{

}

//
// ~CUTS_BE_EISA_Manager_Factory
//
CUTS_BE_EISA_Manager_Factory::~CUTS_BE_EISA_Manager_Factory (void)
{

}

//
// create_manager
//
CUTS_BE_Manager * CUTS_BE_EISA_Manager_Factory::create_manager (void)
{
  return new EISA_BE_Manager ();
}

//
// name
//
const char * CUTS_BE_EISA_Manager_Factory::name (void) const
{
  return "EISA - CIAO";
}

//
// description
//
const char * CUTS_BE_EISA_Manager_Factory::description (void) const
{
  return __description__;
}

CUTS_BE_CREATE_MANAGER_FACTORY_IMPLEMENT (CUTS_BE_EISA_Manager_Factory);
