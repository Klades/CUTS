// $Id$

//
// CUTS_TestLoggerServer_Singleton
//
CUTS_INLINE
CUTS_TestLoggerServer_Singleton::CUTS_TestLoggerServer_Singleton (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerServer_Singleton::CUTS_TestLoggerServer_Singleton (void)");
}

//
// ~CUTS_TestLoggerServer_Singleton
//
CUTS_INLINE
CUTS_TestLoggerServer_Singleton::~CUTS_TestLoggerServer_Singleton (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerServer_Singleton::~CUTS_TestLoggerServer_Singleton (void)");
}

//
// ~CUTS_TestLoggerServer_Singleton
//
CUTS_INLINE
void CUTS_TestLoggerServer_Singleton::
reset (CUTS::TestLoggerServer_ptr server)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerServer_Singleton::reset (CUTS::TestLoggerServer_ptr server)");
  this->server_ = CUTS::TestLoggerServer::_duplicate (server);
}

//
// ~CUTS_TestLoggerServer_Singleton
//
CUTS_INLINE
CUTS::TestLoggerServer_ptr
CUTS_TestLoggerServer_Singleton::get (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_TestLoggerServer_Singleton::get (void)");
  return CUTS::TestLoggerServer::_duplicate (this->server_.in ());
}
