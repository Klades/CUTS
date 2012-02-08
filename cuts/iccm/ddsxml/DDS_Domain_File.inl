// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Domain_File
//
CUTS_INLINE
DDS_Domain_File::DDS_Domain_File (void)
: reader_type (&iccm::reader::domain),
  resolver_ (br_)
{
  this->configure ();
}

//
// DDS_Domain_File
//
CUTS_INLINE
DDS_Domain_File::~DDS_Domain_File (void)
{

}

}
