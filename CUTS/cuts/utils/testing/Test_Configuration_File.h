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
#include "Test_export.h"
#include "XSCRT/utils/File_Reader_T.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "ace/SStringfwd.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
// Forward decl.
class ACE_Process_Options;
ACE_END_VERSIONED_NAMESPACE_DECL

// Forward decl.
class CUTS_Property_Map;

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
  CUTS_Test_Configuration_File (const CUTS_Property_Map & props);

  /// Destructor.
  virtual ~CUTS_Test_Configuration_File (void);

  bool load (const ACE_CString & str);

  int get_startup_process (ACE_Process_Options & options);

  int get_shutdown_process (ACE_Process_Options & options);

  CUTS::testFile & config (void);

private:
  /// Helper method to configure the reader.
  void configure (void);

  int load_process_options (const CUTS::processOptions & po,
                            ACE_Process_Options & options);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver < > > resolver_;

  CUTS::testFile config_;

  const CUTS_Property_Map & props_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Configuration_File.inl"
#endif

#endif  // !defined _CUTS_TEST_CONFIGURATION_FILE_H_
