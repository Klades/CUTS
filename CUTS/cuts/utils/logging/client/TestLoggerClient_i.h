// -*- C++ -*-

//=============================================================================
/**
 * @file          TestLoggerClient_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_CLIENT_I_H_
#define _CUTS_TEST_LOGGER_CLIENT_I_H_

#include "clientS.h"
#include "Test_Logger_Map.h"

/**
 * @class CUTS_TestLoggerClient_i
 *
 * Implementation of the CUTS::TestLoggerClient interface. This object
 * is not thread-safe and must be activated under the RootPOA, or a
 * single-threaded POA. Otherwise, unknown behavior many occur.
 */
class CUTS_TestLoggerClient_i :
  public virtual POA_CUTS::TestLoggerClient
{
public:
  /// Default constructor.
  CUTS_TestLoggerClient_i (PortableServer::POA_ptr root_poa);

  /// Destructor.
  virtual ~CUTS_TestLoggerClient_i (void);

  virtual void register_server (const CUTS::UUID & uuid,
                                CUTS::TestLoggerServer_ptr server);

  virtual void unregister_server (const CUTS::UUID & uuid,
                                  CUTS::TestLoggerServer_ptr server);

  CUTS::TestLoggerFactory_ptr find (const CUTS::UUID & uuid) const;

private:
  /// POA for activating test logger factories.
  PortableServer::POA_var factory_poa_;

  /// Registration map for the test loggers.
  CUTS_Test_Logger_Map map_;
};

#endif  // !defined _CUTS_TEST_LOGGER_CLIENT_I_H_
