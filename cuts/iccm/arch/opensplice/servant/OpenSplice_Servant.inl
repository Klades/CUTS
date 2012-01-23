// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// ~OpenSplice_Servant
//
CUTS_INLINE
OpenSplice_Servant::~OpenSplice_Servant (void)
{

}

//
// configure
//
CUTS_INLINE
void OpenSplice_Servant::configure (void)
{

}

//
// participant
//
CUTS_INLINE
::DDS::DomainParticipant_ptr
OpenSplice_Servant::participant (void)
{
  return ::DDS::DomainParticipant::_duplicate (this->participant_.in ());
}

//
// is_publisher
//
CUTS_INLINE
bool OpenSplice_Servant::is_publisher (void) const
{
  return ::CORBA::is_nil (this->publisher_.in ());
}

//
// get_publisher
//
CUTS_INLINE
::DDS::Publisher_ptr  OpenSplice_Servant::get_publisher (void)
{
  return ::DDS::Publisher::_duplicate (this->publisher_.in ());
}

//
// is_subscriber
//
CUTS_INLINE
bool OpenSplice_Servant::is_subscriber (void) const
{
  return ::CORBA::is_nil (this->subscriber_.in ());
}

//
// get_subscriber
//
CUTS_INLINE
::DDS::Subscriber_ptr  OpenSplice_Servant::get_subscriber (void)
{
  return ::DDS::Subscriber::_duplicate (this->subscriber_.in ());
}

}
