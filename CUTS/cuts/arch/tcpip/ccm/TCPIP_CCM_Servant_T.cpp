// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Servant_T.inl"
#endif

//
// CUTS_TCPIP_CCM_Servant_T
//
template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::
CUTS_TCPIP_CCM_Servant_T (T * servant,
                          CUTS_TCPIP_Servant_Manager & svnt_mgr,
                          typename EXEC::_ptr_type executor)
: base_type (servant, executor),
  svnt_mgr_ (svnt_mgr)
{
  this->svnt_mgr_.activate_object (this);
}

template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE void
CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::remove (void)
{
  this->svnt_mgr_.deactivate_object (this->the_UUID ());

  if (this->impl_)
    this->impl_->ccm_remove ();
}

template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::activate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_activate ();
}

template <typename T, typename CTX, typename EXEC, typename POA_EXEC>
CUTS_INLINE
void CUTS_TCPIP_CCM_Servant_T <T, CTX, EXEC, POA_EXEC>::passivate_component (void)
{
  if (this->impl_)
    this->impl_->ccm_passivate ();
}

