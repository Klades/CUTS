// -*- C++ -*-
// $Id$

#include "stdafx.h"
#include "Unique_Property_Bag.h"

#if !defined (__CUTS_INLINE__)
#include "Unique_Property_Bag.inl"
#endif

//
// insert_parameters
//
void CUTS_CUTE_Unique_Property_Bag::
insert_parameters (const ACE_Unbounded_Set <ACE_CString> & params)
{
  ACE_Unbounded_Set <ACE_CString>::CONST_ITERATOR iter (params);

  for ( ; !iter.done (); ++ iter)
    this->items_.insert (*iter);
}
