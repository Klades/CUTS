// -*- C++ -*-

//=============================================================================
/**
 * @file        TestRetriever_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_RETRIEVER_I_H_
#define _CUTS_TEST_RETRIEVER_I_H_

#include "../archivingS.h"
#include "cuts/config.h"
#include "ace/UUID.h"
#include "ace/FILE_IO.h"

/**
 * @class CUTS_TestRetriever_i
 *
 * Implementation of the CUTS::TestRetriever interface.
 */
class CUTS_TestRetriever_i : public POA_CUTS::TestRetriever
{
public:
  /**
   * Default constructor.
   *
   * @param[in]       uuid            UUID of the test.
   * @param[in]       chunk_size      Size of each download chunk
   */
  CUTS_TestRetriever_i (const ACE_Utils::UUID & uuid,
                        size_t chunk_size);

  /// Destructor.
  virtual ~CUTS_TestRetriever_i (void);

  /**
   * Open the retriever.
   *
   * @param[in]       path            Directory containing the test.
   */
  int open (const ACE_CString & path);

  /// Close the retriever.
  int close (void);

  /**
   * Download a new chunk of the test.
   *
   * @param[out]        packet        Data packet with test data.
   * @retval            true          More data to download.
   * @retval            false         No more data to download.
   */
  virtual CORBA::Boolean recv_data (CUTS::BinaryData_out packet);

  const ACE_Utils::UUID & uuid (void) const;

private:
  /// UUID of the test begin retrieved.
  ACE_Utils::UUID uuid_;

  /// The size of each chunk.
  const size_t chunk_size_;

  ACE_FILE_Addr file_addr_;

  ACE_FILE_IO file_;
};

#if defined (__CUTS_INLINE__)
#include "TestRetriever_i.inl"
#endif

#endif  // !defined _CUTS_TEST_RETRIEVER_I_H_
