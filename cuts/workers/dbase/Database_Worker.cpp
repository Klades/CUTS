// $Id$

#include "Database_Worker.h"

#if !defined (__CUTS_INLINE__)
#include "Database_Worker.inl"
#endif

#include "adbc/Query.h"
#include "ace/Basic_Types.h"
#include "ace/CORBA_macros.h"
#include "ace/OS_Memory.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/Log_Msg.h"
#include <sstream>

#define MAX_DATA_SIZE 255

//
// CUTS_DatabaseWorker
//
CUTS_Database_Worker::CUTS_Database_Worker (void)
{
  // Allocate a new <MyODBC_Connection> object.
  ADBC::ODBC::Connection * conn = 0;

  ACE_NEW_THROW_EX (conn,
                    ADBC::ODBC::Connection (),
                    ACE_bad_alloc ());

  this->conn_.reset (conn);
}

//
// process
//
void CUTS_Database_Worker::process (size_t count)
{
  if (this->stmt_.get ())
  {
    try
    {
      std::ostringstream sqlstr;
      char dataset[MAX_DATA_SIZE];

      long worktag = ACE_OS::rand () % ACE_INT32_MAX;

      for (size_t i = 0; i < count; i ++)
      {
        int size = ACE_OS::rand () % MAX_DATA_SIZE;
        fill_dataset (dataset, size);

        // create a SQL statement for the testing record
        sqlstr
          << "insert into scratchpad (component_id, worktag, dataset) values ("
          << this->parent_ << "," << worktag << ",'" << dataset << "');"
          << std::ends;
      }

      this->stmt_->execute_no_record (sqlstr.str ().c_str ());

      sqlstr.str ("");
      sqlstr.clear ();

      // Delete the insert SQL statement.
      sqlstr
        << "DELETE FROM scratchpad WHERE component_id = "
        << this->parent_ << " AND worktag = " << worktag << ";" << std::ends;

      this->stmt_->execute_no_record (sqlstr.str ().c_str ());
    }
    catch (const ADBC::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T - %M - %s\n"),
                  ex.message ().c_str ()));
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T - %M - caught unknown exceptions\n")));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "[%M] -%T - No ODBC statement allocated. Please verify "
                "you are connected to a database\n"));
  }
}

//
// create_connection
//
bool CUTS_Database_Worker::create_connection (const std::string & connstr)
{
  // We need to kill any existing connections before we
  // continue. This also involves killing the associated
  // <stmt_> for the connection.
  this->destroy_connection ();

  try
  {
    // We are now ready to establish a new connection to the specified
    // hostname.
    this->conn_->connect (connstr.c_str ());

    // We need to allocate an <ODBC_Stmt> for the connection.
    // This will prevent us from having to allocate one each
    // time.
    ADBC::ODBC::Query * query = 0;
    ACE_NEW_THROW_EX (query,
                      ADBC::ODBC::Query (*this->conn_),
                      ACE_bad_alloc ());

    this->stmt_.reset (query);
    return true;
  }
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - %s\n"),
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T - %M - caught unknown exceptions\n")));
  }

  return false;
}

//
// fill_dataset
//
void CUTS_Database_Worker::fill_dataset (char * dataset, int size)
{
  // determine the fill character
  static char fill_value =
    static_cast <int> (fill_value) >= static_cast <int> ('Z')
    ? 'A' : fill_value + 1;

  // fill the dataset with the next value
  char * endpoint = dataset + size;
  std::fill (dataset, endpoint, fill_value);
  dataset[size] = '\0';
}

//
// destroy_connection
//
void CUTS_Database_Worker::destroy_connection (void)
{
  if (this->conn_->is_connected ())
  {
    this->stmt_.reset ();
    this->conn_->disconnect ();
  }
}
