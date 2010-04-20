// -*- C++ -*-

//=============================================================================
/**
 * @file        Testing_Log_Message_Listener.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOG_MESSAGE_TABLE_H_
#define _CUTS_LOG_MESSAGE_TABLE_H_

#include "Testing_Log_Message_Listener_export.h"
#include "adbc/Parameter.h"
#include "adbc/Parameter_List.h"
#include "adbc/Query.h"
#include "adbc/SQLite/Types.h"
#include "ace/OS_NS_string.h"

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_Log_Message_Table_Insert_Stmt;

/**
 * @class CUTS_Log_Message_Table
 *
 * Helper class for managing the log message table in a database. This
 * class has methods for ensuring the table is properly initialized
 * in the target database. It also contains methods for inserting
 * messages into the database.
 */
class CUTS_TESTING_LOG_MESSAGE_LISTENER_Export CUTS_Log_Message_Table
{
public:
  /// Type definition of the insert statement for the table.
  typedef CUTS_Log_Message_Table_Insert_Stmt INSERT_STMT;

  /**
   * Initializing constructor
   *
   * @param[in]     test_db       Target test database.
   */
  CUTS_Log_Message_Table (CUTS_Test_Database & test_db);

  /// Destructor
  ~CUTS_Log_Message_Table (void);

  /// Initialize the table on the database.
  int init (void);

private:
  /// Target test database for table.
  CUTS_Test_Database & test_db_;

  /// Query for SQL statements.
  ADBC::Query * query_;
};

/**
 * @class CUTS_Log_Message_Table_Insert_Stmt
 */
class CUTS_TESTING_LOG_MESSAGE_LISTENER_Export CUTS_Log_Message_Table_Insert_Stmt
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       query         Target query for statement.
   */
  CUTS_Log_Message_Table_Insert_Stmt (ADBC::Query & query);

  /// Destructor.
  ~CUTS_Log_Message_Table_Insert_Stmt (void);

  /// Prepare the statement for execution.
  void prepare (void);

  /// Execute the statement.
  void execute (void);

  /// Reset the statement.
  void reset (void);

  void bind_timeofday (ADBC::SQLite::Date_Time & timeofday);
  void bind_severity (ACE_INT16 & severity);
  void bind_hostname (const char * hostname);
  void bind_message (const char * msg, size_t length);

private:
  /// Target query for statement.
  ADBC::Query & query_;
};

#if defined (__CUTS_INLINE__)
#include "Log_Message_Table.inl"
#endif

#endif  // !defined _CUTS_LOG_MESSAGE_TABLE_H_
