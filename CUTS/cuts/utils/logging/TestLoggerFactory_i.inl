// $Id$

//
// test_number
//
CUTS_INLINE
long CUTS_TestLoggerFactory_i::test_number (void) const
{
  return this->test_number_;
}

//
// test_uuid
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_TestLoggerFactory_i::test_uuid (void) const
{
  return this->test_uuid_;
}


//
// connection
//
CUTS_INLINE
CUTS_DB_Connection & CUTS_TestLoggerFactory_i::connection (void)
{
  return this->conn_;
}
