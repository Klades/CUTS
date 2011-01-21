// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_Servant
//
CUTS_INLINE
CUTS_OpenSplice_Servant::CUTS_OpenSplice_Servant (void)
{

}

//
// CUTS_OpenSplice_Servant
//
CUTS_INLINE
CUTS_OpenSplice_Servant::~CUTS_OpenSplice_Servant (void)
{

}

//
// participant
//
CUTS_INLINE
::DDS::DomainParticipant_ptr
CUTS_OpenSplice_Servant::participant (void)
{
  return ::DDS::DomainParticipant::_duplicate (this->participant_.in ());
}

//
// configure
//
CUTS_INLINE
void CUTS_OpenSplice_Servant::
configure (::DDS::DomainParticipant_ptr participant)
{
  this->participant_ = ::DDS::DomainParticipant::_duplicate (participant);
}

//
// is_publisher
//
CUTS_INLINE
bool CUTS_OpenSplice_Servant::is_publisher (void) const
{
  return ::CORBA::is_nil (this->publisher_.in ());
}

//
// is_subscriber
//
CUTS_INLINE
bool CUTS_OpenSplice_Servant::is_subscriber (void) const
{
  return ::CORBA::is_nil (this->subscriber_.in ());
}
