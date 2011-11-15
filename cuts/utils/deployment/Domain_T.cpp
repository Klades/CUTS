// $Id$

#if !defined (__CUTS_INLINE__)
#include "Domain_T.inl"
#endif

//
// operator =
//
template <typename T>
const CUTS_Domain_T <T> & CUTS_Domain_T <T>::
operator = (const CUTS_Domain_T <T> & rhs)
{
  if (this != &rhs)
    this->items_ = rhs.items_;

  return *this;
}
