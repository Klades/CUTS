// $Id$

//
// test_uuid
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_TestLoggerFactory_i::test_uuid (void) const
{
  return this->test_uuid_;
}

//
// server
//
CUTS_INLINE
CUTS::TestLoggerServer_ptr CUTS_TestLoggerFactory_i::server (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerFactory_i::server (void)");

  return CUTS::TestLoggerServer::_duplicate (this->server_.in ());
}

//
// server
//
CUTS_INLINE
void CUTS_TestLoggerFactory_i::server (CUTS::TestLoggerServer_ptr s)
{
  this->server_ = CUTS::TestLoggerServer::_duplicate (s);
}
