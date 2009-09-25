// -*- C++ -*-
// $Id$

//
// CUTS_CHAOS_CCM_Servant
//
CUTS_INLINE
CUTS_CHAOS_CCM_Servant::
CUTS_CHAOS_CCM_Servant (const char * name)
: CUTS_CCM_Servant (name)
{

}

//
// ~CUTS_CHAOS_CCM_Servant
//
CUTS_INLINE
CUTS_CHAOS_CCM_Servant::~CUTS_CHAOS_CCM_Servant (void)
{

}

//
// configure
//
CUTS_INLINE
void CUTS_CHAOS_CCM_Servant::
configure (::DDS::DomainParticipant_ptr participant)
{
  CUTS_OpenSplice_Servant::configure (participant);
}

//
// configure
//
CUTS_INLINE
void CUTS_CHAOS_CCM_Servant::
configure (::DDSDomainParticipant * participant)
{
  CUTS_RTIDDS_Servant::configure (participant);
}
