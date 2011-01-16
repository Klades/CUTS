// -*- C++ - *-
// $Id$

//
// CUTS_BE_TCPIP_Traits
//
CUTS_INLINE
CUTS_BE_TCPIP_Traits::CUTS_BE_TCPIP_Traits (void)
: has_events_ (false)
{

}

//
// ~CUTS_BE_TCPIP_Traits
//
CUTS_INLINE
CUTS_BE_TCPIP_Traits::~CUTS_BE_TCPIP_Traits (void)
{

}

//
// generate_default_servant
//
CUTS_INLINE
bool CUTS_BE_TCPIP_Traits::generate_default_servant (void)
{
  return false;
}

//
// stub_base_project
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::stub_base_project (void)
{
  return "cuts_tcpip_ccm_stub";
}

//
// svnt_base_project
//
CUTS_INLINE
const char * CUTS_BE_TCPIP_Traits::svnt_base_project (void)
{
  return "cuts_tcpip_ccm";
}
