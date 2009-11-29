// -*- C++ -*-
// $Id$

//
// CUTS_Validation_Test_File
//
CUTS_INLINE
CUTS_Validation_Test_File::CUTS_Validation_Test_File (void)
: reader_type (&CUTS::XML::reader::validation),
  resolver_ (br_)
{
  this->configure ();
}

//
// ~CUTS_Validation_Test_File
//
CUTS_INLINE
CUTS_Validation_Test_File::~CUTS_Validation_Test_File (void)
{

}
