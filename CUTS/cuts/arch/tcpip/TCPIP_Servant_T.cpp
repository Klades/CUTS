// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_T.inl"
#endif

#include "ace/CORBA_macros.h"

//
// vtable_
//
template <typename T, typename CTX, typename EXEC>
CUTS_TCPIP_Servant_VTable_T <T> CUTS_TCPIP_Servant_T <T, CTX, EXEC>::vtable_;

//
// CUTS_TCPIP_Servant_T
//
template <typename T, typename CTX, typename EXEC>
CUTS_TCPIP_Servant_T <T, CTX, EXEC>::
CUTS_TCPIP_Servant_T (T * servant, CUTS_TCPIP_Component * impl)
: servant_ (servant)
{
  // Create the context for the servant/executor.
  CTX * context = 0;
  ACE_NEW_THROW_EX (context, CTX (), ACE_bad_alloc ());
  this->ctx_ = context;

  // Narrow the executor implementation.
  this->impl_ = EXEC::_narrow (impl);

  // Set the session context of the implementation.
  this->impl_->set_session_context (this->ctx_);
}
