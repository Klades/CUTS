// -*- C++ -*-

//=============================================================================
/**
 * @file        TestArchive_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_OPTIONS_H_
#define _CUTS_TEST_ARCHIVE_OPTIONS_H_

/**
 * @class CUTS_TestArchive_Options
 *
 * Options for the test archive application.
 */
class CUTS_TestArchive_Options
{
public:
  /// The location of the archive file.
  ACE_CString archive_file_;

  /// Target directory for the uploads.
  ACE_CString upload_dir_;
};

#endif  // !defined _CUTS_TEST_ARCHIVE_OPTIONS_H_
