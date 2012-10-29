// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// TAO_Component_Instance_Handler
//
CUTS_INLINE
TAO_Component_Instance_Handler::TAO_Component_Instance_Handler (void)
{

}

//
// ~TAO_Component_Instance_Handler
//
CUTS_INLINE
TAO_Component_Instance_Handler::~TAO_Component_Instance_Handler (void)
{

}

//
// orb
//
CUTS_INLINE
::CORBA::ORB_ptr
TAO_Component_Instance_Handler::orb (void)
{
  return this->get_orb ();
}

}
