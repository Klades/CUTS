// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Servant_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Servant_T <T>::
CUTS_TCPIP_Servant_T (T * servant, size_t vtable_size)
: vtable_ (vtable_size),
  servant_ (servant)
{

}

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
CUTS_INLINE int
CUTS_TCPIP_Servant_T <T>::handle_event (ACE_UINT32 id, ACE_Message_Block & ev)
{
  if (id < this->vtable_.size ())
    return (this->servant_->*this->vtable_[id]) (ev);

  return -1;
}
