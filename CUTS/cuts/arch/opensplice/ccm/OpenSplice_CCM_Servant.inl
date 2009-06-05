// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_CCM_Servant
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Servant::
CUTS_OpenSplice_CCM_Servant (const char * name)
  : CUTS_CCM_Servant (name)
{

}

//
// ~CUTS_OpenSplice_CCM_Servant
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Servant::~CUTS_OpenSplice_CCM_Servant (void)
{

}

//
// get_participant
//
CUTS_INLINE
::DDS::DomainParticipant_ptr 
CUTS_OpenSplice_CCM_Servant::get_participant (void)
{
  return ::DDS::DomainParticipant::_duplicate (this->participant_.in ());
}

//
// participant
//
CUTS_INLINE
void CUTS_OpenSplice_CCM_Servant::
participant (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}
