// -*- C++ -*-

#ifndef _CUTS_DB_SQLITE_TYPES_H_
#define _CUTS_DB_SQLITE_TYPES_H_

#include "DB_SQLite_export.h"
#include "cuts/utils/db/DB_Types_Impl.h"
#include "ace/Date_Time.h"

class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Date_Time :
  public CUTS_DB_Date_Time_Impl
{
public:
  CUTS_DB_SQLite_Date_Time (void);

  CUTS_DB_SQLite_Date_Time (const ACE_Date_Time & dt);

  virtual ~CUTS_DB_SQLite_Date_Time (void);

  virtual long month (void) const;

  virtual void month (long val);

  virtual long day (void) const;

  virtual void day (long val);

  virtual long year (void) const;

  virtual void year (long value);

  virtual long hour (void) const;

  virtual void hour (long);

  virtual long minute (void) const;

  virtual void minute (long value);

  virtual long second (void) const;

  virtual void second (long value);

  virtual long fraction (void) const;

  virtual void fraction (long val);

  virtual void * value_i (void);

private:
  /// The actual date time.
  ACE_Date_Time dt_;
};

#if defined (__CUTS_INLINE__)
#include "Types.inl"
#endif

#endif  // !defined _CUTS_DB_SQLITE_TYPES_H_
