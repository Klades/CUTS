// $Id$

//
// CUTS_Test_Configuration_File
//
CUTS_INLINE
CUTS_Test_Configuration_File::
CUTS_Test_Configuration_File (const CUTS_Property_Map & props)
: reader_type (&CUTS::reader::test),
  resolver_ (br_),
  props_ (props)
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

//
// config
//
CUTS_INLINE
CUTS::testFile & CUTS_Test_Configuration_File::config (void)
{
  return this->config_;
}
