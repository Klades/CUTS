// -*- C++ -*-

//=============================================================================
/**
 * @file        Unit_Test_Evaluator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_UNIT_TEST_EVALUATOR_H_
#define _CUTS_UNITE_UNIT_TEST_EVALUATOR_H_

#include "Unite_export.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_Unit_Test;

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_DB_SQLite_Connection;

// Forward decl.
class CUTS_DB_SQLite_Record;

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Log_Format_Data_Entry;

// Forward decl.
class CUTS_Unit_Test_Result;

/**
 * @class CUTS_Unit_Test_Evaluator
 */
class CUTS_UNITE_Export CUTS_Unit_Test_Evaluator
{
public:
  /// Default constructor
  CUTS_Unit_Test_Evaluator (const ACE_CString & sandbox);

  /// Destructor
  ~CUTS_Unit_Test_Evaluator (void);

  bool evaluate (CUTS_Test_Database & data,
                 const CUTS_Unit_Test & test,
                 CUTS_Unit_Test_Result & result);

private:
  void create_vtable (CUTS_DB_SQLite_Connection & conn,
                      const CUTS_Unit_Test & test);

  void create_vtable_indices (CUTS_DB_SQLite_Connection & conn,
                              const CUTS_Log_Format & format);

  void process (CUTS_Log_Format_Data_Entry & entry,
                CUTS_DB_SQLite_Record & record);

  void get_result (CUTS_DB_SQLite_Connection & conn,
                   const CUTS_Unit_Test & test,
                   CUTS_Unit_Test_Result & result);

  /// Location where evaluator performs calculations.
  ACE_CString sandbox_;
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_EVALUATOR_H_
