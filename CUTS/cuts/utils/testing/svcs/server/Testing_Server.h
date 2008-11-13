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

#include "Testing_Server_export.h"
#include "Testing_Server_Task.h"
#include "TestManager_i.h"
#include "cuts/utils/testing/TAO_Testing_Service.h"
#include "tao/PortableServer/Servant_Base.h"
#include "orbsvcs/CosNamingC.h"

// Forward decl.
class CUTS_TestManager_i;

/**
 * @class CUTS_Testing_Server
 */
class CUTS_Testing_Server : public CUTS_TAO_Testing_Service
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

  /**
   * Get the ORB owned by this server.
   *
   * @return        Reference to the ORB.
   */
  CORBA::ORB_ptr the_ORB (void);

private:
  /// Print the help message to the screen.
  void print_help (void);

  /**
   * Parse the command-line arguments.
   */
  virtual int parse_args (int argc, char * argv []);

  /// Helper method to register TestManager with IORTable.
  static int register_with_iortable (CORBA::ORB_ptr orb,
                                     const char * name,
                                     const char * objstr);

  /// Helper method to register TestManager with naming service.
  int register_with_name_service (void);

  /// Helper method to unregister TestManger with the name service.
  int unregister_with_name_service (void);

  /// Test manager for the server.
  CUTS_TestManager_i * test_manager_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;

  /// Register the daemon with the naming service.
  bool register_with_ns_;

  /// The RootPOA for the server.
  PortableServer::POA_var root_poa_;

  PortableServer::POAManager_var poa_mgr_;

  /// The root context of the naming service.
  CosNaming::NamingContextExt_var root_ctx_;

  /// Task for the testing server.
  CUTS_Testing_Server_Task task_;
};

CUTS_TESTING_SERVICE_DECL (CUTS_TESTING_SERVER_Export, _make_CUTS_Testing_Server);

#endif  // !defined _CUTS_TESTING_APP_SERVER_H_
