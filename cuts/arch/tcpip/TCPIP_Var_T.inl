// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Var_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::CUTS_TCPIP_Var_T (void)
: ptr_ (0)
{

}

//
// CUTS_TCPIP_Var_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::CUTS_TCPIP_Var_T (T * ptr)
: ptr_ (ptr)
{

}

//
// CUTS_TCPIP_Var_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::CUTS_TCPIP_Var_T (const CUTS_TCPIP_Var_T & copy)
: ptr_ (copy.ptr_)
{
  this->ptr_->incr_refcount ();
}

//
// ~CUTS_TCPIP_Var_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::~CUTS_TCPIP_Var_T (void)
{
  this->ptr_->decr_refcount ();
}

//
// operator ->
//
template <typename T>
CUTS_INLINE
T * CUTS_TCPIP_Var_T <T>::operator -> (void)
{
  return this->ptr_;
}

//
// operator ->
//
template <typename T>
CUTS_INLINE
const T * CUTS_TCPIP_Var_T <T>::operator -> (void) const
{
  return this->ptr_;
}

//
// operator *
//
template <typename T>
CUTS_INLINE
T & CUTS_TCPIP_Var_T <T>::operator * (void)
{
  return *this->ptr_;
}

//
// operator *
//
template <typename T>
CUTS_INLINE
const T & CUTS_TCPIP_Var_T <T>::operator * (void) const
{
  return *this->ptr_;
}

//
// operator T *
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::operator T * (void)
{
  return this->ptr_;
}

//
// operator const T *
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_Var_T <T>::operator const T * (void) const
{
  return this->ptr_;
}
