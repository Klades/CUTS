// -*- C++ - *-
// $Id$

namespace CUTS_BE_OpenSplice
{

//
// Traits
//
CUTS_INLINE
Traits::Traits (void)
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
  return "iccm_opensplice_stub";
}

//
// skel_base_project
//
CUTS_INLINE
const char * Traits::skel_base_project (void)
{
  return "iccm_opensplice_skel";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * Traits::svnt_base_project (void)
{
  return "iccm_opensplice_svnt";
}

}
