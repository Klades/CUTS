// $Id$

#if !defined (__CUTS_INLINE__)
#include "Deployment_T.inl"
#endif

//
// operator =
//
template <typename T>
const CUTS_Deployment_T <T> &
CUTS_Deployment_T <T>::operator = (const CUTS_Deployment_T & rhs)
{
  if (this != &rhs)
    this->hosts_ = rhs.hosts_;

  return *this;
}
