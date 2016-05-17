// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// CHAOS_Container
//
CUTS_INLINE
CHAOS_Container::
CHAOS_Container (CHAOS_Component_Instance_Handler * handler, ::PortableServer::POA_ptr poa)
: base_type (handler, poa)
{

}

//
// ~CHAOS_Container
//
CUTS_INLINE
CHAOS_Container::~CHAOS_Container (void)
{

}

}
