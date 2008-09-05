// $Id$

//=============================================================================
/**
 * @file        Node_Daemon_Server.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODE_DAEMON_SERVER_H_
#define _CUTS_NODE_DAEMON_SERVER_H_

#include "Server_Options.h"
#include "Node_Daemon_i.h"

/**
 * @class CUTS_Node_Daemon_Server
 */
class CUTS_Node_Daemon_Server
{
public:
  /// Default constructor.
  CUTS_Node_Daemon_Server (void);

  /// Destructor.
  ~CUTS_Node_Daemon_Server (void);

  /**
   * Run the server main event loop.
   *
   * @param[in]         argc          Number of arguments
   * @param[in]         argv          Command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the server.
  void shutdown (void);

private:
  int parse_args (int argc, char * argv []);

  int write_ior_to_file (void);

  int write_ior_to_table (void);

  int load_initial_config (void);

  /// ORB for the server.
  CORBA::ORB_var orb_;

  /// Options for the server.
  CUTS_Node_Daemon_Server_Options opts_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;

  /// Implemenation of the CUTS::TestLoggerClient.
  CUTS_Node_Daemon_i * daemon_;
};

#endif  // !defined _CUTS_NODE_DAEMON_SERVER_H_
