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
// load_executor
//
template <typename CONTAINER>
CUTS_INLINE
::Components::EnterpriseComponent_ptr
CUTS_CCM_Container_Strategy_T <CONTAINER>::
load_executor (const char *, const char *)
{
  return ::Components::EnterpriseComponent::_nil ();
}

//
// load_servant
//
template <typename CONTAINER>
CUTS_INLINE
::PortableServer::Servant
CUTS_CCM_Container_Strategy_T <CONTAINER>::
load_servant (const char *, const char *, const char *, ::Components::EnterpriseComponent_ptr)
{
  return 0;
}
