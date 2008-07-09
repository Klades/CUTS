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

#include "TestManager_i.h"
#include "ace/Task.h"

// Forward decl.
class CUTS_Testing_App;

// Forward decl.
class CUTS_TestManager_i;

/**
 * @class CUTS_Testing_App_Server
 */
class CUTS_Testing_App_Server
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         parent        Parent testing application.
   */
  CUTS_Testing_App_Server (CUTS_Testing_App & parent);

  /// Destructor.
  ~CUTS_Testing_App_Server (void);

  /**
   * Run the testing application's server. This method will spawn
   * a service thread that handle's the server's request so the caller
   * can continue execution.
   *
   * @param[in]         argc          Number of command-line arguments.
   * @param[in]         argv          The command-line arguments.
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the server.
  int shutdown (void);

private:
  /// Service thread for the server. This actually runs the ORB's
  /// main event loop so control can return to the main part of
  /// the application.
  static ACE_THR_FUNC_RETURN svc_run (void * param);

  /// Helper method to register TestManager with IORTable.
  int register_with_iortable (void);

  /// Parent testing app for the server.
  CUTS_Testing_App & parent_;

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// The RootPOA for the server.
  PortableServer::POA_var root_poa_;

  /// Test manager for the server.
  ACE_Auto_Ptr <CUTS_TestManager_i> test_manager_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;

  /// Group id of the service thread.
  int thr_grp_id_;
};

#endif  // !defined _CUTS_TESTING_APP_SERVER_H_
