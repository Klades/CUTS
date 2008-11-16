// $Id$

//=============================================================================
/**
 * @file          Logging_Client.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOGGING_CLIENT_SERVER_H_
#define _CUTS_LOGGING_CLIENT_SERVER_H_

#include "tao/PortableServer/Servant_Base.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_TestLoggerClient_i;

/**
 * @class CUTS_Logging_Client
 *
 * The server class that will daemonize the client application.
 */
class CUTS_Logging_Client
{
public:
  /// Constructor.
  CUTS_Logging_Client (void);

  /// Destructor.
  ~CUTS_Logging_Client (void);

  /**
   * Run the server.
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the server.
  void shutdown (void);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Register the logger with the IOR table.
  int register_with_iortable (void);

  /// Connect to the logging server.
  int connect_to_server (void);

  /// Print the help message to the screen.
  void print_help (void);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;

  /// Implemenation of the CUTS::TestLoggerClient.
  CUTS_TestLoggerClient_i * client_;
};

#endif  // !defined _CUTS_LOGGING_CLIENT_SERVER_H_
