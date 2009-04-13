// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Component_T.inl"
#endif

//
// set_session_context
//
template <typename T, typename CTX>
void CUTS_CCM_Component_T <T, CTX>::
set_session_context (Components::SessionContext_ptr ctx)
{
  // Store the context for the component.
  this->ctx_ = CTX::_narrow (ctx);
  
  if (::CORBA::is_nil (this->ctx_.in ()))
    throw ::CORBA::INTERNAL ();
}
