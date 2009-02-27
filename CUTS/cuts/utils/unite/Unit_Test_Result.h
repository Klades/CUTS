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

#ifndef _CUTS_UNITE_UNIT_TEST_RESULT_H_
#define _CUTS_UNITE_UNIT_TEST_RESULT_H_

#include "Unite_export.h"
#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

/// Type definition of a group result.
typedef ACE_Hash_Map_Manager <ACE_CString,
                              ACE_CString,
                              ACE_Null_Mutex> CUTS_Unit_Test_Group_Result;
/**
 * @class CUTS_Unit_Test_Result
 *
 * Collection of the results for a unit test. Right now, the results
 * are returned in string format. It would be ideal, however to return
 * the results in their native format. Unfortunately, the need for this
 * behavior has not proved to be a necessity at the moment.
 */
class CUTS_UNITE_Export CUTS_Unit_Test_Result
{
public:

  /// Default constructor.
  CUTS_Unit_Test_Result (void);

  /// Destructor.
  ~CUTS_Unit_Test_Result (void);

  void result (const ACE_CString & result);

  const ACE_CString & result (void) const;

  CUTS_Unit_Test_Group_Result & groups (void);

  const CUTS_Unit_Test_Group_Result & groups (void) const;

private:
  ACE_CString result_;

  CUTS_Unit_Test_Group_Result group_;

  CUTS_Unit_Test_Result (const CUTS_Unit_Test_Result &);
  const CUTS_Unit_Test_Result & operator = (const CUTS_Unit_Test_Result &);
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_RESULT_H_
