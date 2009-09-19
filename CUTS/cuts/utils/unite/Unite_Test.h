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
#include "ace/SString.h"
#include "ace/Vector_T.h"

// Forward decl.
class CUTS_Log_Format;

/**
 * @class CUTS_Log_Format_Manager
 */
class CUTS_UNITE_Export CUTS_Unite_Test
{
public:
  /// Type definition for the grouping.
  typedef ACE_Vector <ACE_SString> grouping_type;

  /// Default constructor
  CUTS_Unite_Test (void);

  /**
   * Initializing constructor
   *
   * @param[in]       name        Name of the unit test.
   */
  CUTS_Unite_Test (const ACE_CString & name);

  /// Destructor.
  ~CUTS_Unite_Test (void);

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

private:
  /// Name of the unit test.
  ACE_CString name_;

  /// The evaluation for the unit test.
  ACE_CString evaluation_;

  /// The aggregation function for the test.
  ACE_CString aggr_;

  /// The grouping for the unit test.
  grouping_type grouping_;

  // prevent the following operations
  CUTS_Unite_Test (const CUTS_Unite_Test &);
  const CUTS_Unite_Test & operator = (const CUTS_Unite_Test &);
};

#if defined (__CUTS_INLINE__)
#include "Unite_Test.inl"
#endif

#endif  // !defined _CUTS_UNITE_UNIT_TEST_H_
