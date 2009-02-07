// $Id$

#include "Component_Assembly.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Assembly.inl"
#endif

#include "Component_Instance.h"
#include "ace/CORBA_macros.h"

//
// ~CUTS_Component_Assembly
//
CUTS_Component_Assembly::~CUTS_Component_Assembly (void)
{
  instances_type::ITERATOR iter (this->instances_);

  for ( ; !iter.done (); ++ iter)
    delete iter->int_id_;
}

//
// new_instance
//
CUTS_Component_Instance * CUTS_Component_Assembly::
new_instance (const ACE_CString & name, const CUTS_Component & type)
{
  CUTS_Component_Instance * instance = 0;

  ACE_NEW_THROW_EX (instance,
                    CUTS_Component_Instance (name, type),
                    ACE_bad_alloc ());

  this->instances_.bind (name, instance);
  return instance;
}
