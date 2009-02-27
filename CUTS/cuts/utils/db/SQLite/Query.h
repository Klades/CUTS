// -*- C++ -*-

//=============================================================================
/**
 * @file        Query.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_QUERY_H_
#define _CUTS_DB_SQLITE_QUERY_H_

#include "Record.h"
#include "Parameter_List.h"
#include "cuts/utils/db/DB_Query.h"

// Forward decl.
class CUTS_DB_SQLite_Connection;

// Forward decl.
struct sqlite3_stmt;

/**
 * @class CUTS_DB_SQLite_Query
 *
 * Implemenation of the CUTS_DB_Query class for SQLite
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Query : public CUTS_DB_Query
{
  // Friend decl.
  friend class CUTS_DB_SQLite_Record;

  // Friend decl.
  friend class CUTS_DB_SQLite_Parameter_List;

  // Friend decl.
  friend class CUTS_DB_SQLite_Parameter;

public:
  /// Default constructor
  CUTS_DB_SQLite_Query (CUTS_DB_SQLite_Connection & parent);

  /// Destructor
  virtual ~CUTS_DB_SQLite_Query (void);

  /**
   * Prepare a statement for execution.
   *
   * @param[in]     query     NULL-terminated query string.
   */
  virtual void prepare (const char * query);

  /**
   * Prepare a statement for execution.
   *
   * @param[in]     query     NULL-terminated query string.
   */
  virtual void prepare (const char * query, size_t len);

  /// Destroy the query. The queury is no longer usable after
  /// this method returns.
  virtual void destroy (void);

  /**
   * Directly execute a database query.
   *
   * @param[in]     query     NULL-terminated query string.
   */
  virtual void execute_no_record (const char * query);

  /// Execute an already prepared query.
  virtual void execute_no_record (void);

  /**
   * Execute a query. This method is useful with the query is known
   * to return results that will consist of multiple data rows, and
   * columns. The client has the responsibility of delete the record
   * once its done with it.
   *
   * @return  Pointer to a record.
   */
  virtual CUTS_DB_SQLite_Record * execute (const char * query);

  /**
   * Execute a prepared query. This method is useful with the query is
   * known to return results that will consist of multiple data rows,
   * and columns. The client has the responsibility of delete the record
   * once its done with it.
   *
   * @return  Pointer to a record.
   */
  virtual CUTS_DB_SQLite_Record * execute (void);

  /// Cancel the current query.
  virtual void cancel (void);

  /**
   * Get the last insert id. This method is only value if an
   * insert was made to a table with an \a auto_increment field.
   *
   * @return The last id inserted.
   */
  virtual long last_insert_id (void);

  virtual CUTS_DB_SQLite_Parameter_List & parameters (void);

  virtual const CUTS_DB_SQLite_Parameter_List & parameters (void) const;

  /// Reset the query string.
  virtual void reset (void);

private:
  void finalize (void);

  /// Owner of the query.
  CUTS_DB_SQLite_Connection & parent_;

  /// Actual SQLite3 statement.
  ::sqlite3_stmt * stmt_;

  bool needs_reseting_;

  /// Collection of parameters for this query.
  CUTS_DB_SQLite_Parameter_List params_;
};

#endif  // !defined _CUTS_DB_SQLITE_QUERY_H_
