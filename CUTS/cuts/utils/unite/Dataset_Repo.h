// -*- C++ -*-

//=============================================================================
/**
 * @file        Dataset_Repo.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_DATASET_REPO_H_
#define _CUTS_UNITE_DATASET_REPO_H_

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
class CUTS_Dataflow_Graph;

/**
 * @class CUTS_Dataset_Repo
 */
class CUTS_UNITE_Export CUTS_Dataset_Repo
{
public:
  // Friend decl.
  friend class CUTS_Unit_Test_Result;

  /// Default constructor.
  CUTS_Dataset_Repo (void);

  /// Destructor
  ~CUTS_Dataset_Repo (void);

  /**
   * Open the repo for the given test database. If you want to perform
   * in-memory processing, i.e., do not create a dataset file for later
   * usage, then use :memory: for the \a location.
   *
   * @param[in]       location        Directory for writing datasets
   * @param[in]       data            Test database.
   */
  bool open (const ACE_CString & location, CUTS_Test_Database & data);

  /// Close the variable table repo.
  void close (void);

  /**
   * Build a variable table for the active/open test. The variable
   * table is (re)constructed using the graph of the unit test,
   * which is represented by the relations between log formats.
   *
   * @param[in]       graph           Graph of the unit test.
   */
  bool insert (const CUTS_Dataflow_Graph & graph);

private:
  int open_vtable (CUTS_Test_Database & test);

  void create_vtable (const CUTS_Dataflow_Graph & graph);

  void create_vtable_indices (const CUTS_Dataflow_Graph & test);

  void create_vtable_indices (const CUTS_Dataflow_Graph & test,
                              const CUTS_Log_Format & format);

  void prune_incomplete_rows (const CUTS_Dataflow_Graph & graph);

  /// Pointer to the test database.
  CUTS_Test_Database * data_;

  /// Variable table for the active test.
  CUTS_DB_SQLite_Connection * vtable_;

  CUTS_Dataset_Repo (const CUTS_Dataset_Repo &);
  const CUTS_Dataset_Repo & operator = (const CUTS_Dataset_Repo &);
};

#if defined (__CUTS_INLINE__)
#include "Dataset_Repo.inl"
#endif

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_REPO_H_
