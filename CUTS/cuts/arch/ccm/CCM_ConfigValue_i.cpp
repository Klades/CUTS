// $Id$

#include "CCM_ConfigValue_i.h"

///////////////////////////////////////////////////////////////////////////////
// CUTS_CCM_ConfigValue_i

//
// CUTS_CCM_ConfigValue_i
//
CUTS_CCM_ConfigValue_i::CUTS_CCM_ConfigValue_i (void)
{

}

//
// CUTS_CCM_ConfigValue_i
//
CUTS_CCM_ConfigValue_i::
CUTS_CCM_ConfigValue_i (const char* name, const CORBA::Any & value)
: ::OBV_Components::ConfigValue (name, value)
{

}

//
// ~CUTS_CCM_ConfigValue_i
//
CUTS_CCM_ConfigValue_i::~CUTS_CCM_ConfigValue_i (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_CCM_ConfigValue_Factory

//
// CUTS_CCM_ConfigValue_Factory
//
CUTS_CCM_ConfigValue_Factory::CUTS_CCM_ConfigValue_Factory (void)
{

}

//
// ~CUTS_CCM_ConfigValue_Factory
//
CUTS_CCM_ConfigValue_Factory::~CUTS_CCM_ConfigValue_Factory (void)
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
CUTS_CCM_ConfigValue_Factory::create_for_unmarshal (void)
{
  return new CUTS_CCM_ConfigValue_i ();
}
