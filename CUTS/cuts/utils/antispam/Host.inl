// -*- C++ -*-
// $Id$

//
// CUTS_Host
//
CUTS_INLINE
CUTS_Host::CUTS_Host (void)
{

}

//
// ~CUTS_Host
//
CUTS_INLINE
CUTS_Host::~CUTS_Host (void)
{

}

//
// instances
//
CUTS_INLINE
const CUTS_Host::container_type & CUTS_Host::instances (void) const
{
  return this->instances_;
}

//
// instances
//
CUTS_INLINE
CUTS_Host::container_type & CUTS_Host::instances (void)
{
  return this->instances_;
}
