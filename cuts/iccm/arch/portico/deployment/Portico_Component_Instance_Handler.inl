// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Portico_Component_Instance_Handler
//
CUTS_INLINE
Portico_Component_Instance_Handler::Portico_Component_Instance_Handler (void)
{

}

//
// ~Portico_Component_Instance_Handler
//
CUTS_INLINE
Portico_Component_Instance_Handler::~Portico_Component_Instance_Handler (void)
{

}

//
// get_fedinfo
//
CUTS_INLINE
const Portico_Component_Instance_Handler::FED &
Portico_Component_Instance_Handler::get_fedinfo (void) const
{
  return this->fedinfo_;
}

}
