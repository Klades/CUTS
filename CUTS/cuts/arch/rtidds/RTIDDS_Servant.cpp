// $Id$

#include "RTIDDS_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

//
// participant
//
::DDSDomainParticipant * CUTS_RTIDDS_Servant::participant (void)
{
  return this->participant_;
}

//
// configure
//
void CUTS_RTIDDS_Servant::
configure (::DDSDomainParticipant * participant)
{
  this->participant_ = participant;
}

//
// remove
//
::DDSDomainParticipant * CUTS_RTIDDS_Servant::remove_participant (void)
{
  ::DDSDomainParticipant * participant = this->participant_;
  this->participant_ = 0;

  return participant;
}
