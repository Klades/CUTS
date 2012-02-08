// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Participant_File
//
CUTS_INLINE
DDS_Participant_File::DDS_Participant_File (void)
: reader_type (&iccm::reader::participant),
  resolver_ (br_)
{
  this->configure ();
}

//
// DDS_Participant_File
//
CUTS_INLINE
DDS_Participant_File::~DDS_Participant_File (void)
{

}

}
