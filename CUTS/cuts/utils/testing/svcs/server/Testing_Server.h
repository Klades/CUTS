// -*- C++ -*-

//=============================================================================
/**
 * @file          Testing_App_Server.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_APP_SERVER_H_
#define _CUTS_TESTING_APP_SERVER_H_

#include "cuts/utils/testing/Testing_Service.h"
#include "tao/PortableServer/Servant_Base.h"
#include "orbsvcs/CosNamingC.h"
#include "ace/Task.h"

// Forward decl.
class CUTS_TestManager_i;

/**
 * @class CUTS_Testing_Server
 */
class CUTS_Testing_Server : public CUTS_Testing_Service
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         parent        Parent testing application.
   */
  CUTS_Testing_Server (void);

  /// Destructor.
  virtual ~CUTS_Testing_Server (void);

  /**
   * Run the testing application's server. This method will spawn
   * a service thread that handle's the server's request so the caller
   * can continue execution.
   *
   * @param[in]         argc          Number of command-line arguments.
   * @param[in]         argv          The command-line arguments.
   */
  virtual int init (int argc, char * argv []);

  /// Shutdown the server.
  virtual int fini (void);

private:
  /// Print the help message to the screen.
  void print_help (void);

  /**
   * Parse the command-line arguments.
   */
  virtual int parse_args (int argc, char * argv []);

  /// Service thread for the server. This actually runs the ORB's
  /// main event loop so control can return to the main part of
  /// the application.
  static ACE_THR_FUNC_RETURN svc_run (void * param);

  /// The service thread for the CORBA aspect.
  int orb_svc (void);

  /// Helper method to register TestManager with IORTable.
  int register_with_iortable (void);

  /// Helper method to register TestManager with naming service.
  int register_with_name_service (void);

  /// Helper method to unregister TestManger with the name service.
  int unregister_with_name_service (void);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// Test manager for the server.
  CUTS_TestManager_i * test_manager_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;

  /// Register the daemon with the naming service.
  bool register_with_ns_;

  /// The root context of the naming service.
  CosNaming::NamingContextExt_var root_ctx_;
};

#endif  // !defined _CUTS_TESTING_APP_SERVER_H_
