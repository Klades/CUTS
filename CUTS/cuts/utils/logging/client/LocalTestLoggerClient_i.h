// -*- C++ -*-

//=============================================================================
/**
 *
 */
//=============================================================================

#include "Logging_Client_export.h"
#include "clientS.h"

#ifndef _CUTS_LOCAL_TEST_LOGGER_CLIENT_I_H_
#define _CUTS_LOCAL_TEST_LOGGER_CLIENT_I_H_

// Forward decl.
class CUTS_TestLoggerClient_i;

/**
 * @class CUTS_LocalTestLoggerClient_i
 */
class CUTS_LocalTestLoggerClient_i :
  public POA_CUTS::LocalTestLoggerClient
{
public:
  CUTS_LocalTestLoggerClient_i (const CUTS_TestLoggerClient_i & client);

  virtual ~CUTS_LocalTestLoggerClient_i (void);

  virtual CUTS::TestLoggerFactory_ptr find (const CUTS::UUID & uid);

private:
  const CUTS_TestLoggerClient_i & client_;
};

#endif  // !defined _CUTS_LOCAL_TEST_LOGGER_CLIENT_I_H_
