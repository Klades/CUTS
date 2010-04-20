// $Id$

#include "Testing_LoggingServerListener_i.h"
#include "Log_Message_Table.h"
#include "cuts/Auto_Functor_T.h"
#include "adbc/SQLite/Types.h"
#include "cuts/utils/testing/Test_Database.h"
#include "boost/bind.hpp"
#include "ace/Trace.h"

/**
 * @struct insert_message
 *
 * Functor for inserting a log message into the database.
 */
struct insert_message
{
  /**
   * Initializing constructor.
   *
   * @param[in]       insert_stmt     The insert SQL statement.
   */
  insert_message (CUTS_Log_Message_Table::INSERT_STMT & insert_stmt)
    : insert_stmt_ (insert_stmt)
  {

  }

  /**
   * Functor operator
   */
  void operator () (const CUTS::LogMessage & msg)
  {
    ACE_Time_Value tv (msg.timestamp.sec, msg.timestamp.usec);
    ACE_Date_Time dt (tv);
    ADBC::SQLite::Date_Time timeofday (dt);
    ACE_INT16 severity = msg.severity;

    // Bind the remaining parameters.
    this->insert_stmt_.bind_timeofday (timeofday);
    this->insert_stmt_.bind_severity (severity);
    this->insert_stmt_.bind_message (msg.message.get_buffer (),
                                     msg.message.length ());

    // Execute and reset the insert statement.
    this->insert_stmt_.execute ();
    this->insert_stmt_.reset ();
  }

private:
  CUTS_Log_Message_Table::INSERT_STMT & insert_stmt_;
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
    ADBC::Query * query = this->database_->create_query ();
    CUTS_Auto_Functor_T <ADBC::Query> auto_clean (query, &ADBC::Query::destroy);

    // Start a new transaction.
    query->execute_no_record ("BEGIN TRANSACTION");

    // Prepare the statement for inserting messages.
    CUTS_Log_Message_Table msg_table (*this->database_);

    CUTS_Log_Message_Table::INSERT_STMT insert_stmt (*query);
    insert_stmt.prepare ();
    insert_stmt.bind_hostname (hostname);

    // Insert each message into the database.
    std::for_each (msgs.get_buffer (),
                   msgs.get_buffer () + msgs.length (),
                   insert_message (insert_stmt));

    // End the current transaction.
    query->execute_no_record ("COMMIT");
  }
  catch (const ADBC::Exception & ex)
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
  if (0 == database)
    return -1;

  try
  {
    // Initialize the database with the log message table.
    CUTS_Log_Message_Table msg_table (*database);
    int retval = msg_table.init ();

    // Save the database if initialized correctly.
    if (0 == retval)
      this->database_ = database;

    return retval;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
  }

  return -1;
}

