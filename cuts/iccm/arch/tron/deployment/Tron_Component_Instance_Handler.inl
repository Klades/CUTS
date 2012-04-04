// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Tron_Component_Instance_Handler
//
CUTS_INLINE
Tron_Component_Instance_Handler::Tron_Component_Instance_Handler (void)
: tac_mgr_ (&tac_, false),
  init_complete_ (false)
{

}

//
// ~Tron_Component_Instance_Handler
//
CUTS_INLINE
Tron_Component_Instance_Handler::~Tron_Component_Instance_Handler (void)
{

}

}
