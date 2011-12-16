// -*- C++ -*-
// $Id$

//
// Portico_CCM_Instance_Handler
//
CUTS_INLINE
Portico_CCM_Instance_Handler::Portico_CCM_Instance_Handler (void)
{

}

//
// ~Portico_CCM_Instance_Handler
//
CUTS_INLINE
Portico_CCM_Instance_Handler::~Portico_CCM_Instance_Handler (void)
{

}

//
// get_fedinfo
//
CUTS_INLINE
const Portico_CCM_Instance_Handler::FED &
Portico_CCM_Instance_Handler::get_fedinfo (void) const
{
  return this->fedinfo_;
}
