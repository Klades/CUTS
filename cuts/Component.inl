// -*- C++ -*-
// $Id$

//
// CUTS_Component
//
CUTS_INLINE
CUTS_Component::CUTS_Component (void)
{

}

//
// CUTS_Component
//
CUTS_INLINE
CUTS_Component::~CUTS_Component (void)
{

}

//
// register_object
//
CUTS_INLINE
int CUTS_Component::register_object (CUTS_Active_Object * ao)
{
  return this->ao_list_.insert (ao);
}
