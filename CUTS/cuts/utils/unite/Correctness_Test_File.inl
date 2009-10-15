// -*- C++ -*-
// $Id$

//
// CUTS_Correctness_Test_File
//
CUTS_INLINE
CUTS_Correctness_Test_File::CUTS_Correctness_Test_File (void)
: reader_type (&CUTS::XML::reader::correctness),
  resolver_ (br_)
{
  this->configure ();
}

//
// ~CUTS_Correctness_Test_File
//
CUTS_INLINE
CUTS_Correctness_Test_File::~CUTS_Correctness_Test_File (void)
{

}
