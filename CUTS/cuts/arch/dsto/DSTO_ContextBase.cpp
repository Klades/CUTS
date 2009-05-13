#include "DSTO_ContextBase.h"

namespace CUTS_DSTO
{
  ContextBase::ContextBase (void)
  {
  }
  
  ContextBase::~ContextBase (void)
  {
  }

  ::Components::Principal_ptr
  ContextBase::get_caller_principal (void)
  {
    return ::Components::Principal::_nil ();
  }
  
  ::Components::CCMHome_ptr
  ContextBase::get_CCM_home (void)
  {
    return ::Components::CCMHome::_nil ();
  }
  
  ::CORBA::Boolean
  ContextBase::get_rollback_only (void)
  {
    return false;
  }
  
  ::Components::Transaction::UserTransaction_ptr
  ContextBase::get_user_transaction (void)
  {
    return ::Components::Transaction::UserTransaction::_nil ();
  }
  
  ::CORBA::Boolean
  ContextBase::is_caller_in_role (const char *)
  {
    return false;
  }
  
  void
  ContextBase::set_rollback_only (void)
  {
  }
  
  ::CORBA::Object_ptr
  ContextBase::resolve_service_reference (const char *)
  {
    return ::CORBA::Object::_nil ();
  }
  
  ::CORBA::Object_ptr
  ContextBase::get_CCM_object (void)
  {
    return ::CORBA::Object::_nil ();
  }
}