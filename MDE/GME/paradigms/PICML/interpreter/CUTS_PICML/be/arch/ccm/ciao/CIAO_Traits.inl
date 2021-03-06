// -*- C++ - *-
// $Id$

namespace CUTS_BE_CIAO
{

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
  return "iccm_tao_stub";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * Traits::svnt_base_project (void)
{
  return "iccm_tao_svnt";
}

//
// skel_base_project
//
CUTS_INLINE
const char * Traits::skel_base_project (void)
{
  return "iccm_tao_skel";
}

//
// emulates_async
//
bool Traits::emulates_async (void)
{
  return true;
}

}
