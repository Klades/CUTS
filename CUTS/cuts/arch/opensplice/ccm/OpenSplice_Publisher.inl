// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_CCM_Publisher
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Publisher::CUTS_OpenSplice_CCM_Publisher (void)
{

}

//
// ~CUTS_OpenSplice_CCM_Publisher
//
CUTS_INLINE
CUTS_OpenSplice_CCM_Publisher::~CUTS_OpenSplice_CCM_Publisher (void)
{
  this->disconnect ();
}

//
// configure
//
CUTS_INLINE
void CUTS_OpenSplice_CCM_Publisher::configure (::DDS::Publisher_ptr publisher)
{
  this->publisher_ = ::DDS::Publisher::_duplicate (publisher);
}

