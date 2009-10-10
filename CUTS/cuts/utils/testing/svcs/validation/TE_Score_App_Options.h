// -*- C++ -*-

//=============================================================================
/**
 * @file        TE_Score.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TE_SCORE_APP_OPTIONS_H_
#define _CUTS_TE_SCORE_APP_OPTIONS_H_

#include "ace/SString.h"

/**
 * @class CUTS_TE_Score_App_Options
 */
class CUTS_TE_Score_App_Options
{
public:
  CUTS_TE_Score_App_Options (void)
    : sandbox_ (":memory:")
  {

  }

  /// Location of the test database.
  ACE_CString test_db_file_;

  /// Location of the XML configuration file.
  ACE_CString config_file_;

  /// Location of the sandbox
  ACE_CString sandbox_;
};

#endif  // !defined _CUTS_TE_SCORE_APP_OPTIONS_H_
