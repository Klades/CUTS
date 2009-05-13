// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_ComponentServer_App.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COMPONENTSERVER_APP_H_
#define _CUTS_TCPIP_CCM_COMPONENTSERVER_APP_H_

#include "cuts/ORB_Server_Task.h"
#include "TCPIP_CCM_ComponentServer_Opts.h"
#include "TCPIP_CCM_ComponentServer.h"

/**
 * @class CUTS_TCPIP_CCM_ComponentServer_App
 *
 * Main application for the TCP/IP component server.
 */
class CUTS_TCPIP_CCM_ComponentServer_App
{
public:
  /// Default constructor.
  CUTS_TCPIP_CCM_ComponentServer_App (void);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_ComponentServer_App (void);

  virtual int run_main (int argc, char * argv []);

  virtual void destroy (void);

  virtual void shutdown (void);

private:
  int parse_arg (int argc, char * argv []);

  static void register_valuetypes (CORBA::ORB_ptr orb);

  void print_help (void);

  int configure_component_server (::CIAO::Deployment::ServerActivator_ptr activator);

  CUTS_TCPIP_CCM_ComponentServer_Opts opts_;

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// The root POA for the server.
  PortableServer::POA_var root_;

  /// Task object for the component server.
  CUTS_ORB_Server_Task task_;

  /// The compnent server object.
  CUTS_TCPIP_CCM_ComponentServer server_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer_App.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_APP_H_
