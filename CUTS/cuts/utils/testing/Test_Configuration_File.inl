// $Id$

//
// CUTS_Test_Configuration_File
//
CUTS_INLINE
CUTS_Test_Configuration_File::CUTS_Test_Configuration_File (void)
: reader_type (&CUTS::reader::test),
  resolver_ (br_)
{
  this->configure ();
}

//
// ~CUTS_Test_Configuration_File
//
CUTS_INLINE
CUTS_Test_Configuration_File::~CUTS_Test_Configuration_File (void)
{

}
