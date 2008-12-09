// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Archive_Server.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_ARCHIVE_SERVER_H_
#define _CUTS_TEST_ARCHIVE_SERVER_H_

#include "TestArchive_i.h"

/**
 * @class CUTS_Test_Archive_Server
 *
 * The test archive server.
 */
class CUTS_Test_Archive_Server
{
public:
  /// Default constructor.
  CUTS_Test_Archive_Server (void);

  /// Destructor.
  ~CUTS_Test_Archive_Server (void);

  /**
   * Main entry point for the application.
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The command-line arguments
   * @return          Exit status of the server.
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the server application.
  void shutdown (void);

  /// Destroy the server, and its resources.
  void destroy (void);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Print the help for the server.
  void print_help (void);

  int register_with_iortable (const char * name, const char * objstr);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// The RootPOA for the server.
  PortableServer::POA_var root_poa_;

  /// The test archive servant for this server.
  CUTS_TestArchive_i archive_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Archive_Server.inl"
#endif

#endif  // !defined _CUTS_TEST_ARCHIVE_SERVER_H_
