#include "CHAOS_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Container_Strategy.inl"
#endif

#include "CHAOS_Container.h"
#include "../servant/CHAOS_Servant.h"
#include "CHAOS_Component_Instance_Handler.h"

namespace iCCM
{

CHAOS_Container_Strategy::
CHAOS_Container_Strategy (CHAOS_Container & container)
: base_type (container)
{
}

void CHAOS_Container_Strategy::
install_servant (::PortableServer::Servant servant)
{

}

void CHAOS_Container_Strategy::
configure_servant (::PortableServer::Servant s, const ::Components::ConfigValues & values)
{
  // First, configure the servant.
  CHAOS_Servant * svnt = dynamic_cast < CHAOS_Servant * > (s);

  if (svnt != 0)
    svnt->handle_config (values);

  // Then, let each architecture specific handler configure the servants
  // managed by the chaos servant.
  // 
  // It would be better if each servant and deployment handler shared a 
  // common value that can could be used to determine if a servant could 
  // be configured by a deployment handler.
  typedef CHAOS_Servant::servant_map_type::const_iterator servant_iterator;
  typedef CHAOS_Component_Instance_Handler::handler_map_t::const_iterator handler_iterator;

  const CHAOS_Servant::servant_map_type & servants = svnt->servants ();
  const CHAOS_Component_Instance_Handler::handler_map_t & handlers = this->container_.inst_handler ()->instance_handlers ();

  for (servant_iterator svIt = servants.begin (); svIt != servants.end (); ++svIt)
  {
    for (handler_iterator hdIt = handlers.begin (); hdIt != handlers.end (); ++hdIt)
    {
      hdIt->second->get_container ()->get_strategy ()->configure_servant (svIt->item (), values);
    }
  }
}

//
// remove_servant
//
void CHAOS_Container_Strategy::
remove_servant (::PortableServer::Servant servant)
{
  // NOTE: The servant can be casted to an CHAOS_Servant
  // by using 'dynamic_cast <CHAOS_Servant *> (servant)'.
}

}
