// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Context_T
//
template <typename T, typename SVNT>
CUTS_INLINE
Context_T <T, SVNT>::Context_T (SVNT & svnt)
: svnt_ (svnt)
{

}

//
// ~Context_T
//
template <typename T, typename SVNT>
CUTS_INLINE
Context_T <T, SVNT>::~Context_T (void)
{

}

//
// get_home
//
template <typename T, typename SVNT>
CUTS_INLINE
::Components::CCMHome_ptr Context_T <T, SVNT>::get_CCM_home (void)
{
  return ::Components::CCMHome::_nil ();
}

//
// resolve_service_reference
//
template <typename T, typename SVNT>
CUTS_INLINE
::CORBA::Object_ptr
Context_T <T, SVNT>::resolve_service_reference (const char *)
{
  return ::CORBA::Object::_nil ();
}

//
// get_object
//
template <typename T, typename SVNT>
CUTS_INLINE
::CORBA::Object_ptr Context_T <T, SVNT>::get_CCM_object (void)
{
  return this->svnt_._this ();
}

#if !defined (CCM_LW)
//
// get_caller_principal
//
template <typename T, typename SVNT>
CUTS_INLINE
::Components::Principal_ptr Context_T <T, SVNT>::get_caller_principal (void)
{
  return ::Components::Principal::_nil ();
}

//
// get_rollback_only
//
template <typename T, typename SVNT>
CUTS_INLINE
::CORBA::Boolean Context_T <T, SVNT>::get_rollback_only (void)
{
  return false;
}

//
// get_user_transaction
//
template <typename T, typename SVNT>
CUTS_INLINE
::Components::Transaction::UserTransaction_ptr
Context_T <T, SVNT>::get_user_transaction (void)
{
  return ::Components::Transaction::UserTransaction::_nil ();
}

//
// is_caller_in_role
//
template <typename T, typename SVNT>
CUTS_INLINE
::CORBA::Boolean Context_T <T, SVNT>::is_caller_in_role (const char *)
{
  return false;
}

//
// set_rollback_only
//
template <typename T, typename SVNT>
CUTS_INLINE
void Context_T <T, SVNT>::set_rollback_only (void)
{

}

#endif

}
