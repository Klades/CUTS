// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// OpenSplice_EventConsumer
//
CUTS_INLINE
OpenSplice_EventConsumer::OpenSplice_EventConsumer (void)
: subscriber_ (0),
  topic_qos_ (0)
{

}

//
// is_configured
//
CUTS_INLINE
bool OpenSplice_EventConsumer::is_configured (void) const
{
  return !::CORBA::is_nil (this->subscriber_);
}

//
// is_configured
//
CUTS_INLINE
::DDS::DataReader_ptr OpenSplice_EventConsumer::get_datareader (void)
{
  return ::DDS::DataReader::_duplicate (this->abstract_reader_.in ());
}

}
