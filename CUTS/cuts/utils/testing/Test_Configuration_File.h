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
#include "Command_Options_List.h"

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

  /// Load the configuration file using the file name
  bool load (const ACE_CString & str);

  /// Sets the configurations related to rhe startup process
  int get_startup_process (ACE_Process_Options & options);

  /// Sets  the configuration related to the shutdown process
  int get_shutdown_process (ACE_Process_Options & options);

  /// Sets the configuration related to test commands
  int get_testops (CUTS_Command_Options_List & testops);

  /// Gets the configuration
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
