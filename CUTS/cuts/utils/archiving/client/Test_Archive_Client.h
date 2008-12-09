// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Archive_Client.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_CLIENT_H_
#define _CUTS_TEST_ARCHIVE_CLIENT_H_

#include "../archivingC.h"
#include "Test_Archive_Client_Options.h"

namespace ACE_Utils
{
  // Forward decl.
  class UUID;
}

/**
 * @class CUTS_Test_Archive_Client
 *
 * Client-side implementation of the archive framework.
 */
class CUTS_Test_Archive_Client
{
public:
  /// Default constructor.
  CUTS_Test_Archive_Client (void);

  /// Destructor.
  ~CUTS_Test_Archive_Client (void);

  int run_main (int argc, char * argv []);

  /// Shutdown the client.
  void shutdown (void);

  /// Destroy the client's resources.
  void destroy (void);

private:
  /// Parse the command-line options.
  int parse_args (int argc, char * argv []);

  int get_test_uuid (ACE_Utils::UUID & uuid);

  /// Print the help for the application.
  void print_help (void);

  /// Reference to the test archive.
  CUTS::TestArchive_var archive_;

  /// Agent used to upload the test data.
  CUTS::TestUploader_var upload_;

  /// The ORB for the test client.
  CORBA::ORB_var orb_;

  /// Options for the client.
  CUTS_Test_Archive_Client_Options opts_;

  /// The busy state of the client.
  bool is_busy_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Archive_Client.inl"
#endif

#endif  // !defined _CUTS_TEST_ARCHIVE_CLIENT_H_
