// -*- C++ -*-

//=============================================================================
/**
 * @file        Record.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_RECORD_H_
#define _CUTS_DB_SQLITE_RECORD_H_

#include "DB_SQLite_export.h"
#include "cuts/utils/db/DB_Record.h"

// Forward decl.
class CUTS_DB_SQLite_Query;

/**
 * @class CUTS_DB_SQLite_Record
 *
 * Implemenation of the CUTS_DB_Record for SQLite.
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Record :
  public CUTS_DB_Record
{
public:
  /// Default constructor
  CUTS_DB_SQLite_Record (const CUTS_DB_SQLite_Query & query);

  /// Destructor
  virtual ~CUTS_DB_SQLite_Record (void);

  virtual size_t count (void) const;

  virtual size_t columns (void) const;

  virtual void advance (void);

  virtual bool done (void) const;

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
  /// SQLite statement for the record.
  const CUTS_DB_SQLite_Query & query_;

  int state_;
};

#if defined (__CUTS_INLINE__)
#include "Record.inl"
#endif

#endif  // !defined _CUTS_DB_SQLITE_RECORD_H_
