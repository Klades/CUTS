// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Var_T.inl"
#endif

//
// operator =
//
template <typename T>
const CUTS_TCPIP_Var_T <T> &
CUTS_TCPIP_Var_T <T>::operator = (T * ptr)
{
  if (this->ptr_ != ptr && 0 != this->ptr_)
    this->ptr_->decr_refcount ();

  this->ptr_ = ptr;
  return *this;
}

//
// operator =
//
template <typename T>
const CUTS_TCPIP_Var_T <T> &
CUTS_TCPIP_Var_T <T>::operator = (const CUTS_TCPIP_Var_T & rhs)
{
  // Prevent self assignment.
  if (this == &rhs)
    return *this;

  // First, we need to increment the right-hand side reference
  // count. This will ensure that we do not accidently delete
  // the object during this assignment operation.
  if (0 != rhs.ptr_)
    rhs.ptr_->incr_refcount ();

  // Save the pointer to the right-hand side.
  T * temp = this->ptr_;
  this->ptr_ = rhs.ptr_;

  // Decrement the current object's reference count.
  if (0 != temp)
    temp->decr_refcount ();

  return *this;
}

//
// _retn
//
template <typename T>
T * CUTS_TCPIP_Var_T <T>::_retn (void)
{
  T * temp = this->ptr_;
  this->ptr_ = 0;
  return temp;
}
