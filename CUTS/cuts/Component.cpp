// $Id$

#include "Component.h"

#if !defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

#include "Active_Object.h"

//
// activate
//
int CUTS_Component::activate (void)
{
  ao_list_type::ITERATOR iter (this->ao_list_);

  for (; !iter.done (); ++ iter)
    (*iter)->activate ();

  return 0;
}

//
// deactivate
//
int CUTS_Component::deactivate (void)
{
  ao_list_type::ITERATOR iter (this->ao_list_);

  for (; !iter.done (); ++ iter)
    (*iter)->deactivate ();

  return 0;
}
