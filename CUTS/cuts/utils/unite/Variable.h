// -*- C++ -*-

//=============================================================================
/**
 * @file        Variable_Table.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_VARIABLE_H_
#define _CUTS_UNITE_VARIABLE_H_

#include "Unite_export.h"
#include "cuts/utils/db/SQLite/Parameter.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_DB_SQLite_Parameter;

/**
 * @class CUTS_Log_Format_Variable
 */
class CUTS_UNITE_Export CUTS_Log_Format_Variable
{
public:
  enum type_t
  {
    /// The variable type is unknown
    VT_UNKNOWN,

    /// The variable is a string
    VT_STRING,

    /// The variable is an integer
    VT_INTEGER,

    /// The varialbe is an float/double
    VT_DOUBLE
  };

  /// Destructor.
  virtual ~CUTS_Log_Format_Variable (void);

  virtual void value (const char * begin, const char * end) = 0;

  virtual void bind (CUTS_DB_SQLite_Parameter & param) = 0;

  size_t index (void) const;

  type_t type (void) const;

protected:
  /**
   * Initializing constructor
   *
   * @param[in]       type          The variable's type
   * @param[in]       index         The index of the variable.
   */
  CUTS_Log_Format_Variable (type_t type, size_t index);

private:
  /// The variable's type information
  type_t type_;

  /// The index of the variable.
  size_t index_;
};

/**
 * @class CUTS_String_Log_Format_Variable
 */
class CUTS_UNITE_Export CUTS_String_Log_Format_Variable :
  public CUTS_Log_Format_Variable
{
public:
  CUTS_String_Log_Format_Variable (size_t index);

  virtual ~CUTS_String_Log_Format_Variable (void);

  virtual void value (const char * begin, const char * end);

  virtual void bind (CUTS_DB_SQLite_Parameter & param);

private:
  ACE_CString value_;
};

/**
 * @class CUTS_Integer_Log_Format_Variable
 */
class CUTS_UNITE_Export CUTS_Integer_Log_Format_Variable :
  public CUTS_Log_Format_Variable
{
public:
  CUTS_Integer_Log_Format_Variable (size_t index);

  virtual ~CUTS_Integer_Log_Format_Variable (void);

  virtual void value (const char * begin, const char * end);

  virtual void bind (CUTS_DB_SQLite_Parameter & param);

private:
  int value_;
};

#if defined (__CUTS_INLINE__)
#include "Variable.inl"
#endif

#endif  // !defined _CUTS_UNITE_VARIABLE_H_
