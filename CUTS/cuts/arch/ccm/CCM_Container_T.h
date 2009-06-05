// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_Container_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_CONTAINER_T_H_
#define _CUTS_CCM_CONTAINER_T_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ccm/ComponentServer/CCM_ComponentServer_ClientC.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "CCM_Container_Strategy_T.h"

/**
 * @class CUTS_CCM_Container
 */
template <typename T, typename SERVER, typename STRATEGY, typename SERVANT_BASE>
class CUTS_CCM_Container_T :
  public POA_CIAO::Deployment::Container
{
public:
  /// Type definition of the container type.
  typedef T container_type;

  /// Type definition of the container's component server.
  typedef SERVER server_type;

  /// Type definition of the container's strategy.
  typedef STRATEGY strategy_type;

  /// Type definition of the servant base type.
  typedef SERVANT_BASE servant_base_type;

  /**
   * Initializing constructor.
   */
  CUTS_CCM_Container_T (SERVER * server,
                        const Components::ConfigValues & config,
                        ::PortableServer::POA_ptr poa,
                        ::Components::Deployment::ComponentInstallation_ptr installer);

  /// Destructor.
  virtual ~CUTS_CCM_Container_T (void);

  /// Get the component server that create the container.
  SERVER * server (void);

  virtual Components::ConfigValues * configuration (void);

  virtual ::Components::Deployment::ComponentServer_ptr get_component_server (void);

  virtual ::Components::CCMHome_ptr install_home (const char *,
                                                  const char *,
                                                  const ::Components::ConfigValues &);

  virtual void remove_home (::Components::CCMHome_ptr home);

  virtual Components::CCMHomes * get_homes (void);

  virtual void remove (void);

  virtual ::Components::CCMObject_ptr
    install_component (const char * id,
                       const char * entrypt,
                       const ::Components::ConfigValues & config);

  virtual void activate_component (::Components::CCMObject_ptr comp);

  virtual void passivate_component (::Components::CCMObject_ptr comp);

  virtual void remove_component (::Components::CCMObject_ptr cref);

  virtual ::Components::CCMObjectSeq * get_components (void);

protected:
  void copy (::Components::ConfigValues & dst, const ::Components::ConfigValues & src);

  /// Pointer to the concrete container object.
  SERVER * server_;

  /// The actual strategy for the container.
  ACE_Auto_Ptr <STRATEGY> strategy_;

  /// The current configuration for the container.
  ::Components::ConfigValues_var config_;

  /// The POA for instantianting servants.
  ::PortableServer::POA_var poa_;

  /// Type definition for the install components.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                ::PortableServer::ServantBase_var,
                                ACE_RW_Thread_Mutex> components_type;

  /// Collection of installed components.
  components_type components_;

  /// Installer for the components.
  ::Components::Deployment::ComponentInstallation_var installer_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Container_T.inl"
#endif

#include "CCM_Container_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_H_
