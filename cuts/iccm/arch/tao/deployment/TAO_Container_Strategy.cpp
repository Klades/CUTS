// -*- C++ -*-
// $Id$

#include "TAO_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "TAO_Container_Strategy.inl"
#endif

#include "TAO_Container.h"
#include "../servant/TAO_Servant.h"

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
