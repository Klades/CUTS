// -*- C++ -*-

//=============================================================================
/**
 * @file          CCM_Component_Instance_Handler_T.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_COMPONENT_INSTANCE_HANDLER_T_H_
#define _CUTS_CCM_COMPONENT_INSTANCE_HANDLER_T_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "dance/DAnCE_LocalityManagerC.h"
#include "ciao/Containers/Container_BaseC.h"
#include "ccm/CCM_CookieC.h"
#include "tao/PortableServer/PortableServer.h"
#include "tao/LocalObject.h"

#include <set>
#include <map>

/**
 * @class CUTS_CCM_Component_Instance_Handler_T
 */
template <typename HANDLER, typename CONTAINER>
class CUTS_CCM_Component_Instance_Handler_T :
  public virtual ::DAnCE::InstanceDeploymentHandler,
  public virtual ::CORBA::LocalObject
{
public:
  /// Type definition of the handler type.
  typedef HANDLER handler_type;

  /// Type definition of the container type.
  typedef CONTAINER container_type;

  /// Default constructor
  CUTS_CCM_Component_Instance_Handler_T (void);

  /// Destructor
  virtual ~CUTS_CCM_Component_Instance_Handler_T (void);

  virtual char * instance_type (void);

  ::CORBA::StringSeq * dependencies (void);

  virtual void install_instance (const ::Deployment::DeploymentPlan & plan,
                                 ::CORBA::ULong instanceRef,
                                 ::CORBA::Any_out instance_reference);

  virtual void activate_instance (const ::Deployment::DeploymentPlan & ,
                                  ::CORBA::ULong ,
                                  const ::CORBA::Any &);

  virtual void passivate_instance (const ::Deployment::DeploymentPlan & ,
                                   ::CORBA::ULong ,
                                   const ::CORBA::Any &);

  virtual void remove_instance (const ::Deployment::DeploymentPlan & plan,
                                ::CORBA::ULong instanceRef,
                                const ::CORBA::Any & instance_reference);

  virtual void provide_endpoint_reference (const ::Deployment::DeploymentPlan &,
                                           ::CORBA::ULong,
                                           ::CORBA::Any_out);

  virtual void connect_instance (const ::Deployment::DeploymentPlan & plan,
                                 ::CORBA::ULong connectionRef,
                                 const ::CORBA::Any & provided_reference);

  virtual void disconnect_instance (const ::Deployment::DeploymentPlan & plan,
                                    ::CORBA::ULong connectionRef);

  virtual void instance_configured (const ::Deployment::DeploymentPlan &,
                                    ::CORBA::ULong);

  virtual void configure (const Deployment::Properties &);

  virtual void close (void);

protected:
  /// The only and only container for now. :-)
  ::CIAO::Container_var container_;

private:
  const char * get_implementation (const char *name,
                                   const ::Deployment::DeploymentPlan &plan);

  void create_attribute_configuration (const ::Deployment::Properties &props,
                                       ::Components::ConfigValues & values);

  /// Helper method to register values types with current ORB.
  static void register_valuetypes (::CORBA::ORB_ptr);

  /// Reference to the ORB.
  ::CORBA::ORB_var orb_;

  /// Reference to POA passed to created containers.
  ::PortableServer::POA_var poa_;

  typedef std::set <::Components::Cookie_var> cookies;

  typedef std::map <std::string, cookies > cookie_map;

  cookie_map cookies_;
};

#include "CCM_Component_Instance_Handler_T.cpp"

#endif  // !defined _CUTS_COMPONENT_INSTANCE_HANDLER_H_
