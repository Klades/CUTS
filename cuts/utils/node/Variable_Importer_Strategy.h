// -*- C++ -*-

//=============================================================================
/**
 * @file        Variable_Importer_Strategy.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_VARIABLE_IMPORTER_STRATEGY_H_
#define _CUTS_VARIABLE_IMPORTER_STRATEGY_H_

#include "ace/SStringfwd.h"
#include "cuts/config.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Variable_Importer_Strategy
 *
 * Strategy/base class for all variable importer implementations.
 */
class CUTS_Variable_Importer_Strategy
{
public:
  /// Default constructor.
  CUTS_Variable_Importer_Strategy (void);

  /// Destructor.
  virtual ~CUTS_Variable_Importer_Strategy (void);

  /**
   * Import variables at the specified location. Each implmentation
   * is required to implement this method. The imported variables
   * will be stored in /a vars.
   *
   * @param[in]       location          Location of variable file
   * @param[out]      vars              Imported variables
   * @retval          0                 Import succeeded
   * @retval          -1                Import failed
   */
  virtual int handle_import (const ACE_CString & location,
                             CUTS_Property_Map & vars) = 0;
};

#if defined (__CUTS_INLINE__)
#include "Variable_Importer_Strategy.inl"
#endif

#endif  // !defined _CUTS_VARIABLE_IMPORTER_STRATEGY_H_
