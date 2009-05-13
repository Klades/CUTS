// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_CCM_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_CCM_CONTAINER_H_
#define _CUTS_TCPIP_CCM_CONTAINER_H_

#include "ciao/ComponentServer/CIAO_ComponentServerS.h"
#include "ccm/CCM_ContainerC.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"
#include "cuts/arch/tcpip/config.h"

class CUTS_TCPIP_CCM_ComponentServer;

/**
 * @class CUTS_TCPIP_CCM_Container
 */
class CUTS_TCPIP_CCM_Container :
  public POA_CIAO::Deployment::Container
{
public:
  CUTS_TCPIP_CCM_Container (CUTS_TCPIP_CCM_ComponentServer & parent,
                            const Components::ConfigValues & config,
                            ::PortableServer::POA_ptr poa);

  virtual ~CUTS_TCPIP_CCM_Container (void);

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

private:
  void init (const ::Components::ConfigValues & config);

  void copy (::Components::ConfigValues & dst, const ::Components::ConfigValues & src);

  ::Components::EnterpriseComponent_ptr
    load_executor (const ::Components::ConfigValue & artifact, const char * entrypt);

  ::PortableServer::Servant load_servant (const char * name,
                                          const ::Components::ConfigValue & artifact,
                                          const ::Components::ConfigValue & entrypt,
                                          ::Components::EnterpriseComponent_ptr executor);

  CUTS_TCPIP_CCM_ComponentServer & parent_;

  ::Components::ConfigValues_var config_;

  ::PortableServer::POA_var poa_;

  /// Type definition for the install components.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                ::PortableServer::ServantBase_var,
                                ACE_RW_Thread_Mutex> components_type;

  /// Collection of installed components.
  components_type components_;
};

#if defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Container.inl"
#endif

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_H_
