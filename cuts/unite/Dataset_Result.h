// -*- C++ -*-

//=============================================================================
/**
 * @file        Unit_Test_Result.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_DATASET_RESULT_H_
#define _CUTS_UNITE_DATASET_RESULT_H_

#include "Aspect.h"
#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/Array_Base.h"

namespace ADBC
{
namespace SQLite
{
// Forward decl.
class Query;

// Forward decl.
class Record;
}
}

// Forward decl.
class CUTS_Dataset_Repo;

// Forward decl.
class CUTS_Unite_Test;

/// Type definition for the collection of group names.
typedef ACE_Array_Base <ACE_CString> CUTS_Group_Name;

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Dataset_Result
 *
 * Collection of the results for a unit test. Right now, the results
 * are returned in string format. It would be ideal, however to return
 * the results in their native format. Unfortunately, the need for this
 * behavior has not proved to be a necessity at the moment.
 */
class CUTS_UNITE_Export CUTS_Dataset_Result
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]         eval          Evaluator of the unit test
   * @param[in]         graph         Name of the graph to evaluate
   */
  CUTS_Dataset_Result (CUTS_Dataset_Repo & repo,
                       size_t bufsize = CUTS_RESULT_DEFAULT_BUFFER_SIZE);

  /// Destructor.
  ~CUTS_Dataset_Result (void);

  /**
   * Evaluate a tests.
   *
   * @param[in]         test          Unit test to evaluate
   * @param[in]         datagraph     Name of the graph to apply result
   * @param[in]         aspect        Aspect of data to evaluate
   * @param[in]         aggr          Aggregate the results
   */
  int evaluate (const CUTS_Unite_Test & test,
                const ACE_CString & datagraph,
                CUTS_UNITE_Aspect * aspect = 0,
                bool aggr = true);

  /// Close the result.
  void close (void);

  /// Determine if the result is done.
  bool done (void) const;

  /// Advance to the next result in the record.
  void advance (void);

  /**
   * Get the current result.
   */
  const char * get_result (void);

  const CUTS_Group_Name & get_group_name (void);

  /// Determine if the result has groupings.
  bool has_groupings (void) const;

  /**
   * Get the unit test associated with the result
   *
   * @return        Unit test for the result.
   */
  const CUTS_Unite_Test * unit_test (void) const;

  /**
   * Get the name of the variable table used for evaluating the
   * unit test.
   *
   * @return        Name of the variable table.
   */
  const ACE_CString * vtable_name (void) const;

  /// Move to the first row in the result.
  void rewind (void);

private:
  /// The target variable repo for the result.
  CUTS_Dataset_Repo * repo_;

  /// The query that created the result.
  ADBC::SQLite::Query * query_;

  /// The record holding the results.
  ADBC::SQLite::Record * record_;

  /// The index of the result.
  size_t result_index_;

  /// The buffer holding the result.
  ACE_Auto_Array_Ptr <char> result_;

  /// The size of the result buffer.
  size_t bufsize_;

  /// Name of the variable table used for evaluation.
  const ACE_CString * vtable_name_;

  /// The unit test used in the evaluation.
  const CUTS_Unite_Test * unit_test_;

  /// Group name associated with the current result.
  CUTS_Group_Name group_name_;

  /// The result is old, i.e., needs updating.
  bool result_is_old_;

  /// The result is old, i.e., needs updating.
  bool group_is_old_;

  // prevent the following operations
  CUTS_Dataset_Result (const CUTS_Dataset_Result &);
  const CUTS_Dataset_Result & operator = (const CUTS_Dataset_Result &);
};

#if defined (__CUTS_INLINE__)
#include "Dataset_Result.inl"
#endif

#endif  // !defined _CUTS_UNITE_DATASET_RESULT_H_