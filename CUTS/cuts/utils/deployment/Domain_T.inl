// $Id$
// -*- C++ -*-

//
// CUTS_Domain_T
//
template <typename T>
CUTS_INLINE
CUTS_Domain_T <T>::CUTS_Domain_T (void)
{

}

//
// CUTS_Domain_T
//
template <typename T>
CUTS_INLINE
CUTS_Domain_T <T>::CUTS_Domain_T (const CUTS_Domain_T & domain)
: items_ (domain.items_)
{

}

//
// ~CUTS_Domain_T
//
template <typename T>
CUTS_INLINE
CUTS_Domain_T <T>::~CUTS_Domain_T (void)
{

}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Domain_T <T>::iterator CUTS_Domain_T <T>::begin (void)
{
  return this->items_.begin ();
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Domain_T <T>::const_iterator CUTS_Domain_T <T>::begin (void) const
{
  return this->items_.begin ();
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Domain_T <T>::iterator CUTS_Domain_T <T>::end (void)
{
  return this->items_.end ();
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Domain_T <T>::const_iterator CUTS_Domain_T <T>::end (void) const
{
  return this->items_.end ();
}

//
// size
//
template <typename T>
CUTS_INLINE
size_t CUTS_Domain_T <T>::size (void) const
{
  return this->items_.size ();
}

template <typename T>
CUTS_INLINE
bool CUTS_Domain_T <T>::insert (T item)
{
  return this->items_.insert (item).second;
}
