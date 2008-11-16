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
#include "TestLoggerServer_i.h"
#include "tao/PortableServer/PortableServer.h"

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

private:
  int parse_args (int argc, char * argv[]);

  int register_with_iortable (const char * name,
                              const char * objstr);

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
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVER_H_
