// -*- C++ -*-
// $Id$

#include "Portico_CCM_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Container_Strategy.inl"
#endif

#include "Portico_CCM_Container.h"
#include "Portico_CCM_Instance_Handler.h"

#include "../ccm/Portico_CCM_Servant.h"

//
// install_servant
//
void
Portico_CCM_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  // Cast the servant to a Portico servant, then locate the
  // RTI ambassador for the corresponding servant.
  Portico_CCM_Servant * federate = dynamic_cast <Portico_CCM_Servant *> (servant);

  if (0 == federate)
    throw ::Deployment::StartError ("StartError", "servant is not a Portico servant");

  // Get references to entities need to register this servant
  // as a federate in the execution.
  const Portico_CCM_Instance_Handler::FED & fedinfo =
    this->container_.inst_handler ()->get_fedinfo ();

  if (0 != federate->install (fedinfo.file_, fedinfo.execution_))
    throw ::Deployment::StartError ("StartError", "failed to install federate");
}

//
// configure_servant
//
void
Portico_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant, const ::Components::ConfigValues & )
{

}

//
// remove_servant
//
void
Portico_CCM_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{

}
