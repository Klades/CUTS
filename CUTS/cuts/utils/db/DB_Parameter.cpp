// $Id$

#include "DB_Parameter.h"

#if !defined (__CUTS_INLINE__)
#include "DB_Parameter.inl"
#endif

//
// CUTS_DB_Parameter
//
CUTS_DB_Parameter::CUTS_DB_Parameter (void)
: index_ (-1),
  type_ (PT_UNKNOWN),
  null_ (0)
{

}

//
// CUTS_DB_Parameter
//
CUTS_DB_Parameter::CUTS_DB_Parameter (const CUTS_DB_Parameter & p)
: index_ (p.index_),
  type_ (p.type_),
  null_ (p.null_)
{

}

//
// CUTS_DB_Parameter
//
CUTS_DB_Parameter::~CUTS_DB_Parameter (void)
{

}
