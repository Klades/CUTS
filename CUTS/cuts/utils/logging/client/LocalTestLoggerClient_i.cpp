// $Id$

#include "LocalTestLoggerClient_i.h"
#include "TestLoggerClient_i.h"

//
// CUTS_LocalTestLoggerClient_i
//
CUTS_LocalTestLoggerClient_i::
CUTS_LocalTestLoggerClient_i (const CUTS_TestLoggerClient_i & client)
: client_ (client)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_LocalTestLoggerClient_i::CUTS_LocalTestLoggerClient_i (void)");
}

//
// ~CUTS_LocalTestLoggerClient_i
//
CUTS_LocalTestLoggerClient_i::~CUTS_LocalTestLoggerClient_i (void)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_LocalTestLoggerClient_i::~CUTS_LocalTestLoggerClient_i (void)");
}

//
// find
//
CUTS::TestLoggerFactory_ptr
CUTS_LocalTestLoggerClient_i::find (const CUTS::UUID & uuid)
{
  CUTS_TEST_LOGGING_CLIENT_TRACE ("CUTS_LocalTestLoggerClient_i::find (const CUTS::UUID &)");
  return this->client_.find (uuid);
}
