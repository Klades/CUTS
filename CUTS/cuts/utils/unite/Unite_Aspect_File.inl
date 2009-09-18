// -*- C++ -*-
// $Id$

//
// CUTS_Unite_Aspect_File
//
CUTS_INLINE
CUTS_Unite_Aspect_File::CUTS_Unite_Aspect_File (void)
: reader_type (&CUTS::XML::reader::aspect),
  resolver_ (br_)
{
  this->configure ();
}

//
// ~CUTS_Unite_Aspect_File
//
CUTS_INLINE
CUTS_Unite_Aspect_File::~CUTS_Unite_Aspect_File (void)
{

}
