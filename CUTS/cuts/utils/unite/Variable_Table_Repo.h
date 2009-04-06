// -*- C++ -*-

//=============================================================================
/**
 * @file        Variable_Table_Repo.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_VARIABLE_TABLE_REPO_H_
#define _CUTS_UNITE_VARIABLE_TABLE_REPO_H_

#include "Unit_Test_Result.h"
#include "ace/SString.h"

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

// Forward decl.
class CUTS_Unit_Test_Graph;

/**
 * @class CUTS_Variable_Table_Repo
 */
class CUTS_UNITE_Export CUTS_Variable_Table_Repo
{
public:
  // Friend decl.
  friend class CUTS_Unit_Test_Result;

  /**
   * Initializing constructor
   *
   * @param[in]       sandbox         Location of the variable table(s)
   */
  CUTS_Variable_Table_Repo (const ACE_CString & sandbox);

  /// Destructor
  ~CUTS_Variable_Table_Repo (void);

  /**
   * Open the repo for the given test database
   *
   * @param[in]       data            Test database.
   */
  bool open (CUTS_Test_Database & data);

  /// Close the active test.
  void close (void);

  /**
   * Build a variable table for the active/open test. The variable
   * table is (re)constructed using the graph of the unit test,
   * which is represented by the relations between log formats.
   *
   * @param[in]       graph           Graph of the unit test.
   */
  bool insert (const CUTS_Unit_Test_Graph & graph);

private:
  int open_vtable (CUTS_Test_Database & test);

  void create_vtable (const CUTS_Unit_Test_Graph & graph);

  void create_vtable_indices (const CUTS_Unit_Test_Graph & test);

  void create_vtable_indices (const CUTS_Unit_Test_Graph & test,
                              const CUTS_Log_Format & format);

  void prune_incomplete_rows (const CUTS_Unit_Test_Graph & graph);

  void process (CUTS_Log_Format_Data_Entry & entry,
                CUTS_DB_SQLite_Record & record);

  /// Location where evaluator performs calculations.
  ACE_CString sandbox_;

  /// Pointer to the test database.
  CUTS_Test_Database * data_;

  /// Variable table for the active test.
  CUTS_DB_SQLite_Connection * vtable_;
};

#if defined (__CUTS_INLINE__)
#include "Variable_Table_Repo.inl"
#endif

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_REPO_H_
