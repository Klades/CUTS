// $Id$

#include "Host.h"

#if !defined (__CUTS_INLINE__)
#include "Host.inl"
#endif

#include "Component_Instance.h"

//
// utilization
//
double CUTS_Host::utilization (void) const
{
  double util = 0.0;
  container_type::CONST_ITERATOR iter (this->instances_);

  for (; !iter.done (); ++ iter)
    util += (*iter)->utilization ();

  return util;
}
