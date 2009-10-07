// $Id$

#include "Testing_LoggingServerListener_i.h"
#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/testing/Test_Database.h"
#include "boost/bind.hpp"
#include "ace/Trace.h"

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

static const char * __INSERT_STMT__ =
  "INSERT INTO cuts_logging (timeofday, severity, hostname, message) "
  "VALUES (?, ?, ?, ?)";

struct insert_message
{
  insert_message (CUTS_DB_Query & query)
    : query_ (query)
  {

  }

  void operator () (const CUTS::LogMessage & msg)
  {
    ACE_Time_Value tv (msg.timestamp.sec, msg.timestamp.usec);
    ACE_Date_Time dt (tv);
    CUTS_DB_SQLite_Date_Time datetime (dt);

    ACE_INT16 severity = msg.severity;

    // Bind the remaining parameters.
    this->query_.parameters ()[0].bind (datetime);
    this->query_.parameters ()[1].bind (severity);
    this->query_.parameters ()[3].bind (msg.message.get_buffer (),
                                        msg.message.length ());

    // Insert the data into the database.
    this->query_.execute_no_record ();
    this->query_.reset ();
  }

private:
  CUTS_DB_Query & query_;
};

//
// CUTS_Testing_LoggingServerListener_i
//
CUTS_Testing_LoggingServerListener_i::CUTS_Testing_LoggingServerListener_i (void)
{

}

//
// ~CUTS_Testing_LoggingServerListener_i
//
CUTS_Testing_LoggingServerListener_i::~CUTS_Testing_LoggingServerListener_i (void)
{

}


//
// handle_messages
//
void CUTS_Testing_LoggingServerListener_i::
handle_messages (const char * hostname,
                 const ::CUTS::UUID & test,
                 const ::CUTS::LogMessages & msgs)
{
  try
  {
    ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->mutex_);

    if (0 == this->database_)
      return;

    // Create a new query object.
    CUTS_DB_Query * query = this->database_->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    query->execute_no_record ("BEGIN TRANSACTION");
    query->prepare (__INSERT_STMT__);

    // Bind the hostname since it will never change.
    query->parameters ()[2].bind (hostname, ACE_OS::strlen (hostname));

    ::CORBA::ULong msg_count = msgs.length ();

    std::for_each (msgs.get_buffer (),
                   msgs.get_buffer () + msg_count,
                   insert_message (*query));

    query->execute_no_record ("COMMIT");
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception (%N:%l)\n")));
  }
}

//
// init
//
int CUTS_Testing_LoggingServerListener_i::init (CUTS_Test_Database * database)
{
  try
  {
    // Try to create the logging table in the database.
    CUTS_DB_Query * query = database->create_query ();
    CUTS_Auto_Functor_T <CUTS_DB_Query> auto_clean (query, &CUTS_DB_Query::destroy);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - initializing CUTS logging data table(s)\n"));

    for (size_t i = 0; i < INIT_STMT_COUNT; ++ i)
      query->execute_no_record (__INIT_STMTS__[i]);

    this->database_ = database;
    return 0;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

