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

#include "Testing_App.h"
#include "tao/PortableServer/Servant_Base.h"
#include "ace/Task.h"

// Forward decl.
class CUTS_TestManager_i;

/**
 * @class CUTS_Testing_App_Server
 */
class CUTS_Testing_App_Server : public CUTS_Testing_App
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         parent        Parent testing application.
   */
  CUTS_Testing_App_Server (void);

  /// Destructor.
  virtual ~CUTS_Testing_App_Server (void);

  /**
   * Run the testing application's server. This method will spawn
   * a service thread that handle's the server's request so the caller
   * can continue execution.
   *
   * @param[in]         argc          Number of command-line arguments.
   * @param[in]         argv          The command-line arguments.
   */
  virtual int run_main (int argc, char * argv []);

  /// Shutdown the server.
  virtual int shutdown (void);

private:
  /**
   * Parse the command-line arguments.
   */
  virtual int parse_args (int argc, char * argv []);

  /// Service thread for the server. This actually runs the ORB's
  /// main event loop so control can return to the main part of
  /// the application.
  static ACE_THR_FUNC_RETURN svc_run (void * param);

  /// Helper method to register TestManager with IORTable.
  int register_with_iortable (void);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// Test manager for the server.
  CUTS_TestManager_i * test_manager_;

  /// POA servant.
  PortableServer::ServantBase_var servant_;
};

#endif  // !defined _CUTS_TESTING_APP_SERVER_H_
