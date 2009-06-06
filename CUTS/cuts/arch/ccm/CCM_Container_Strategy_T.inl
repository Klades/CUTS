// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Container_Strategy_T
//
template <typename CONTAINER>
CUTS_INLINE
CUTS_CCM_Container_Strategy_T <CONTAINER>::
CUTS_CCM_Container_Strategy_T (CONTAINER * container)
: container_ (container)
{

}

//
// ~CUTS_CCM_Container_Strategy_T
//
template <typename CONTAINER>
CUTS_INLINE
CUTS_CCM_Container_Strategy_T <CONTAINER>::~CUTS_CCM_Container_Strategy_T (void)
{

}

//
// configure_servant
//
template <typename CONTAINER>
CUTS_INLINE void
CUTS_CCM_Container_Strategy_T <CONTAINER>::
configure_servant (::PortableServer::Servant ,
		   const ::Components::ConfigValues & )
{

}

