// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Archive_Client_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_OPTIONS_H_
#define _CUTS_TEST_ARCHIVE_OPTIONS_H_

#include "ace/SString.h"

/**
 * @class CUTS_Test_Archive_Client_Options
 *
 * Options for the test archive client.
 */
struct CUTS_Test_Archive_Client_Options
{
  /// Input file to upload to the client.
  ACE_CString input_file_;
};

#endif  // !defined _CUTS_TEST_ARCHIVE_OPTIONS_H_
