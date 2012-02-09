// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// OpenSplice_Publisher
//
CUTS_INLINE
OpenSplice_Publisher::OpenSplice_Publisher (void)
{

}

//
// get_datawriter
//
CUTS_INLINE
::DDS::DataWriter_ptr OpenSplice_Publisher::get_datawriter (void)
{
  return DDS::DataWriter::_duplicate (this->abstract_writer_.in ());
}

//
// is_configured
//
CUTS_INLINE
bool OpenSplice_Publisher::is_configured (void) const
{
  return !::CORBA::is_nil (this->abstract_writer_.in ());
}

}
