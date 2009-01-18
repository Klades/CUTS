// -*- C++ -*-

//=============================================================================
/**
 * @file        TestArchive_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_I_H_
#define _CUTS_TEST_ARCHIVE_I_H_

#include "../archivingS.h"
#include "Test_Archive_Options.h"
#include "cuts/utils/db/ODBC/ODBC_Connection.h"
#include "tao/PortableServer/POAC.h"
#include "ace/Unbounded_Set.h"
#include "ace/UUID.h"

/**
 * @class CUTS_TestArchive_i
 *
 * Implementation of the CUTS::TestArchive interface.
 */
class CUTS_TestArchive_i : public POA_CUTS::TestArchive
{
public:
  /// Default constructor.
  CUTS_TestArchive_i ();

  /// Destructor.
  virtual ~CUTS_TestArchive_i (void);

  /**
   * Initialize the archive within the specified POA.
   *
   * @param[in]       parent          Parent POA.
   */
  int init (PortableServer::POA_ptr parent);

  /**
   * Begin uploading a test to the archive.
   *
   * @param[in]         info        Information about the test results
   * @return            Agent for uplaoding the results.
   */
  virtual CUTS::TestUploader_ptr begin_upload (const CUTS::TestResult & info);

  /**
   * The upload of the data is complete.
   *
   * @param[in]         uploader    Agent uploading the data.
   */
  virtual void upload_complete (CUTS::TestUploader_ptr uploader);

  /// Access the test archive options.
  CUTS_Test_Archive_Options & opts (void);

private:
  /// Type definition for the collection of uploads.
  typedef ACE_Unbounded_Set <ACE_Utils::UUID> collection_type;

  /// Current uploads to the archive.
  collection_type uploads_;

  /// POA for activating objects.
  PortableServer::POA_var upload_poa_;

  /// Upload directory for the archive.
  CUTS_Test_Archive_Options opts_;

  /// Connection to the indexing database.
  ODBC_Connection conn_;
};

#if defined (__CUTS_INLINE__)
#include "TestArchive_i.inl"
#endif

#endif  // !defined _CUTS_TEST_ARCHIVE_I_H_
