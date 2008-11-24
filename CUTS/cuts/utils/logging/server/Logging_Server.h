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
#include "Logging_Server_Task.h"
#include "Logging_Server_Options.h"
#include "TestLoggerServer_i.h"
#include "tao/PortableServer/PortableServer.h"
#include "ace/UUID.h"
#include "ace/Unbounded_Set.h"
#include <string>

namespace ACE_Utils
{
  class UUID;
}

/**
 * @class CUTS_Test_Logging_Server
 *
 * Defines the main entry point for the test logging server
 * application
 */
class CUTS_TEST_LOGGING_SERVER_Export CUTS_Test_Logging_Server
{
public:
  /// Friend decl.
  friend class CUTS_Test_Logging_Server_Task;

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
   * Set the UUID for the server.
   *
   * @param[in]     uuid          UUID of the server.
   */
  void uuid (const ACE_Utils::UUID & uuid);

private:
  int parse_args (int argc, char * argv[]);

  void print_help (void);

  void register_with_clients (void);

  void register_with_client (const std::string & client,
                             ::CUTS::TestLoggerServer_ptr server);

  void unregister_with_clients (void);

  /// The task for the server.
  CUTS_Test_Logging_Server_Task task_;

  /// Reference to the CORBA ORB.
  CORBA::ORB_var orb_;

  /// Reference to the RootPOA
  PortableServer::POA_var root_poa_;

  /// Reference to the POA manager.
  PortableServer::POAManager_var poa_mgr_;

  /// The actual implemenation of the server.
  CUTS_TestLoggerServer_i server_;

  /// Logging server options.
  CUTS_Logging_Server_Options opts_;

  /// The UUID of the server.
  CUTS::UUID uuid_;

  /// Collection of clients server is registered.
  typedef ACE_Unbounded_Set <CUTS::TestLoggerClient_ptr> clients_set_type;

  clients_set_type clients_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVER_H_
