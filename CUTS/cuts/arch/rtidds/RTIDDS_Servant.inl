// -*- C++ -*-
// $Id$

//
// CUTS_RTIDDS_Servant
//
CUTS_INLINE
CUTS_RTIDDS_Servant::CUTS_RTIDDS_Servant (void)
: participant_ (0),
  publisher_ (0),
  subscriber_ (0)
{

}

//
// CUTS_RTIDDS_Servant
//
CUTS_INLINE
CUTS_RTIDDS_Servant::~CUTS_RTIDDS_Servant (void)
{

}

//
// participant
//
CUTS_INLINE
::DDSDomainParticipant * CUTS_RTIDDS_Servant::participant (void)
{
  return this->participant_;
}

//
// configure
//
CUTS_INLINE
void CUTS_RTIDDS_Servant::configure (::DDSDomainParticipant * participant)
{
  this->participant_ = participant;
}
