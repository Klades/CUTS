// $Id$

#include "Component_Assembly.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Assembly.inl"
#endif

#include "Antispam_Visitor.h"
#include "Component_Instance.h"
#include "ace/CORBA_macros.h"
#include "boost/bind.hpp"

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
  // Create a new instance.
  CUTS_Component_Instance * instance = 0;

  ACE_NEW_THROW_EX (instance,
                    CUTS_Component_Instance (name, type),
                    ACE_bad_alloc ());

  // Save the instance.
  this->instances_.bind (name, instance);

  // Update the start for the assembly.
  std::for_each (instance->start ().begin (),
                 instance->start ().end (),
                 boost::bind (&start_type::insert,
                              boost::ref (this->start_),
                              _1));

  return instance;
}

//
// accept
//
void CUTS_Component_Assembly::accept (CUTS_Antispam_Visitor & visitor)
{
  visitor.visit_CUTS_Component_Assembly (*this);
}