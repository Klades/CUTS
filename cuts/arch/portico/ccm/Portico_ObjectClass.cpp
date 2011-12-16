// $Id$

#include "Portico_ObjectClass.h"

//
// Portico_ObjectClass
//
Portico_ObjectClass::Portico_ObjectClass (RTI::ObjectClassHandle hla_type)
: hla_type_ (hla_type)
{

}

//
// Portico_ObjectClass
//
Portico_ObjectClass::~Portico_ObjectClass (void)
{

}

//
// __hla_type
//
RTI::ObjectClassHandle Portico_ObjectClass::__hla_type (void) const
{
  return this->hla_type_;
}
