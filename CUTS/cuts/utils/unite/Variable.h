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
 * @class CUTS_Basic_Log_Format_Variable_T
 */
template <typename T>
class CUTS_Basic_Log_Format_Variable_T :
  public CUTS_Log_Format_Variable
{
public:
  /// Type definition of the integer type.
  typedef T type;

  CUTS_Basic_Log_Format_Variable_T (size_t index);

  virtual ~CUTS_Basic_Log_Format_Variable_T (void);

  virtual void value (const char * begin, const char * end);

  virtual void bind (CUTS_DB_SQLite_Parameter & param);

private:
  T value_;
};

/**
 * @struct CUTS_Log_Format_Variable_Type_T
 *
 * Trait class for determining a variables type.
 */
template <typename T>
struct CUTS_Log_Format_Variable_Type_T 
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_UNKNOWN;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_INT16>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_UINT16>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_INT32>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_UINT32>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_INT64>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

template < >
struct CUTS_Log_Format_Variable_Type_T <ACE_UINT64>
{
  static const CUTS_Log_Format_Variable::type_t result_type = CUTS_Log_Format_Variable::VT_INTEGER;
};

#if defined (__CUTS_INLINE__)
#include "Variable.inl"
#include "Variable_T.inl"
#endif

#include "Variable_T.cpp"

#endif  // !defined _CUTS_UNITE_VARIABLE_H_
