// -*- C++ -*-

//=============================================================================
/**
 * @file        TestUploader_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_UPLOADER_I_H_
#define _CUTS_TEST_UPLOADER_I_H_

#include "cuts/config.h"
#include "../archivingS.h"
#include "ace/FILE_Addr.h"
#include "ace/FILE_IO.h"
#include "ace/UUID.h"

/**
 * @class CUTS_TestUploader_i
 *
 * Implementation of the CUTS::TestUploader interface.
 */
class CUTS_TestUploader_i : public POA_CUTS::TestUploader
{
public:
  /// Default constructor.
  CUTS_TestUploader_i (const ACE_Utils::UUID & uuid,
                       const ACE_CString & output_dir);

  /// Destructor.
  virtual ~CUTS_TestUploader_i (void);

  /**
   * Open the file for writing.
   *
   * @param[in]       filename          Name of the file to open.
   */
  int open (const ACE_CString & filename);

  /// Close the uploader object.
  int close (void);

  /**
   * Send data to the upload agent.
   *
   * @param[in]       packet            Data packet to upload.
   */
  virtual void send_data (const CUTS::ResultData & packet);

  /// Get the UUID of the agent/test for this upload.
  const ACE_Utils::UUID & uuid (void) const;

  bool is_open (void) const;

private:
  /// Initialize the uploader.
  int init (void);

  /// UUID of the upload.
  ACE_Utils::UUID uuid_;

  /// Output directory for the test.
  const ACE_CString & output_dir_;

  /// File where data is written.
  ACE_FILE_Addr file_addr_;

  /// File handle for the upload.
  ACE_FILE_IO file_;
};

#if defined (__CUTS_INLINE__)
#include "TestUploader_i.inl"
#endif

#endif  // !defined _CUTS_TEST_UPLOADER_I_H_
