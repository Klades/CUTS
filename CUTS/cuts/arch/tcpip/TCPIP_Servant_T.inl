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
