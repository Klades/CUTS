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

#ifndef _CUTS_CCM_COMPONENTSERVER_APP_T_H_
#define _CUTS_CCM_COMPONENTSERVER_APP_T_H_

#include "ciao/ComponentServer/CIAO_CS_ClientC.h"
#include "tao/PortableServer/PortableServer.h"
#include "cuts/arch/ccm/CCM_ComponentServer_Callback.h"
#include "cuts/ORB_Server_Task.h"

/**
 * @class CUTS_CCM_ComponentServer_App_T
 *
 * Template for the component server's application.
 */
template <typename T, typename IMPL>
class CUTS_CCM_ComponentServer_App_T :
  public CUTS_CCM_ComponentServer_Callback
{
public:
  /// Type definition of the parent type.
  typedef T type;

  /// Type definition fo the component server's implementation.
  typedef IMPL impl_type;

  /// Default constructor.
  CUTS_CCM_ComponentServer_App_T (void);

  /// Destructor.
  virtual ~CUTS_CCM_ComponentServer_App_T (void);

  /**
   * Run the main application.
   */
  int run_main (int argc, char * argv []);

  /// Destory the applications' resources.
  void destroy (void);

  /// Shutdown the application.
  virtual void shutdown (bool notify);

private:
  /// Helper method to register the value types.
  static void register_valuetypes (::CORBA::ORB_ptr orb);

  /// Helper method to parse the command-line options.
  int parse_standard_args (int argc, char * argv []);

  /// Helper method to configure the component server's implementation.
  int configure_component_server (::CIAO::Deployment::ServerActivator_ptr activator);

  /// The ORB for the server.
  CORBA::ORB_var orb_;

  /// The root POA for the server.
  PortableServer::POA_var root_;

  /// Task object for the component server.
  CUTS_ORB_Server_Task task_;

  /// The compnent server object.
  ACE_Auto_Ptr <IMPL> server_;

  /// Callback IOR for the server activator.
  ACE_CString callback_ior_;

  /// UUID for the component server.
  ACE_CString uuid_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_ComponentServer_App_T.inl"
#endif

#include "CCM_ComponentServer_App_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_APP_H_
