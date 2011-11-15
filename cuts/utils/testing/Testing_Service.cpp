// $Id$

#include "Testing_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service.inl"
#endif

//
// destroy
//
void CUTS_Testing_Service::destroy (void)
{
  delete this;
}
