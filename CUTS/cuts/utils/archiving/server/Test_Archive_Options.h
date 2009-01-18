// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Archive_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_OPTIONS_H_
#define _CUTS_TEST_ARCHIVE_OPTIONS_H_

/**
 * @class CUTS_Test_Archive_Options
 *
 * Options for the test archive application.
 */
class CUTS_Test_Archive_Options
{
public:
  CUTS_Test_Archive_Options (void)
    : hostname_ (CUTS_DEFAULT_HOSTNAME),
      username_ (CUTS_USERNAME),
      password_ (CUTS_PASSWORD)
  {

  }

  /// The location of the archive file.
  ACE_CString archive_file_;

  /// Target directory for the uploads.
  ACE_CString upload_dir_;

  /// Location of the test database.
  ACE_CString hostname_;

  /// Username to use for connection.
  ACE_CString username_;

  /// Password for authentication.
  ACE_CString password_;
};

#endif  // !defined _CUTS_TEST_ARCHIVE_OPTIONS_H_
