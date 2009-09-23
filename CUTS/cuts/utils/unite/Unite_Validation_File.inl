// -*- C++ -*-
// $Id $

//
// CUTS_Unite_Validation_File
//
CUTS_INLINE
CUTS_Unite_Validation_File::CUTS_Unite_Validation_File (void)
: reader_type (&CUTS::XML::reader::validation),
  resolver_ (br_)
{
  this->configure ();
}

//
// ~CUTS_Unite_Validation_File
//
CUTS_INLINE
CUTS_Unite_Validation_File::~CUTS_Unite_Validation_File (void)
{

}
