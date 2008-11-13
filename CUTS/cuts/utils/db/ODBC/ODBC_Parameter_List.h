// -*- C++ -*-

//=============================================================================
/**
 * @file      ODBC_Parameter_List.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ODBC_PARAMETER_LIST_H_
#define _CUTS_ODBC_PARAMETER_LIST_H_

#include "ODBC_Parameter.h"
#include "cuts/utils/db/DB_Parameter_List.h"
#include "ace/Array_Base.h"

// Forward decl.
class ODBC_Query;

/**
 * @class ODBC_Parameter_List
 *
 * Container class for ODBC_Parameter objects.
 */
class CUTS_ODBC_Export ODBC_Parameter_List :
  public CUTS_DB_Parameter_List
{
public:
  /**
   * Initializing constructor.
   */
  ODBC_Parameter_List (const ODBC_Query & query);

  /// Destructor.
  virtual ~ODBC_Parameter_List (void);

  /**
   * Get the size of the parameter list.
   *
   * @return    Size of the parmameter list.
   */
  virtual size_t size (void) const;

  /**
   * Get an existing parameter.
   *
   * @param[in]     index       Index of the parameter.
   * @param[out]    param       Pointer to the parameter.
   */
  virtual const ODBC_Parameter & operator [] (size_t index) const;

  virtual ODBC_Parameter & operator [] (size_t index);

  /// Reset the number parameters for the statement.
  void reset (void);

private:
  /// Type definition of the list of parameters.
  typedef ACE_Array_Base <ODBC_Parameter> array_type;

  /// List of parameters
  array_type params_;

  /// The parent of the query.
  const ODBC_Query & query_;

  int return_;
};

#if defined (__CUTS_INLINE__)
#include "ODBC_Parameter_List.inl"
#endif

#endif  // !defined _ODBC_PARAMETER_LIST_H_
