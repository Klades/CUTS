// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

//
// CUTS_TCPIP_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
CUTS_TCPIP_CCM_Servant_T <T, CONTEXT, EXEC, POA_EXEC>::
CUTS_TCPIP_CCM_Servant_T (const char * name,
                          T * servant,
                          CUTS_TCPIP_Servant_Manager & svnt_mgr,
                          typename EXEC::_ptr_type executor)
: CUTS_CCM_Servant_T <CONTEXT, EXEC, POA_EXEC> (name, executor),
  CUTS_TCPIP_Servant_T <T> (servant),
  svnt_mgr_ (svnt_mgr)
{
  // Create the context for the servant/executor.
  CONTEXT * context = 0;
  ACE_NEW_THROW_EX (context,
                    CONTEXT (*servant),
                    ::CORBA::NO_MEMORY ());

  // Set the session context of the implementation.
  this->ctx_.reset (context);
  this->impl_->set_session_context (this->ctx_.get ());

  // Activate the object.
  this->svnt_mgr_.activate_object (this);
}

//
// remove
//
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
void CUTS_TCPIP_CCM_Servant_T <T, CONTEXT, EXEC, POA_EXEC>::remove (void)
{
  this->svnt_mgr_.deactivate_object (this->the_UUID ());

  if (this->impl_)
    this->impl_->ccm_remove ();
}

//
// activate_component
//
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
void CUTS_TCPIP_CCM_Servant_T <T, CONTEXT, EXEC, POA_EXEC>::activate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_activate ();
}

//
// passivate_component
//
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
void CUTS_TCPIP_CCM_Servant_T <T, CONTEXT, EXEC, POA_EXEC>::passivate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_passivate ();
}

//
// configuration_complete
//
template <typename T, typename CONTEXT, typename EXEC, typename POA_EXEC>
void CUTS_TCPIP_CCM_Servant_T <T, CONTEXT, EXEC, POA_EXEC>::configuration_complete (void)
{
  if (this->impl_)
    this->impl_->configuration_complete ();
}
