// -*- C++ -*-
// $Id$

//
// CUTS_Host_T
//
template <typename T>
CUTS_INLINE
CUTS_Host_T <T>::CUTS_Host_T (void)
{

}

//
// CUTS_Host_T
//
template <typename T>
CUTS_INLINE
CUTS_Host_T <T>::CUTS_Host_T (const std::string & name)
: name_ (name)
{

}

//
// CUTS_Host_T
//
template <typename T>
CUTS_INLINE
CUTS_Host_T <T>::CUTS_Host_T (const CUTS_Host_T & host)
: name_ (host.name_),
  items_ (host.items_)
{

}

//
// ~CUTS_Host_T
//
template <typename T>
CUTS_INLINE
CUTS_Host_T <T>::~CUTS_Host_T (void)
{

}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Host_T <T>::iterator CUTS_Host_T <T>::begin (void)
{
  return this->items_.begin ();
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Host_T <T>::const_iterator CUTS_Host_T <T>::begin (void) const
{
  return this->items_.begin ();
}

//
// end
//
template <typename T>
CUTS_INLINE
typename CUTS_Host_T <T>::iterator CUTS_Host_T <T>::end (void)
{
  return this->items_.end ();
}

//
// end
//
template <typename T>
CUTS_INLINE
typename CUTS_Host_T <T>::const_iterator CUTS_Host_T <T>::end (void) const
{
  return this->items_.end ();
}

//
// name
//
template <typename T>
CUTS_INLINE
const std::string & CUTS_Host_T <T>::name (void) const
{
  return this->name_;
}

//
// name
//
template <typename T>
CUTS_INLINE
void CUTS_Host_T <T>::name (const std::string & name)
{
  this->name_ = name;
}

//
// operator ==
//
template <typename T>
CUTS_INLINE
bool CUTS_Host_T <T>::operator == (const CUTS_Host_T & host) const
{
  return this->name_ == host.name_;
}

//
// operator <
//
template <typename T>
CUTS_INLINE
bool CUTS_Host_T <T>::operator < (const CUTS_Host_T & host) const
{
  return this->name_ < host.name_;
}

//
// operator >
//
template <typename T>
CUTS_INLINE
bool CUTS_Host_T <T>::operator > (const CUTS_Host_T & host) const
{
  return this->name_ > host.name_;
}

//
// operator >
//
template <typename T>
CUTS_INLINE
bool CUTS_Host_T <T>::insert (item_type item)
{
  return this->items_.insert (item).second;
}
