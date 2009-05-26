// $Id$

//=============================================================================
/**
 * @file          Logging_Server.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_LOGGING_SERVER_H_
#define _CUTS_TEST_LOGGING_SERVER_H_

#include "Logging_Server_export.h"
#include "Logging_Server_Options.h"
#include "TestLoggerServer_i.h"
#include "cuts/ORB_Server_Task.h"
#include "cuts/utils/testing/Test_Database.h"
#include "tao/PortableServer/PortableServer.h"
#include "ace/UUID.h"
#include "ace/Unbounded_Set.h"
#include <string>

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
namespace ACE_Utils
{
  class UUID;
}
ACE_END_VERSIONED_NAMESPACE_DECL

/**
 * @class CUTS_Test_Logging_Server
 *
 * Defines the main entry point for the test logging server
 * application
 */
class CUTS_TEST_LOGGING_SERVER_Export CUTS_Test_Logging_Server
{
public:
  /// Constructor
  CUTS_Test_Logging_Server (void);

  /**
   * Initializing constructor
   *
   * @param[in]         orb         Target ORB for server.
   */
  CUTS_Test_Logging_Server (CORBA::ORB_ptr orb);

  /// Destructor
  virtual ~CUTS_Test_Logging_Server (void);

  /**
   * Run the logging server.
   *
   * @param[in]     argc          Number of command-line arguments
   * @param[in]     argv          Command-line arguments
   */
  int run_main (int argc, char * argv[]);

  int spawn_main (int argc, char * argv []);

  /// Shutdown the application.
  void shutdown (void);

  /**
   * Install a callback into the logging server.
   *
   * @param[in]     callback      Pointer to callback to install.
   */
  int install_callback (CUTS::TestLoggerServerCallback_ptr callback);

  /**
   * Set the archive for logging data.
   *
   * @param[in]     archive          Location of the archive.
   */
  void archive (CUTS_Test_Database * archive);

private:
  int parse_args (int argc, char * argv[]);

  int init_test_database (void);

  void print_help (void);

  void register_with_clients (void);

  void register_with_client (const std::string & client,
                             CUTS::TestLoggerServer_ptr server);

  void unregister_with_clients (void);

  /// The task for the server.
  CUTS_ORB_Server_Task task_;

  /// Reference to the CORBA ORB.
  CORBA::ORB_var orb_;

  /// Reference to the RootPOA
  PortableServer::POA_var root_poa_;

  /// The actual implemenation of the server.
  CUTS_TestLoggerServer_i server_;

  /// Logging server options.
  CUTS_Logging_Server_Options opts_;

  /// Archive for logging data.
  ACE_CString archive_file_;

  /// UUID from the archive.
  CUTS::UUID uuid_;

  /// Collection of clients server is registered.
  typedef ACE_Unbounded_Set <CUTS::TestLoggerClient_var> clients_set_type;

  clients_set_type clients_;

  /// Ownership flag for the archive.
  bool is_owner_;

  /// Temporary CUTS database
  CUTS_Test_Database * archive_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVER_H_
