// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Servant_VTable_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Servant_VTable_T <T>::CUTS_TCPIP_Servant_VTable_T (void)
: is_init_ (false)
{

}

//
// ~CUTS_TCPIP_Servant_VTable_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Servant_VTable_T <T>::~CUTS_TCPIP_Servant_VTable_T (void)
{

}

//
// lock
//
template <typename T>
CUTS_INLINE
bool CUTS_TCPIP_Servant_VTable_T <T>::is_init (void) const
{
  return this->is_init_;
}

template <typename T>
CUTS_INLINE
size_t CUTS_TCPIP_Servant_VTable_T <T>::size (void) const
{
  return this->vtable_.size ();
}

//
// operator []
//
template <typename T>
CUTS_INLINE
typename CUTS_TCPIP_Servant_VTable_T <T>::method_type &
CUTS_TCPIP_Servant_VTable_T <T>::operator [] (size_t index)
{
  return this->vtable_[index];
}

//
// operator []
//
template <typename T>
CUTS_INLINE
const typename CUTS_TCPIP_Servant_VTable_T <T>::method_type &
CUTS_TCPIP_Servant_VTable_T <T>::operator [] (size_t index) const
{
  return this->vtable_[index];
}
