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

#ifndef _CUTS_LOGGING_SERVER_H_
#define _CUTS_LOGGING_SERVER_H_

#include "Logging_Server_Options.h"
#include "LoggingServer_i.h"
#include "cuts/Servant_Manager_T.h"
#include "cuts/Servant_Traits_T.h"
#include "cuts/IOR_File_Trait.h"
#include "cuts/IOR_Table_Trait.h"

/**
 * @class CUTS_Logging_Server
 *
 * Defines the main entry point for the test logging server
 * application
 */
class CUTS_Logging_Server
{
public:
  /// Constructor
  CUTS_Logging_Server (void);

  /// Destructor
  virtual ~CUTS_Logging_Server (void);

  /**
   * Run the logging server.
   *
   * @param[in]     argc          Number of command-line arguments
   * @param[in]     argv          Command-line arguments
   */
  int run_main (int argc, char * argv[]);

  /// Shutdown the application.
  void shutdown (void);

  /// Destroy the server resources.
  void destroy (void);

private:
  /// Helper function for parsing command-line arguments.
  int parse_args (int argc, char * argv[]);

  /// Helper function for print help.
  void print_help (void);

  /// Reference to the CORBA ORB.
  ::CORBA::ORB_var orb_;

  /// Reference to the RootPOA
  ::PortableServer::POA_var root_poa_;

  /// The actual implemenation of the server.
  CUTS_LoggingServer_i server_;

  typedef
    CUTS_Servant_Trait_T <CUTS_IOR_File_Trait,
    CUTS_Servant_Trait_T <CUTS_IOR_Table_Trait> > traits_type;

  /// Servant manager for the logging server servant.
  CUTS_Servant_Manager_Ex_T <CUTS_LoggingServer_i, traits_type> servant_mgr_;

  /// Logging server options.
  CUTS_Logging_Server_Options opts_;
};

#if defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#endif  // !defined _CUTS_TEST_LOGGING_SERVER_H_
