// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_ComponentServer.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
#define _CUTS_TCPIP_CCM_COMPONENTSERVER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "cuts/arch/tcpip/TCPIP_ComponentServer.h"
#include "cuts/ORB_Server_Task.h"
#include "ace/Unbounded_Set.h"
#include "TCPIP_CCM_ComponentServer_Opts.h"

// Forward decl.
class CUTS_TCPIP_CCM_ComponentServer_App;

// Forward decl.
class CUTS_TCPIP_CCM_Container;

/**
 * @class CUTS_TCPIP_CCM_ComponentServer
 *
 * Implementation of the CIAO component server for TCP/IP.
 */
class CUTS_TCPIP_CCM_ComponentServer :
  public POA_CIAO::Deployment::ComponentServer,
  public CUTS_TCPIP_ComponentServer
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_TCPIP_CCM_ComponentServer (CUTS_TCPIP_CCM_ComponentServer_App * app);

  /// Destructor.
  virtual ~CUTS_TCPIP_CCM_ComponentServer (void);

  void configure (::CIAO::Deployment::ServerActivator_ptr activator,
                  ::Components::ConfigValues * config,
                  ::PortableServer::POA_ptr poa);

  void shutdown (bool notify = false);

  /// {
  virtual void shutdown (void);

  virtual
    Components::ConfigValues *
    configuration (void);

  virtual
    Components::Deployment::ServerActivator_ptr
    get_server_activator (void);

  virtual
    Components::Deployment::Container_ptr
    create_container (const Components::ConfigValues &);

  virtual
    void remove_container (Components::Deployment::Container_ptr);

  virtual
    Components::Deployment::Containers *
    get_containers (void);

  virtual void remove (void);
  /// }
private:
  /// Parent application of the component server.
  CUTS_TCPIP_CCM_ComponentServer_App * app_;

  /// POA for activating containers.
  PortableServer::POA_var poa_;

  ::CIAO::Deployment::ServerActivator_var activator_;

  ::Components::ConfigValues_var config_;

  typedef ACE_Unbounded_Set <CUTS_TCPIP_CCM_Container *> container_set;

  container_set containers_;

  // Installation object for the component.
  ::CIAO::Deployment::ComponentInstallation_var installer_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_ComponentServer.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_COMPONENTSERVER_H_
