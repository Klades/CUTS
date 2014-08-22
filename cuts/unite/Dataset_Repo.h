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
#include "Dataflow_Graph.h"
#include "Relation.h"
#include <vector>

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

// Forward decl.
class CUTS_Graph_Worker;

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

  typedef std::vector <CUTS_Dataflow_Graph::vertex_descriptor> vertex_list;

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

  bool open (const ACE_CString & sandbox, CUTS_Test_Database & data, int graph_worker_id);

  /**
   * Build a variable table for the active/open test. The variable
   * table is (re)constructed using the graph of the unit test,
   * which is represented by the relations between log formats.
   *
   * @param[in]       graph           Graph of the unit test.
   * @param[in]       sorted_list     topologically sorted vertices.
   */
  bool insert (CUTS_Dataflow_Graph * graph,
               vertex_list & sorted_list);

  /// Creates a SQLite Query
  ADBC::SQLite::Query * create_query (void);

  /// Checks whether the relation is in the graph
  bool qualified_relation (const CUTS_Log_Format_Relation & relation,
                           CUTS_Dataflow_Graph & graph);

   /// graph_worker
  void graph_worker (CUTS_Graph_Worker * worker);

  /// Get the name of the sub vtable
  const ACE_CString & table_name (void) const;

  /// Get the name of the sub repo
  const ACE_CString & repo_name (void) const;

  /// Attach a sub repo to this repo
  void attach_database (const char * file_name,
                        const char * sqlite_db_name);

  /// Join set of data repos
  void join (std::vector <CUTS_Graph_Worker *> & workers,
             CUTS_Dataflow_Graph & graph);

  /// Test function to check whether the join is scuuceeded
  void test_repo (void);

private:

  /// Open the vtable associates with the CUTS_Test_Database
  int open_vtable (CUTS_Test_Database & test);

  /// Creates a vtable for a Dataflow graph of log formats
  void create_vtable (CUTS_Dataflow_Graph & graph,
                      vertex_list & sorted_list);

  /// Create an index for the vtable
  void create_vtable_indices (CUTS_Dataflow_Graph & test,
                              vertex_list & sorted_list);

  /// Create an index based on a particular log formaty
  void create_vtable_indices (CUTS_Dataflow_Graph & test,
                              const CUTS_Log_Format & format);

  /// Delete all the rows in whic some of there columns doesn't have a value
  void prune_incomplete_rows (CUTS_Dataflow_Graph & graph,
                              vertex_list & sorted_list);

  /// Pointer to the test database.
  CUTS_Test_Database * data_;

  /// Variable table for the active test.
  ADBC::SQLite::Connection * vtable_;

  /// Copy constructor
  CUTS_Dataset_Repo (const CUTS_Dataset_Repo &);

  /// Overloaded = operator
  const CUTS_Dataset_Repo & operator = (const CUTS_Dataset_Repo &);

  /// Associated worker
  CUTS_Graph_Worker * graph_worker_;

  /// Get the table name
  ACE_CString table_name_;

  /// Get the repo name
  ACE_CString repo_name_;

};

#if defined (__CUTS_INLINE__)
#include "Dataset_Repo.inl"
#endif

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_REPO_H_