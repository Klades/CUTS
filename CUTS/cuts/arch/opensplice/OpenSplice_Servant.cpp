// $Id$

#include "OpenSplice_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

//
// participant
//
::DDS::DomainParticipant_ptr
CUTS_OpenSplice_Servant::participant (void)
{
  return ::DDS::DomainParticipant::_duplicate (this->participant_.in ());
}

//
// configure
//
void CUTS_OpenSplice_Servant::
configure (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}

//
// remove
//
::DDS::DomainParticipant_ptr CUTS_OpenSplice_Servant::remove_participant (void)
{
  return this->participant_._retn ();
}
