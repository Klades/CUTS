// -*- C++ -*-
// $Id$

//
// ~CUTS_TCPIP_Servant_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Servant_T <T>::~CUTS_TCPIP_Servant_T (void)
{

}

//
// handle_event
//
template <typename T>
CUTS_INLINE
int CUTS_TCPIP_Servant_T <T>::
handle_event (ACE_UINT32 id, CUTS_TCPIP_InputCDR & input)
{
  if (id < this->vtable_.size ())
    return (this->vtable_[id]) (this->servant_, input);

  return -1;
}
