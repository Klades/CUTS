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

#include "ciao/Containers/Session/Session_ContainerC.h"
#include "tao/PortableServer/Servant_Base.h"

#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/SString.h"

#include "CCM_Container_Strategy_T.h"

/**
 * @class CUTS_CCM_Container_T
 */
template <typename T, typename INST_HANDLER, typename STRATEGY, typename SERVANT_BASE>
class CUTS_CCM_Container_T :
  public ::CIAO::Session_Container
{
public:
  /// Type definition of the container type.
  typedef T container_type;

  /// Type definition of the container's component server.
  typedef INST_HANDLER server_type;

  /// Type definition of the container's strategy.
  typedef STRATEGY strategy_type;

  /// Type definition of the servant base type.
  typedef SERVANT_BASE servant_base_type;

  /**
   * Initializing constructor.
   */
  CUTS_CCM_Container_T (INST_HANDLER * server, ::PortableServer::POA_ptr poa);

  /// Destructor.
  virtual ~CUTS_CCM_Container_T (void);

  /// Get the component server that create the container.
  INST_HANDLER * inst_handler (void);

  virtual void init (const char * name);

  virtual void fini (void);

  virtual ::Components::CCMHome_ptr
    install_home (const char * primary_artifact,
                  const char * entry_point,
                  const char * servant_artifact,
                  const char * servant_entrypoint,
                  const char * name);

  virtual void uninstall_home (::Components::CCMHome_ptr home);

  virtual ::Components::CCMObject_ptr
    install_component (const char * primary_artifact,
                       const char * entry_point,
                       const char * servant_artifact,
                       const char * servant_entrypoint,
                       const char * name);

  virtual void
    set_attributes (::CORBA::Object_ptr name,
                    const ::Components::ConfigValues & values);

  virtual void remove (void);

  virtual void activate_component (::Components::CCMObject_ptr comp);

  virtual void passivate_component (::Components::CCMObject_ptr comp);

  virtual void uninstall_component (::Components::CCMObject_ptr cref);

  virtual ::Components::Cookie *
    connect_local_facet (::Components::CCMObject_ptr,
                         const char * ,
                         ::Components::CCMObject_ptr,
                         const char *);

  virtual void
    disconnect_local_facet (::Components::Cookie *,
                            ::Components::CCMObject_ptr,
                            const char * ,
                            ::Components::CCMObject_ptr,
                            const char *);

  virtual ::CORBA::Object_ptr
    install_servant (::PortableServer::Servant svnt,
                     ::CIAO::Container_Types::OA_Type type,
                     ::PortableServer::ObjectId_out oid);

  virtual void
    uninstall_servant (::PortableServer::Servant compptr,
                       ::CIAO::Container_Types::OA_Type type,
                       ::PortableServer::ObjectId_out oid);

  virtual ::CORBA::Object_ptr
    generate_reference (const char * obj_id,
                        const char * repo_id,
                        ::CIAO::Container_Types::OA_Type type);

  virtual ::CORBA::Object_ptr
    get_objref (::PortableServer::Servant p);

  virtual ::PortableServer::POA_ptr the_POA (void);

  virtual ::PortableServer::POA_ptr the_port_POA (void);

  virtual ::CORBA::Object_ptr
    resolve_service_reference (const char * service_id);

#if !defined (CUTS_CCM_CONTAINER_LACKS_SERVANT_ACTIVATOR)
  virtual ::CIAO::Servant_Activator_ptr ports_servant_activator (void);
#endif

protected:
  void initialize_the_POA (::PortableServer::POA_ptr);
  void initialize_the_port_POA (::PortableServer::POA_ptr);

  /// Pointer to the concrete container object.
  INST_HANDLER * inst_handler_;

  /// The actual strategy for the container.
  ACE_Auto_Ptr <STRATEGY> strategy_;

  /// The current configuration for the container.
  ::Components::ConfigValues_var config_;

  /// The POA for instantianting servants.
  ::PortableServer::POA_var poa_;

  /// The POA for instantianting servants.
  ::PortableServer::POA_var port_poa_;

  /// Type definition for the install components.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                ::PortableServer::ServantBase_var,
                                ACE_RW_Thread_Mutex> servant_map;

  /// Collection of installed components.
  servant_map components_;

  /// Name assigned to the container.
  ACE_CString name_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Container_T.inl"
#endif

#include "CCM_Container_T.cpp"

#endif  // !defined _CUTS_TCPIP_CCM_CONTAINER_H_
