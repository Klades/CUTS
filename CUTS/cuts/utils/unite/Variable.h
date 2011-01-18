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

#include "ace/SString.h"
#include "Unite_export.h"
#include "adbc/SQLite/Parameter.h"
#include "ace/Date_Time.h"
#include <sstream>

namespace ADBC
{
namespace SQLite
{
class Parameter;
}
}

/**
 * @ingroup UNITE_Core
 *
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
    VT_DOUBLE,

  /// The varialbe is a Date_time
    VT_DATETIME,

  /// The variable is a Regular expression
    VT_REGEX

};

  /// Destructor.
  virtual ~CUTS_Log_Format_Variable (void);

   /**
   * Set the variable values using the two end pointers
   * @param[in]     begin    starting pointer of the string
   * @param[in]     end      endpoint of the string
   */
  virtual void value (const char * begin, const char * end) = 0;

  /// Binds the corresponding sqlite prameter
  virtual void bind (ADBC::SQLite::Parameter & param) = 0;

  /// Set the value straightaway from a string
  virtual void value (char * val) = 0;

  /// Posiiton of the variables array
  size_t index (void) const;

  /// Type of the variable
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

  virtual void bind (ADBC::SQLite::Parameter & param);

  virtual void value (char * val);


private:
  ACE_CString value_;
};

/**
 * @class CUTS_Datetime_Log_Format_Variable
 */
class CUTS_UNITE_Export CUTS_Datetime_Log_Format_Variable :
  public CUTS_Log_Format_Variable
{
public:
  /// Construtor
  CUTS_Datetime_Log_Format_Variable (size_t index, const std::string format);

  virtual ~CUTS_Datetime_Log_Format_Variable (void);

  virtual void value (const char * begin, const char * end);

  virtual void bind (ADBC::SQLite::Parameter & param);

  virtual void value (char * val);

  /// Set the corresponding ACE Date_Time
  void date_time (ACE_Date_Time & dt);

  /// Get the user specified Date_Time format
  const std::string format ();

  // Get the constructed Date_Time object
  ACE_Date_Time date_time ();


private:
  /* String representing the Datetime format specified by the user */
  const std::string format_;

  /* The Corresponding ACE_Date_Time object */
  ACE_Date_Time date_time_;
};


/**
 * @class CUTS_Datetime_Log_Format_Variable
 */
class CUTS_UNITE_Export CUTS_Regex_Log_Format_Variable :
  public CUTS_Log_Format_Variable
{
public:
  CUTS_Regex_Log_Format_Variable (size_t index, const std::string format);

  virtual ~CUTS_Regex_Log_Format_Variable (void);

  virtual void value (const char * begin, const char * end);

  virtual void bind (ADBC::SQLite::Parameter & param);

  virtual void value (char *val);

  const std::string format ();


private:
  /* String representing the Regex format specified by the user */
  const std::string format_;

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

  virtual void bind (ADBC::SQLite::Parameter & param);

  virtual void value (char * val);

  /// Set the value of the variable straightaway using the type
  void value (T val);

private:
  /// Value of the variable in the variable's type
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