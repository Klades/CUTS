// -*- C++ -*-

//=============================================================================
/**
 * @file      ODBC_Parameter.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _ODBC_PARAMETER_H_
#define _ODBC_PARAMETER_H_

#include "ODBC_Base.h"
#include "ODBC_Exception.h"
#include "cuts/utils/db/DB_Parameter.h"

// Forward decl.
class ODBC_Query;

// Forward decl.
class ODBC_Parameter_List;

//=============================================================================
/**
 * @class ODBC_Parameter
 *
 * ODBC implementation of the CUTS_DB_Parameter abstract type.
 */
//=============================================================================

class CUTS_ODBC_Export ODBC_Parameter :
  public CUTS_DB_Parameter,
  public ODBC_Base
{
  // Friend decl.
  friend class ODBC_Parameter_List;

public:
  /// Default constructor
  ODBC_Parameter (void);

  ODBC_Parameter (const ODBC_Parameter & p);

  /// Destructor.
  virtual ~ODBC_Parameter (void);

  virtual void null (void);

  virtual void bind (char * buffer, size_t bufsize);

  virtual void bind (const char * buffer, size_t bufsize);

  virtual void bind (ACE_INT16 & buffer);

  virtual void bind (ACE_UINT16 & buffer);

  virtual void bind (ACE_INT32 & buffer);

  virtual void bind (ACE_UINT32 & buffer);

  virtual void bind (ACE_UINT64 & value);

  virtual void bind (ACE_INT64 & value);

  virtual void bind (float & value);

  virtual void bind (double & value);

  virtual void bind (CUTS_DB_Date_Time & dt);

  const ODBC_Parameter & operator = (const ODBC_Parameter & rhs);

  /**
   * Set the length of the parameter. This is necessary of the
   * parameter is already bound to a buffer, and the length of the
   * input buffer has changed.
   *
   * @param[in]       len         Length of the buffer.
   */
  virtual void length (long len);

  /**
   * Get the current length/size of the parameter.
   *
   * @return          The length/size of the parameter.
   */
  virtual long length (void);

private:
  /// Helper method for binding SQL parameters.
  void bind_i (SQLSMALLINT iotype,
               SQLSMALLINT valuetype,
               SQLSMALLINT paramtype,
               SQLUINTEGER columnsize,
               SQLSMALLINT decimals,
               SQLPOINTER  valueptr,
               SQLINTEGER  buffer_length);

  /// Handle to the ODBC statement.
  const ODBC_Query * query_;

  /// Size of the parameter buffer.
  SQLINTEGER intptr_;

  /// Pointer to allocated memory.
  void * buffer_;
};

#endif  // !defined _ODBC_PARAMETER_H_
