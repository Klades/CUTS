// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Logging_Callback.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGING_CALLBACK_H_
#define _CUTS_TEST_LOGGING_CALLBACK_H_

#include "cuts/utils/logging/server/serverC.h"

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_DB_Query;

/**
 * @class CUTS_Test_Logging_Callback
 */
class CUTS_Test_Logging_Callback :
  public CUTS::TestLoggerServerCallback
{
public:
  /// Default constructor.
  CUTS_Test_Logging_Callback (CUTS_Test_Database & test_db);

  /// Destructor.
  virtual ~CUTS_Test_Logging_Callback (void);

  virtual void handle_messages (const CUTS::LogMessagePacket & packet);

private:
  /**
   * Helper method to insert a message using the specified query.
   */
  static void insert_message (CUTS_DB_Query * query,
                              const CUTS::LogMessage & msg);

  /// Reference to the test database.
  CUTS_Test_Database & test_db_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Logging_Callback.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_CALLBACK_H_
