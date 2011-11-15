// -*- C++ -*-

//=============================================================================
/**
 * @file        NodeDaemon_Client_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_CLIENT_APP_H_
#define _CUTS_NODEDAEMON_CLIENT_APP_H_

#include "cuts/config.h"
#include "tao/corba.h"

/**
 * @class CUTS_NodeDaemon_Client_App
 */
class CUTS_NodeDaemon_Client_App
{
public:
  /// Default constructor.
  CUTS_NodeDaemon_Client_App (void);

  /// Destructor.
  ~CUTS_NodeDaemon_Client_App (void);

  /**
   * Main entry point for the application.
   *
   * @param[in]     argc        Number of command-line arguments
   * @param[in]     argv        The command-line arguments
   */
  int run_main (int argc, char * argv []);

private:
  /// Helper method to parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method to print help.
  void print_help (void);

  /// The ORB for the client application.
  ::CORBA::ORB_var orb_;

  /// Reset the active environment.
  bool reset_env_;

  /// Set the active environment.
  ACE_CString set_active_env_;

  /// Get the active environment.
  bool get_active_env_;
};

#if defined (__CUTS_INLINE__)
#include "NodeDaemon_Client_App.inl"
#endif


#endif  // !defined _CUTS_NODEDAEMON_CLIENT_APP_H_
