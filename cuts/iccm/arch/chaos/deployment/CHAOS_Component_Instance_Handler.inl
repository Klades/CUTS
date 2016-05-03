// -*- C++ -*-
// $Id$

namespace iCCM
{

CUTS_INLINE
CHAOS_Component_Instance_Handler::~CHAOS_Component_Instance_Handler (void)
{

}

CUTS_INLINE
const CHAOS_Component_Instance_Handler::handler_map_t &
CHAOS_Component_Instance_Handler::instance_handlers (void) const
{
  return this->known_handlers_;
}

}
