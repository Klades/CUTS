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
  /**
   * Initializing constructor
   *
   * @param[in]       sandbox         Location of the variable tables
   */
  CUTS_Unit_Test_Evaluator (const ACE_CString & sandbox);

  /// Destructor
  ~CUTS_Unit_Test_Evaluator (void);

  /**
   * Open the evaluator for the given test database
   *
   * @param[in]       data            Test database.
   */
  bool open (CUTS_Test_Database & data);

  /// Close the active test.
  void close (void);

  /**
   * Evaluate a new unit test. This will delete any existing
   * records of the unit test in the variable database.
   *
   * @param[in]       test            Unit test to evaluate
   * @param[out]      result          Results of the evaluation.
   */
  bool evaluate (const CUTS_Unit_Test & test,
                 CUTS_Unit_Test_Result & result);

  /**
   * Get the results of an existing test.
   *
   * @param[in]       test            Test in question
   * @param[out]      result          Results of the evaluation.
   */
  void get_result (const CUTS_Unit_Test & test,
                   CUTS_Unit_Test_Result & result);

  /**
   * Get the data trend for the specified unit test.
   *
   * @param[in]       test            Test in question
   * @param[out]      result          Pointer to the results
   */
  bool get_data_trend (const CUTS_Unit_Test & test,
                       CUTS_DB_SQLite_Connection * & record);

private:
  int open_vtable (CUTS_Test_Database & test);

  void create_vtable (const CUTS_Unit_Test & test);

  void create_vtable_indices (const CUTS_Unit_Test & test,
                              const CUTS_Log_Format & format);

  void process (CUTS_Log_Format_Data_Entry & entry,
                CUTS_DB_SQLite_Record & record);

  /// Location where evaluator performs calculations.
  ACE_CString sandbox_;

  /// Pointer to the test database.
  CUTS_Test_Database * data_;

  /// Variable table for the active test.
  CUTS_DB_SQLite_Connection * vtable_;
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_EVALUATOR_H_
