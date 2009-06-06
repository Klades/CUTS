// $Id$

#include "OpenSplice_CCM_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_CCM_Servant.inl"
#endif

//
// participant
//
::DDS::DomainParticipant_ptr
CUTS_OpenSplice_CCM_Servant::participant (void)
{
  return ::DDS::DomainParticipant::_duplicate (this->participant_.in ());
}

//
// participant
//
void CUTS_OpenSplice_CCM_Servant::
participant (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}
