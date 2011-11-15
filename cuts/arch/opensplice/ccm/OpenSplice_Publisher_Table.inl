// -*- C++ -*-

//
// CUTS_OpenSplice_CCM_Publisher_Table
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Publisher_Table::CUTS_OpenSplice_CCM_Publisher_Table (void)
{

}

//
// ~CUTS_OpenSplice_CCM_Publisher_Table
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Publisher_Table::~CUTS_OpenSplice_CCM_Publisher_Table (void)
{

}

//
// configure
//
CUTS_INLINE
void CUTS_OpenSplice_CCM_Publisher_Table::
configure (::DDS::Publisher_ptr publisher)
{
  this->publisher_ = ::DDS::Publisher::_duplicate (publisher);
}
