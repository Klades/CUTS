// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_ComponentServer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_COMPONENTSERVER_T_H_
#define _CUTS_CCM_COMPONENTSERVER_T_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "ace/Unbounded_Set.h"
#include "CCM_export.h"

// Forward decl.
class CUTS_CCM_ComponentServer_Callback;

/**
 * @class CUTS_CCM_ComponentServer_T
 *
 * Template implementation of a component server.
 */
template <typename T, typename CONTAINER>
class CUTS_CCM_ComponentServer_T :
  public POA_CIAO::Deployment::ComponentServer
{
public:
  /// Type definition of the server type.
  typedef T server_type;

  /// Type definition of the container type.
  typedef CONTAINER container_type;

  /**
   * Initializing constructor.
   */
  CUTS_CCM_ComponentServer_T (CUTS_CCM_ComponentServer_Callback * callback);

  /// Destructor.
  virtual ~CUTS_CCM_ComponentServer_T (void);

  virtual int init (int argc, char * argv []);

  virtual void configure (::CIAO::Deployment::ServerActivator_ptr activator,
                          ::Components::ConfigValues * config,
                          ::PortableServer::POA_ptr poa);

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
  CUTS_CCM_ComponentServer_Callback * callback_;

  /// POA for activating containers.
  ::PortableServer::POA_var poa_;

  /// The server activator from the node manager.
  ::CIAO::Deployment::ServerActivator_var activator_;

  /// The configuration for this component server.
  ::Components::ConfigValues_var config_;

  /// Type definition for the collection of containers.
  typedef ACE_Unbounded_Set <CONTAINER *> container_set;

  /// Collection of containers on this component server.
  container_set containers_;

  // Installation object for the component.
  ::CIAO::Deployment::ComponentInstallation_var installer_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_ComponentServer_T.inl"
#endif

#include "CCM_ComponentServer_T.cpp"

#endif  // !defined _CUTS_CCM_COMPONENTSERVER_T_H_
