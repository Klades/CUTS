// -*- C++ -*-

#ifndef _CUTS_DB_SQLITE_PARAMATER_LIST_H_
#define _CUTS_DB_SQLITE_PARAMATER_LIST_H_

#include "Parameter.h"
#include "cuts/utils/db/DB_Parameter_List.h"
#include "ace/Array_Base.h"

// Forward decl.
class CUTS_DB_SQLite_Query;

/**
 * @class CUTS_DB_SQLite_Parameter_List
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Parameter_List :
  public CUTS_DB_Parameter_List
{
public:
  /// Default constructor.
  CUTS_DB_SQLite_Parameter_List (const CUTS_DB_SQLite_Query & parent);

  virtual ~CUTS_DB_SQLite_Parameter_List (void);

  virtual const CUTS_DB_SQLite_Parameter & operator [] (size_t index) const;

  virtual CUTS_DB_SQLite_Parameter & operator [] (size_t index);

  virtual size_t size (void) const;

  const CUTS_DB_SQLite_Query & owner (void) const;

  /// Reset the size of the parameter list.
  void reset (void);

private:
  typedef ACE_Array_Base <CUTS_DB_SQLite_Parameter> array_type;

  const CUTS_DB_SQLite_Query & parent_;

  array_type params_;
};

#if defined (__CUTS_INLINE__)
#include "Parameter_List.inl"
#endif

#endif  // !defined _CUTS_DB_SQLITE_PARAMATER_LIST_H_
