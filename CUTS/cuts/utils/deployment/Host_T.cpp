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
// size
//
template <typename T>
size_t CUTS_Host_T <T>::size (void) const
{
  return this->items_.size ();
}
