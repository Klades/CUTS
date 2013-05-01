// -*- C++ -*-
// $Id$

#include "Portico_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_Container_Strategy.inl"
#endif

#include "Portico_Container.h"
#include "../servant/Portico_Servant.h"
#include "dance/Deployment/Deployment_StartErrorC.h"
#include "Portico_Component_Instance_Handler.h"

namespace iCCM
{

//
// install_servant
//
void Portico_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an Portico_Servant
  // by using 'dynamic_cast <Portico_Servant *> (servant)'.
  Portico_Servant * federate = dynamic_cast <Portico_Servant *> (servant);

  if (0 == federate)
    throw ::Deployment::StartError ("StartError", "servant is not a Portico servant");

  // Get references to entities need to register this servant
  // as a federate in the execution.
  const Portico_Component_Instance_Handler::FED & fedinfo =
    this->container_.inst_handler ()->get_fedinfo ();

  if (0 != federate->install (fedinfo.file_, fedinfo.execution_))
    throw ::Deployment::StartError ("StartError", "failed to install federate");
}

//
// configure_servant
//
void Portico_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  // NOTE: The servant can be casted to an Portico_Servant
  // by using 'dynamic_cast <Portico_Servant *> (servant)'.
  // Also, the ConfigValues passed into this method are the same
  // configuration values attached to a component instance.
}

//
// remove_servant
//
void Portico_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an Portico_Servant
  // by using 'dynamic_cast <Portico_Servant *> (servant)'.
}

}
