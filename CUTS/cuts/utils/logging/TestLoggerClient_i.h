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

#include "loggingS.h"
#include "cuts/utils/ODBC/ODBC_Connection.h"
#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"

// Forward decl.
class CUTS_TestLoggerFactory_i;

/**
 * @class CUTS_TestLoggerClient_i
 *
 * Implementation of the CUTS::TestLoggerClient interface. This object
 * is not thread-safe and must be activated under the RootPOA, or a
 * single-threaded POA. Otherwise, unknown behavior many occur.
 */
class CUTS_TestLoggerClient_i :
  public POA_CUTS::TestLoggerClient
{
public:
  /// Default constructor.
  CUTS_TestLoggerClient_i (PortableServer::POA_ptr root_poa);

  /// Destructor.
  virtual ~CUTS_TestLoggerClient_i (void);

  /**
   * Create a new factory object for the test.
   *
   * @param[in]       test_number       The new test.
   */
  virtual CUTS::TestLoggerFactory_ptr create (CORBA::Long test_number);

  /**
   * Destroy the logger factory for a test. At this stage, we can assume
   * the logger factory as cleaned all its resources and is ready to
   * be removed from memory.
   */
  virtual void destroy (CUTS_TestLoggerFactory_i * factory);

private:
  /// Implementation of the destroy () method.
  void destroy_i (CUTS_TestLoggerFactory_i * factory);

  /// Reference to the RootPOA.
  PortableServer::POA_var root_poa_;

  /// Type definition of the factory mapping for tests.
  typedef
    ACE_Hash_Map_Manager <long,
                          CUTS_TestLoggerFactory_i *,
                          ACE_Null_Mutex> map_type;

  /// Factory map for each test.
  map_type factory_map_;
};

#endif  // !defined _CUTS_TEST_LOGGER_CLIENT_I_H_
