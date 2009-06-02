// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Container_Strategy_T
//
template <typename SERVER>
CUTS_INLINE
CUTS_CCM_Container_Strategy_T <SERVER>::
CUTS_CCM_Container_Strategy_T (SERVER * server)
: server_ (server)
{

}

//
// ~CUTS_CCM_Container_Strategy_T
//
template <typename SERVER>
CUTS_INLINE
CUTS_CCM_Container_Strategy_T <SERVER>::~CUTS_CCM_Container_Strategy_T (void)
{

}

//
// load_executor
//
template <typename SERVER>
CUTS_INLINE
::Components::EnterpriseComponent_ptr
CUTS_CCM_Container_Strategy_T <SERVER>::
load_executor (const char *, const char *)
{
  return ::Components::EnterpriseComponent::_nil ();
}

//
// load_servant
//
template <typename SERVER>
CUTS_INLINE
::PortableServer::Servant
CUTS_CCM_Container_Strategy_T <SERVER>::
load_servant (const char *, const char *, const char *, ::Components::EnterpriseComponent_ptr)
{
  return 0;
}
