// $Id$

//
// CUTS_Component_Assembly
//
CUTS_INLINE
CUTS_Component_Assembly::
CUTS_Component_Assembly (const ACE_CString & name)
: CUTS_Component (name)
{

}

//
// instances
//
CUTS_INLINE
const CUTS_Component_Assembly::instances_type &
CUTS_Component_Assembly::instances (void) const
{
  return this->instances_;
}

//
// instances
//
CUTS_INLINE
CUTS_Component_Assembly::instances_type & CUTS_Component_Assembly::instances (void)
{
  return this->instances_;
}

//
// start
//
CUTS_INLINE
const CUTS_Component_Assembly::start_type &
CUTS_Component_Assembly::start (void) const
{
  return this->start_;
}
