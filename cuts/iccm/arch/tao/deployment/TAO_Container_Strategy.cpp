// -*- C++ -*-
// $Id$

#include "TAO_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TAO_Container_Strategy.inl"
#endif

#include "TAO_Container.h"
#include "../servant/TAO_Servant.h"
#include "TAO_Component_Instance_Handler.h"

namespace iCCM
{

//
// install_servant
//
void TAO_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{

}

//
// configure_servant
//
void TAO_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  // NOTE: The servant can be casted to an TAO_Servant
  // by using 'dynamic_cast <TAO_Servant *> (servant)'.
  // Also, the ConfigValues passed into this method are the same
  // configuration values attached to a component instance.
  TAO_Servant * tao_servant = dynamic_cast <TAO_Servant *> (servant);

  if (0 == tao_servant)
    return;

  // Register the servant's value types with the orb
  ::CORBA::ORB_ptr orb = this->container_.inst_handler ()->orb ();
  tao_servant->register_value_factories (orb);

  tao_servant->handle_config (values);
}

//
// remove_servant
//
void TAO_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an TAO_Servant
  // by using 'dynamic_cast <TAO_Servant *> (servant)'.
}

}
