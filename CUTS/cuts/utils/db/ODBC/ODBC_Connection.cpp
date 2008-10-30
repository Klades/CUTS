// $Id$

#include "ODBC_Connection.h"
#include "ODBC_Query.h"

#if !defined (__CUTS_INLINE__)
#include "ODBC_Connection.inl"
#endif

#include "ace/Log_Msg.h"
#include <sstream>
#include <algorithm>

//
// ODBC_Connection
//
ODBC_Connection::ODBC_Connection (void)
: env_ (SQL_NULL_HANDLE),
  conn_ (SQL_NULL_HANDLE)
{
  // Allocate environment handle. Eventually we would like to be
  // able to attach to user-defined environments.
  SQL_VERIFY (::SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->env_),
              ODBC_Env_Exception (this->env_));

  // Set the version of ODBC. Right now we only support ODBC 3.x
  SQL_VERIFY (::SQLSetEnvAttr (this->env_,
                               SQL_ATTR_ODBC_VERSION,
                               (void *)SQL_OV_ODBC3,
                               0),
              ODBC_Env_Exception (this->env_));

  // Allocate the connection handle.
  SQL_VERIFY (::SQLAllocHandle (SQL_HANDLE_DBC, this->env_, &this->conn_),
              ODBC_Env_Exception (this->env_));
}

//
// ~ODBC_Connection
//
ODBC_Connection::~ODBC_Connection (void)
{
  // release the resource for the connection
  if (this->conn_ != SQL_NULL_HANDLE)
    ::SQLFreeHandle (SQL_HANDLE_DBC, this->conn_);

  // free the environment variable
  if (this->env_ != SQL_NULL_HANDLE)
    ::SQLFreeHandle (SQL_HANDLE_ENV, this->env_);
}

//
// connect
//
void ODBC_Connection::connect (const ACE_CString & username,
                               const ACE_CString & password,
                               const ACE_CString & server,
                               int port)
{
  // Genereate the connection string for MySQL.
  std::ostringstream connstr;

#if defined (_WIN32) || defined (WIN32)
  connstr << "Driver={MySQL ODBC 3.51 Driver};"
          << "Uid=" << username.c_str () << ";"
          << "Pwd=" << password.c_str () << ";"
#else
  connstr << "Dsn=CUTS;"
          << "User=" << username.c_str () << ";"
          << "Password=" << password.c_str () << ";"
#endif  // defined _WIN32
          << "Database=cuts;"
          << "Server=" << server.c_str () << ";"
          << "Port=" << port << ";"
          << "Option=3;" << std::ends;

  this->connect_i (connstr.str ().c_str (), connstr.str ().length ());
}

//
// connect
//
void ODBC_Connection::connect (const ACE_CString & connstr)
{
  this->connect_i (connstr.c_str (), connstr.length ());
}

//
// connect_i
//
void ODBC_Connection::connect_i (const char * connstr, size_t length)
{
  short result = 0;
  SQLCHAR tempstr[1024];

  // Remove this connection.
  this->disconnect ();

  SQL_VERIFY (
    ::SQLDriverConnect (this->conn_,
                        0,
                        (SQLCHAR *) connstr,
                        length,
                        tempstr,
                        sizeof (tempstr),
                        &result,
                        SQL_DRIVER_NOPROMPT),
    ODBC_Conn_Exception (this->conn_));

  // Pass control to the base class.
  CUTS_DB_Connection::connect (ACE_CString (connstr, length, 0, false));
}

//
// disconnect
//
void ODBC_Connection::disconnect (void)
{
  if (this->conn_ != SQL_NULL_HDBC && this->connected_)
  {
    SQL_VERIFY (::SQLDisconnect (this->conn_),
                ODBC_Conn_Exception (this->conn_));
  }

  // Pass control to the base class.
  CUTS_DB_Connection::disconnect ();
}

//
// create_odbc_query
//
ODBC_Query * ODBC_Connection::create_odbc_query (void)
{
  ODBC_Query * query = 0;
  ACE_NEW_RETURN (query, ODBC_Query (this->conn_), 0);

  return query;
}

//
// create_query
//
CUTS_DB_Query * ODBC_Connection::create_query (void)
{
  return this->create_odbc_query ();
}
