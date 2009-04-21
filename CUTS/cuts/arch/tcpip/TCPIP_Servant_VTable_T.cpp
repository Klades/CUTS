// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_VTable_T.inl"
#endif

//
// CUTS_TCPIP_Servant_VTable_Init_Guard_T
//
template <typename T>
CUTS_TCPIP_Servant_VTable_Init_Guard_T <T>::
CUTS_TCPIP_Servant_VTable_Init_Guard_T (CUTS_TCPIP_Servant_VTable_T <T> & vtable, size_t n)
: vtable_ (vtable),
  size_ (n)
{
  this->vtable_.lock_.acquire ();

  if (this->vtable_.vtable_.size () != n)
    this->vtable_.vtable_.size (n);
}

//
// CUTS_TCPIP_Servant_VTable_Init_Guard_T
//
template <typename T>
CUTS_TCPIP_Servant_VTable_Init_Guard_T <T>::
~CUTS_TCPIP_Servant_VTable_Init_Guard_T (void)
{
  if (this->vtable_.vtable_.size () == this->size_)
    this->vtable_.is_init_ = true;

  this->vtable_.lock_.release ();
}
