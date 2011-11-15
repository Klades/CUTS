// $Id$

#if !defined (__CUTS_INLINE__)
#include "Host_T.inl"
#endif

//
// operator =
//
template <typename T>
const CUTS_Host_T <T> & CUTS_Host_T <T>::operator = (const CUTS_Host_T & host)
{
  if (this != &host)
    this->items_ = host.items_;

  return *this;
}

//
// contains
//
