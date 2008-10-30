// -*- C++ -*-

//=============================================================================
/**
 * @file        Connection.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_CONNECTION_H_
#define _CUTS_DB_SQLITE_CONNECTION_H_

#include "cuts/utils/db/DB_Connection.h"
#include "ace/SString.h"
#include "Query.h"

/**
 * @class CUTS_DB_SQLite_Connection
 *
 * Implementation of a SQLite connection.
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Connection :
  public CUTS_DB_Connection
{
  friend class CUTS_DB_SQLite_Query;

public:
  /// Default constructor
  CUTS_DB_SQLite_Connection (void);

  /// Destructor.
  virtual ~CUTS_DB_SQLite_Connection (void);

  void connect (const ACE_CString & connstr, long flags, const char * vfs = 0);

  virtual void connect (const ACE_CString & connstr);

  /// Disconnect from the database.
  virtual void disconnect (void);

  virtual CUTS_DB_SQLite_Query * create_query (void);

private:
  /// Connection the database.
  sqlite3 * conn_;
};

#endif  // !defined _CUTS_DB_SQLITE_CONNECTION_H_
