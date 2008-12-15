// $Id$

#include "Test_Logging_Callback.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Logging_Callback.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/testing/Test_Database.h"
#include "boost/bind.hpp"
#include <algorithm>

static const char * __CREATE_CUTS_LOGGING_TABLE__ =
"CREATE TABLE IF NOT EXISTS cuts_logging"
"("
"lid INTEGER PRIMARY KEY AUTOINCREMENT,"
"timeofday DATETIME,"
"severity INTEGER,"
"hostname VARCHAR,"
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
// handle_messeages
//
void CUTS_Test_Logging_Callback::
handle_messages (const CUTS::LogMessagePacket & packet)
{
  try
  {
    static const char * __INSERT_STMT__ =
      "INSERT INTO cuts_logging (timeofday, severity, hostname, message) "
      "VALUES (?, ?, ?, ?)";

    // Create a new query object.
    CUTS_DB_Query * query = this->test_db_->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    // Prepare the statement.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - preparing the insert statement\n"));

    query->prepare (__INSERT_STMT__);

    // Bind the hostname since it will never change.
    query->parameters ()[2].bind (packet.hostname.in (),
                                  ACE_OS::strlen (packet.hostname.in ()));

    CORBA::Long msg_count = packet.messages.length ();

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - inserting %d messages into the database\n",
                msg_count));

    std::for_each (packet.messages.get_buffer (),
                   packet.messages.get_buffer () + msg_count,
                   boost::bind (&CUTS_Test_Logging_Callback::insert_message,
                                query,
                                _1));
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }
}

//
// insert_message
//
void CUTS_Test_Logging_Callback::
insert_message (CUTS_DB_Query * query, const CUTS::LogMessage & msg)
{
  try
  {
    ACE_Time_Value tv (msg.timestamp.sec, msg.timestamp.usec);
    ACE_INT16 severity = msg.severity;

    // Bind the remaining parameters.
    const char * ts = "2008-12-21 12:12:12";
    query->parameters ()[0].bind (ts, ACE_OS::strlen (ts));
    query->parameters ()[1].bind (severity);
    query->parameters ()[3].bind (msg.message.get_buffer (),
                                  msg.message.length ());

    // Insert the data into the database.
    query->execute_no_record ();
    query->reset ();
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }
}

//
// init
//
int CUTS_Test_Logging_Callback::init (void)
{
  try
  {
    // Try to create the logging table in the database.
    CUTS_DB_Query * query = this->test_db_.create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - initializing CUTS logging data table(s)\n"));

    for (size_t i = 0; i < INIT_STMT_COUNT; ++ i)
      query->execute_no_record (__INIT_STMTS__[i]);

    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  return -1;
}
