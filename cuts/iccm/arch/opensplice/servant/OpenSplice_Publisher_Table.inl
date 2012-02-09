// -*- C++ -*-

namespace iCCM
{

//
// OpenSplice_Publisher_Table
//
CUTS_INLINE
OpenSplice_Publisher_Table::OpenSplice_Publisher_Table (void)
{

}

//
// get_datawriter
//
CUTS_INLINE
::DDS::DataWriter_ptr OpenSplice_Publisher_Table::get_datawriter (void)
{
  return DDS::DataWriter::_duplicate (this->abstract_writer_.in ());
}

//
// is_configured
//
CUTS_INLINE
bool OpenSplice_Publisher_Table::is_configured (void) const
{
  return !::CORBA::is_nil (this->abstract_writer_.in ());
}

}
