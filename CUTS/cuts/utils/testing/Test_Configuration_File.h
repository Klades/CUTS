// -*- C++ -*-

//=============================================================================
/**
 * @file          Test_Configuration_File.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_CONFIGURATION_FILE_H_
#define _CUTS_TEST_CONFIGURATION_FILE_H_

#include "test.h"
#include "cuts/config.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @class CUTS_Test_Configuration_File
 *
 * Helper class that simplifies loading test configuration XML
 * documents.
 */
class CUTS_Test_Configuration_File :
  public XSCRT::utils::File_Reader_T <CUTS::testFile>
{
public:
  /// Type definition of the reader type.
  typedef XSCRT::utils::File_Reader_T <CUTS::testFile> reader_type;

  /// Default constructor.
  CUTS_Test_Configuration_File (void);

  /// Destructor.
  virtual ~CUTS_Test_Configuration_File (void);

private:
  /// Helper method to configure the reader.
  void configure (void);
};

#if defined (__CUTS_INLINE__)
#include "Test_Configuration_File.inl"
#endif

#endif  // !defined _CUTS_TEST_CONFIGURATION_FILE_H_
