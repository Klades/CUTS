// -*- C++ - *-
// $Id$

namespace CUTS_BE_OpenSplice
{

//
// Traits
//
CUTS_INLINE
Traits::Traits (void)
: has_events_ (false)
{

}

//
// ~Traits
//
CUTS_INLINE
Traits::~Traits (void)
{

}

//
// generate_default_servant
//
CUTS_INLINE
bool Traits::generate_default_servant (void)
{
  return false;
}

//
// stub_base_project
//
CUTS_INLINE
const char * Traits::stub_base_project (void)
{
  return "cuts_opensplice_ccm_stub";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * Traits::svnt_base_project (void)
{
  return "cuts_opensplice_ccm";
}

}
