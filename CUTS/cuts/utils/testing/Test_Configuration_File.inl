// $Id$

//
// CUTS_Test_Configuration_File
//
CUTS_INLINE
CUTS_Test_Configuration_File::CUTS_Test_Configuration_File (void)
: reader_type (&CUTS::reader::test)
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
