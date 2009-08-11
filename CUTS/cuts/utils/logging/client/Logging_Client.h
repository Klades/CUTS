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
#include "Logging_Client_Options.h"
#include "LoggingClient_i.h"
#include "Logger_Task.h"
#include "cuts/Servant_Manager_T.h"
#include "cuts/Servant_Traits_T.h"
#include "cuts/IOR_File_Trait.h"
#include "cuts/IOR_Table_Trait.h"

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

  void destroy (void);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Print the help message to the screen.
  void print_help (void);

  /// The ORB for the server.
  ::CORBA::ORB_var orb_;

  typedef
    CUTS_Servant_Trait_T <CUTS_IOR_File_Trait,
    CUTS_Servant_Trait_T <CUTS_IOR_Table_Trait> > traits_type;

  /// Implementation of the CUTS::TestLoggerClient.
  CUTS_Servant_Manager_Ex_T <CUTS_LoggingClient_i, traits_type> client_;

  /// The clean task for the logger.
  CUTS_Logger_Task cleaning_task_;

  CUTS_Logging_Client_Options opts_;
};

#endif  // !defined _CUTS_LOGGING_CLIENT_SERVER_H_
