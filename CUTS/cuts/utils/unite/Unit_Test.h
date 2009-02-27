// -*- C++ -*-

//=============================================================================
/**
 * @file        Unit_Test.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_UNIT_TEST_H_
#define _CUTS_UNITE_UNIT_TEST_H_

#include "Unite_export.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "ace/Vector_T.h"

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Unit_Test_Graph;

/**
 * @class CUTS_Log_Format_Manager
 */
class CUTS_UNITE_Export CUTS_Unit_Test
{
public:
  /// Type definition of the map type.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                CUTS_Log_Format *,
                                ACE_Null_Mutex> formats_type;

  /// Type definition for the grouping.
  typedef ACE_Vector <ACE_SString> grouping_type;

  /// Default constructor
  CUTS_Unit_Test (void);

  /**
   * Initializing constructor
   *
   * @param[in]       name        Name of the unit test.
   */
  CUTS_Unit_Test (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Unit_Test (void);

  /**
   * Set the name of the unit test.
   *
   * @param[in]       n           New name for the unit test.
   */
  void name (const ACE_CString & n);

  /**
   * Get the name of the unit test.
   */
  const ACE_CString & name (void) const;

  /**
   * Set the name of the unit test.
   *
   * @param[in]       n           New name for the unit test.
   */
  void evaluation (const ACE_CString & n);

  /**
   * Get the name of the unit test.
   */
  const ACE_CString & evaluation (void) const;

  /**
   * Set the name of the unit test.
   *
   * @param[in]       n           New name for the unit test.
   */
  void aggregation (const ACE_CString & aggr);

  /**
   * Get the name of the unit test.
   */
  const ACE_CString & aggregation (void) const;

  /**
   * Get the name of the unit test.
   */
  const grouping_type & groupings (void) const;

  /**
   * @overload
   */
  grouping_type & groupings (void);

  /**
   * Create a new log format.
   *
   * @param[in]         name      Name of the log format.
   */
  bool create_log_format (const ACE_CString & name);

  /**
   * Create a new log format.
   *
   * @param[in]         name      Name of the log format.
   */
  bool create_log_format (const ACE_CString & name, CUTS_Log_Format *& format);

  /**
   * Associate the causality of two log formats.
   *
   * @param[in]         cause         The source log format (cause).
   * @param[in]         effect        The target log format (effect).
   */
  bool associate (const ACE_CString & cause, const ACE_CString & effect);

  /**
   * Get the underlying causality graph for the unit test.
   *
   * @return            Pointer to the graph.
   */
  const CUTS_Unit_Test_Graph * graph (void) const;

  /**
   * Get the collection of log formats for the unit test.
   */
  const formats_type & log_formats (void) const;

private:
  /// Name of the unit test.
  ACE_CString name_;

  /// The evaluation for the unit test.
  ACE_CString evaluation_;

  /// The aggregation function for the test.
  ACE_CString aggr_;

  /// The log formats for the unit test.
  formats_type formats_;

  /// The grouping for the unit test.
  grouping_type grouping_;

  /// Graph of the unit test.
  CUTS_Unit_Test_Graph * graph_;

  // prevent the following operations
  CUTS_Unit_Test (const CUTS_Unit_Test &);
  const CUTS_Unit_Test & operator = (const CUTS_Unit_Test &);
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_H_
