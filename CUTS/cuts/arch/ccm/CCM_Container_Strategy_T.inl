// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Container_Strategy_T
//
template <typename CONTAINER>
CUTS_INLINE
CUTS_CCM_Container_Strategy_T <CONTAINER>::
CUTS_CCM_Container_Strategy_T (CONTAINER & container)
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
// install_servant
//
template <typename CONTAINER>
CUTS_INLINE void
CUTS_CCM_Container_Strategy_T <CONTAINER>::
install_servant (::PortableServer::Servant)
{

}

//
// configure_servant
//
template <typename CONTAINER>
CUTS_INLINE void
CUTS_CCM_Container_Strategy_T <CONTAINER>::
configure_servant (::PortableServer::Servant,
                   const ::Components::ConfigValues & )
{

}

//
// remove_servant
//
template <typename CONTAINER>
CUTS_INLINE void
CUTS_CCM_Container_Strategy_T <CONTAINER>::
remove_servant (::PortableServer::Servant)
{

}
