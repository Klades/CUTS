// -*- C++ -*-

//=============================================================================
/**
 * @file          TestLoggerFactory_i.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGER_FACTORY_I_H_
#define _CUTS_TEST_LOGGER_FACTORY_I_H_

#include "clientS.h"
#include "Logging_Client_export.h"
#include "ace/UUID.h"
#include "ace/Unbounded_Set.h"

/**
 * @class CUTS_TestLoggerFactory_i
 *
 * Implementation of the CUTS::TestLoggerClient interface.
 */
class CUTS_TestLoggerFactory_i :
  public POA_CUTS::TestLoggerFactory
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       uuid            Test number for the factory
   * @param[in]       poa             POA this object is activated in
   */
  CUTS_TestLoggerFactory_i (const ACE_Utils::UUID & uuid,
                            CUTS::TestLoggerServer_ptr server,
                            PortableServer::POA_ptr poa);

  /// Destructor.
  virtual ~CUTS_TestLoggerFactory_i (void);

  /**
   * Factory method for creating a new test logger for the
   * associated test.
   *
   * @return        The
   */
  virtual CUTS::TestLogger_ptr create (void);

  /**
   * Destory the specified logger. This will decrement is reference
   * count and remove it from the listing, if necessary.
   *
   * @param[in]       logger        Target logger to destroy.
   */
  virtual void destroy (CUTS::TestLogger_ptr logger);

  const ACE_Utils::UUID & test_uuid (void) const;

  CUTS::TestLoggerServer_ptr server (void);

  void server (CUTS::TestLoggerServer_ptr s);

private:
  /// Test number for the factory.
  ACE_Utils::UUID uuid_;

  /// Number of loggers.
  ACE_Atomic_Op <ACE_RW_Thread_Mutex, size_t> next_log_id_;

  /// POA that the test logger factory activated in.
  PortableServer::POA_var poa_;

  /// Reference to the logger server.
  CUTS::TestLoggerServer_var server_;
};

#if defined (__CUTS_INLINE__)
#include "TestLoggerFactory_i.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGER_FACTORY_I_H_
