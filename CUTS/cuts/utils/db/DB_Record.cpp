// $Id$

#include "DB_Record.h"

#if !defined (__CUTS_INLINE__)
#include "DB_Record.inl"
#endif

//
// destroy
//
void CUTS_DB_Record::destroy (void)
{
  delete this;
}
