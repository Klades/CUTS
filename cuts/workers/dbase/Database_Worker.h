// -*- C++ -*-

//=============================================================================
/**
 * @file    DatabaseWorker.h
 *
 * $Id$
 *
 * This class contains the default database worker for CUTS
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_DATABASE_WORKER_H_
#define _CUTS_DATABASE_WORKER_H_

#include "Database_Worker_export.h"
#include "cuts/Worker.h"
#include "adbc/ODBC/ODBC_Connection.h"
#include "ace/Auto_Ptr.h"
#include <string>

// Forward decl.
class CUTS_DB_Connection;

// Forward decl.
class CUTS_DB_Query;

/**
 * @class CUTS_Database_Worker
 *
 * Workload generator for database operations.
 */
class CUTS_DATABASE_WORKER_Export CUTS_Database_Worker :
  public CUTS_Worker
{
public:
  /// Constructor.
  CUTS_Database_Worker (void);

  /// Destructor.
  virtual ~CUTS_Database_Worker (void);

  /**
   * Excercise the database worker.
   *
   * @param[in]     reps       Number of repetitions.
   */
  virtual void process (size_t count);

  /**
   * Create a connection for the database worker to the
   * database on the specified host.
   *
   * @param[in]     hostname    Location of the database.
   */
  bool create_connection (const std::string & hostname);

  /// Destroy the database connection if it exists.
  void destroy_connection (void);

  /// Get the name of the host for the database.
  const char * hostname (void) const;

private:
  void fill_dataset (char * data, int size);

  /// Pointer to the database connection.
  ACE_Auto_Ptr <ADBC::ODBC::Connection> conn_;

  /// Pointer to the statement for the connection.
  ACE_Auto_Ptr <ADBC::ODBC::Query> stmt_;
};

#if defined (__CUTS_INLINE__)
#include "Database_Worker.inl"
#endif

#endif  // !defined _CUTS_DATABASE_WORKER_H_
