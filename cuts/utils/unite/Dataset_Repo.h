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

#include "Dataset_Result.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_Test_Database;

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Log_Format_Data_Entry;

// Forward decl.
class CUTS_Dataset_Result;

// Forward decl.
class CUTS_Dataflow_Graph;

namespace ADBC
{
namespace SQLite
{
// Forward decl.
class Connection;

// Forward decl.
class Record;
}
}

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Dataset_Repo
 */
class CUTS_UNITE_Export CUTS_Dataset_Repo
{
public:
  // Friend decl.
  friend class CUTS_Dataset_Result;

  /// Default constructor.
  CUTS_Dataset_Repo (void);

  /// Destructor
  ~CUTS_Dataset_Repo (void);

  /**
   * Open the repo for the given test database. If you want to perform
   * in-memory processing, i.e., do not create a dataset file for later
   * usage, then use ":memory:" for the \a sandbox.
   *
   * @param[in]       sandbox         Directory for writing datasets
   * @param[in]       data            Test database.
   */
  bool open (const ACE_CString & sandbox, CUTS_Test_Database & data);

  /// Close the variable table repo.
  void close (void);

  /**
   * Build a variable table for the active/open test. The variable
   * table is (re)constructed using the graph of the unit test,
   * which is represented by the relations between log formats.
   *
   * @param[in]       graph           Graph of the unit test.
   */
  bool insert (CUTS_Dataflow_Graph & graph);

  /// Creates a SQLite Query
  ADBC::SQLite::Query * create_query (void);

private:

  /// Open the vtable associates with the CUTS_Test_Database
  int open_vtable (CUTS_Test_Database & test);

  /// Creates a vtable for a Dataflow graph of log formats
  void create_vtable (CUTS_Dataflow_Graph & graph);

  /// Create an index for the vtable
  void create_vtable_indices (CUTS_Dataflow_Graph & test);

  /// Create an index based on a particular log formaty
  void create_vtable_indices (CUTS_Dataflow_Graph & test,
                              const CUTS_Log_Format & format);

  /// Delete all the rows in whic some of there columns doesn't have a value
  void prune_incomplete_rows (CUTS_Dataflow_Graph & graph);

  /// Pointer to the test database.
  CUTS_Test_Database * data_;

  /// Variable table for the active test.
  ADBC::SQLite::Connection * vtable_;

  /// Copy constructor
  CUTS_Dataset_Repo (const CUTS_Dataset_Repo &);

  /// Overloaded = operator
  const CUTS_Dataset_Repo & operator = (const CUTS_Dataset_Repo &);
};

#if defined (__CUTS_INLINE__)
#include "Dataset_Repo.inl"
#endif

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_REPO_H_