// $Id$

//
// ~CUTS_TestLoggerFactory_i
//
CUTS_INLINE
CUTS_TestLoggerFactory_i::~CUTS_TestLoggerFactory_i (void)
{

}

//
// test_number
//
CUTS_INLINE
long CUTS_TestLoggerFactory_i::test_number (void) const
{
  return this->test_number_;
}

//
// connection
//
CUTS_INLINE
CUTS_DB_Connection & CUTS_TestLoggerFactory_i::connection (void)
{
  return this->conn_;
}
