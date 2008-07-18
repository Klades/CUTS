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

#include "loggingS.h"
#include "cuts/utils/ODBC/ODBC_Connection.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class CUTS_TestLogger_i;

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
   * @param[in]       root            Child POA for the test.
   * @param[in]       test_number     Test number for the factory.
   */
  CUTS_TestLoggerFactory_i (long test_number, PortableServer::POA_ptr poa);

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
  void destroy (CUTS_TestLogger_i * logger);

  /**
   * Set the address of the database server.
   */
  void database (const ACE_CString & addr);

  /**
   * Set the timeout interval for flushing the message queue.
   */
  void timeout_interval (const ACE_Time_Value & tv);

  /**
   * Get the database connection for the logger factory. This connection
   * should already be open.
   *
   * @return          The database connection.
   */
  CUTS_DB_Connection & connection (void);

  /**
   * Get the POA assigned to the test logger factory.
   *
   * @return          The assigned POA.
   */
  PortableServer::POA_ptr poa (void);

private:
  void unregister_test_i (long test);

  /// Test number for the factory.
  long test_number_;

  /// POA assigned to this test.
  PortableServer::POA_var test_poa_;

  /// The servant for the logger.
  ACE_Unbounded_Set <CUTS_TestLogger_i *> servants_;

  /// The database connection for the client.
  ODBC_Connection conn_;

  /// The hostname of the logging client.
  ACE_Auto_String_Free hostname_;

  ACE_Thread_Mutex lock_;
};

#endif  // !defined _CUTS_TEST_LOGGER_FACTORY_I_H_
