// -*- C++ -*-

//=============================================================================
/**
 * @file        DB_Parameter_List.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_PARAMETER_LIST_H_
#define _CUTS_DB_PARAMETER_LIST_H_

#include "DB_Utils_Export.h"

// Forward decl.
class CUTS_DB_Parameter;

/**
 * @class CUTS_DB_Parameter_List
 */
class CUTS_DB_UTILS_Export CUTS_DB_Parameter_List
{
public:
  /// Default constructor.
  CUTS_DB_Parameter_List (void);

  /// Destructor
  virtual ~CUTS_DB_Parameter_List (void);

  virtual const CUTS_DB_Parameter & operator [] (size_t index) const = 0;

  virtual CUTS_DB_Parameter & operator [] (size_t index) = 0;

  /**
   * Get the size of the parameter list.
   */
  virtual size_t size (void) const = 0;
};

#if defined (__CUTS_INLINE__)
#include "DB_Parameter_List.inl"
#endif

#endif  // !defined _CUTS_DB_PARAMETER_LIST_H_
