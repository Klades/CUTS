// $Id$

#include "Portico_ObjectClass_Factory.h"

//
// Portico_ObjectClass_Factory
//
Portico_ObjectClass_Factory::
Portico_ObjectClass_Factory (RTI::ObjectClassHandle handle)
: handle_ (handle)
{

}

//
// ~Portico_ObjectClass_Factory
//
Portico_ObjectClass_Factory::~Portico_ObjectClass_Factory (void)
{

}

//
// get_handle
//
RTI::ObjectClassHandle Portico_ObjectClass_Factory::get_handle (void) const
{
  return this->handle_;
}
