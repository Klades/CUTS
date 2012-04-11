// -*- C++ -*-
// $Id$

#include "Tron_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "Tron_Container_Strategy.inl"
#endif

#include "Tron_Container.h"
#include "../servant/Tron_Servant.h"
#include "TestAdapter_i.h"

namespace iCCM
{

//
// install_servant
//
void Tron_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{
  Tron_Servant * tron_servant = dynamic_cast <Tron_Servant *> (servant);

  if (0 == tron_servant)
    return;

  // Set the servant's reporter. This will allow the servant to
  // register all its input/output ports with the reporter and
  // TRON/UPPAAL.
  tron_servant->init (this->container_.inst_handler ()->get_reporter (),
                      this->container_.inst_handler ()->get_consumer_map ());
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
