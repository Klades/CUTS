// -*- C++ -*-

//=============================================================================
/**
 * @file        Exception.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_EXCEPTION_H_
#define _CUTS_DB_SQLITE_EXCEPTION_H_

#include "cuts/utils/db/DB_Exception.h"
#include "DB_SQLite_export.h"
#include "sqlite3.h"

/**
 * @class CUTS_DB_SQLite_Exception
 *
 * Implementation of the exception class for SQLite
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Exception :
  public CUTS_DB_Exception
{
public:
  /// Default constructor
  CUTS_DB_SQLite_Exception (void);

  /**
   * Initializing constructor
   *
   * @param[in]       err_code      Error code for the exception
   */
  CUTS_DB_SQLite_Exception (long err_code);

  /// Destructor
  virtual ~CUTS_DB_SQLite_Exception (void);

private:
  /// Listing of error messages.
  static const char * error_msgs_[27];
};

#endif  // !defined _CUTS_DB_SQLITE_EXCEPTION_H_
