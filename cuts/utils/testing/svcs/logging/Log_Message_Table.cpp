// $Id$

#include "Log_Message_Table.h"

#if !defined (__CUTS_INLINE__)
#include "Log_Message_Table.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/testing/Test_Database.h"

static const char * __CREATE_CUTS_LOGGING_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_logging"
"("
"lid INTEGER PRIMARY KEY AUTOINCREMENT,"
"timeofday DATETIME,"
"severity INTEGER,"
"hostname VARCHAR,"
"thread_id INTEGER,"
"message TEXT"
")";

static const char * __CREATE_INDEX_CUTS_LOGGING_MESSAGE__ =
"CREATE INDEX IF NOT EXISTS cuts_logging_message ON cuts_logging (message)";

#define INIT_STMT_COUNT 2

static const char * __INIT_STMTS__[INIT_STMT_COUNT] =
{
  __CREATE_CUTS_LOGGING_TABLE__,
  __CREATE_INDEX_CUTS_LOGGING_MESSAGE__
};

//
// init
//
int CUTS_Log_Message_Table::init (void)
{
  // Try to create the logging table in the database.
  ADBC::Query * query = this->test_db_.create_query ();
  CUTS_Auto_Functor_T <ADBC::Query> auto_clean (query, &ADBC::Query::destroy);

  for (size_t i = 0; i < INIT_STMT_COUNT; ++ i)
    query->execute_no_record (__INIT_STMTS__[i]);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Log_Message_Table_Insert_Stmt
