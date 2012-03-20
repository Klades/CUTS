// -*- C++ -*-
// $Id$

#include "Tron_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_Container_Strategy.inl"
#endif

#include "Tron_Container.h"
#include "../servant/Tron_Servant.h"

namespace iCCM
{

//
// install_servant
//
void Tron_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an Tron_Servant
  // by using 'dynamic_cast <Tron_Servant *> (servant)'.
}

//
// configure_servant
//
void Tron_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  // NOTE: The servant can be casted to an Tron_Servant
  // by using 'dynamic_cast <Tron_Servant *> (servant)'.
  // Also, the ConfigValues passed into this method are the same
  // configuration values attached to a component instance.
  for (size_t i = 0; i < values.length (); ++ i)
  {
//  const char * param = 0;
//  config[i].name >>= param;

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - found param: %s\n"), values[i]->name ()));
  }


}

//
// remove_servant
//
void Tron_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an Tron_Servant
  // by using 'dynamic_cast <Tron_Servant *> (servant)'.
}

}
