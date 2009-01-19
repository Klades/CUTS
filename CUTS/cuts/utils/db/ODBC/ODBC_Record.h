// -*- C++ -*-

//=============================================================================
/**
 * @file      ODBC_Record.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ODBC_RECORD_H_
#define _CUTS_ODBC_RECORD_H_

#include "ODBC_Base.h"
#include "ODBC_Exception.h"
#include "cuts/utils/db/DB_Record.h"

// Forward decl.
class ODBC_Query;

/**
 * @class ODBC_Record
 *
 * @brief ODBC implementation of the CUTS_DB_Record class.
 */
class CUTS_ODBC_Export ODBC_Record :
  public ODBC_Base,
  public CUTS_DB_Record
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]     handle      Statement handle.
   */
  ODBC_Record (const ODBC_Query & query);

  /// Destructor.
  virtual ~ODBC_Record (void);

  /// Fetch the next row in the records.
  virtual void advance (void);

  /// Get the number of records
  virtual size_t count (void) const;

  virtual bool done (void) const;

  /**
   * Get the number of columns in the result.
   *
   * @return Number of columns.
   */
  virtual size_t columns (void) const;

  virtual void get_data (size_t column, char * buffer, size_t bufsize);

  virtual void get_data (size_t column, char & value);

  virtual void get_data (size_t column, unsigned char & value);

  virtual void get_data (size_t column, short & value);

  virtual void get_data (size_t column, unsigned short & value);

  virtual void get_data (size_t column, long & value);

  virtual void get_data (size_t column, unsigned long & value);

  virtual void get_data (size_t column, float & value);

  virtual void get_data (size_t column, double & value);

  virtual void get_data (size_t column, ACE_Date_Time & datetime);

private:
  /// Help method that wraps the SQLGetData method.
  void get_data_i (SQLUSMALLINT column,
                   SQLSMALLINT target_type,
                   SQLPOINTER target,
                   SQLINTEGER bufsize,
                   SQLINTEGER * result);

  /// ODBC statement resource handle.
  const ODBC_Query & query_;

  /// Current location in the record set.
  size_t curr_;

  /// Number of records.
  size_t count_;

  /// Number of columns in the record set.
  size_t columns_;
};

#if defined (__CUTS_INLINE__)
#include "ODBC_Record.inl"
#endif

#endif  // !defined _CUTS_ODBC_RECORD_H_
