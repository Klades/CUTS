// $Id$

//
// options
//
CUTS_INLINE
const CUTS_Test_Options & CUTS_Testing_App::options (void) const
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::options (void) const");
  return this->opts_;
}

//
// test_db
//
CUTS_INLINE
CUTS_Test_Database & CUTS_Testing_App::test_db (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_App::test_db (void)");
  return this->test_db_;
}
