// $Id$

//
// CUTS_Component_Assembly
//
CUTS_INLINE
CUTS_Component_Assembly::CUTS_Component_Assembly (void)
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
// start
//
CUTS_INLINE
const CUTS_Component_Assembly::start_type &
CUTS_Component_Assembly::start (void) const
{
  return this->start_;
}
