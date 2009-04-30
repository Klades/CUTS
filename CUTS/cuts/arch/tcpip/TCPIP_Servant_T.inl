// -*- C++ -*-
// $Id$

//
// ~CUTS_TCPIP_Servant_T
//
template <typename T, typename CTX, typename EXEC>
CUTS_INLINE
CUTS_TCPIP_Servant_T <T, CTX, EXEC>::~CUTS_TCPIP_Servant_T (void)
{

}

//
// handle_event
//
template <typename T, typename CTX, typename EXEC>
CUTS_INLINE
int CUTS_TCPIP_Servant_T <T, CTX, EXEC>::
handle_event (ACE_UINT32 id, ACE_InputCDR & input)
{
  if (id < this->vtable_.size ())
    return (this->servant_->*this->vtable_[id]) (input);

  return -1;
}

//
// configuration_complete
//
template <typename T, typename CTX, typename EXEC>
void CUTS_TCPIP_Servant_T <T, CTX, EXEC>::configuration_complete (void)
{
  if (this->impl_)
    this->impl_->configuration_complete ();
}

//
// ccm_activate
//
template <typename T, typename CTX, typename EXEC>
void CUTS_TCPIP_Servant_T <T, CTX, EXEC>::ccm_activate (void)
{
  if (this->impl_)
    this->impl_->ccm_activate ();
}

//
// ccm_passivate
//
template <typename T, typename CTX, typename EXEC>
void CUTS_TCPIP_Servant_T <T, CTX, EXEC>::ccm_passivate (void)
{
  if (this->impl_)
    this->impl_->ccm_passivate ();
}

//
// ccm_remove
//
template <typename T, typename CTX, typename EXEC>
void CUTS_TCPIP_Servant_T <T, CTX, EXEC>::ccm_remove (void)
{
  if (this->impl_)
    this->impl_->ccm_remove ();
}
