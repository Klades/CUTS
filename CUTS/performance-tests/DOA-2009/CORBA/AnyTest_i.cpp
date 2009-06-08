// $Id$

#include "AnyTest_i.h"

AnyTest_i::AnyTest_i (void)
{

}

AnyTest_i::~AnyTest_i (void)
{

}

void AnyTest_i::send_any (const ::CORBA::Any & any)
{
  this->any_count_ ++;
}

void AnyTest_i::send_any_oneway (const ::CORBA::Any & any)
{
  this->any_oneway_count_ ++;
}
