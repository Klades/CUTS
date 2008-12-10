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

#include "Logging_Client_export.h"
#include "Local_Logging_Client_App.h"
#include "TestLoggerClient_i.h"
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

  /// Print the help message to the screen.
  void print_help (void);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// Implementation of the CUTS::TestLoggerClient.
  ACE_Auto_Ptr <CUTS_TestLoggerClient_i> client_;

  ACE_Auto_Ptr <CUTS_Local_Logging_Client_App> local_client_;
};

#endif  // !defined _CUTS_LOGGING_CLIENT_SERVER_H_