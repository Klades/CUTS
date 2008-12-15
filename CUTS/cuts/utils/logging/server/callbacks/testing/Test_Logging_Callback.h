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

#include "Test_Logging_Callback_export.h"
#include "cuts/utils/logging/server/serverC.h"

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_DB_Query;

/**
 * @class CUTS_Test_Logging_Callback
 *
 * Test logging server callback that inserts messages into a CUTS
 * test database.
 */
class CUTS_TEST_LOGGING_CALLBACK_Export CUTS_Test_Logging_Callback :
  public CUTS::TestLoggerServerCallback
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       test_db         Target test database
   */
  CUTS_Test_Logging_Callback (CUTS_Test_Database & test_db);

  /// Destructor.
  virtual ~CUTS_Test_Logging_Callback (void);

  int init (void);

  /**
   * Callback for handling a message packet
   *
   * @param[in]       packet          Packet of log messages
   */
  virtual void handle_messages (const CUTS::LogMessagePacket & packet);

private:
  /// Helper method for inserting message into database
  static void insert_message (CUTS_DB_Query *, const CUTS::LogMessage &);

  /// Reference to the test database.
  CUTS_Test_Database & test_db_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Logging_Callback.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_CALLBACK_H_
