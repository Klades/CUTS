// -*- C++ -*-
// $Id$

//
// CUTS_Deployment_T
//
template <typename T>
CUTS_INLINE
CUTS_Deployment_T <T>::CUTS_Deployment_T (void)
{

}

//
// CUTS_Deployment_T
//
template <typename T>
CUTS_INLINE
CUTS_Deployment_T <T>::CUTS_Deployment_T (const CUTS_Deployment_T & copy)
: hosts_ (copy.hosts_)
{

}

//
// ~CUTS_Deployment_T
//
template <typename T>
CUTS_INLINE
CUTS_Deployment_T <T>::~CUTS_Deployment_T (void)
{

}

//
// insert
//
template <typename T>
CUTS_INLINE
bool CUTS_Deployment_T <T>::insert (item_type item)
{
  return this->hosts_.insert (item).second;
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Deployment_T <T>::iterator
CUTS_Deployment_T <T>::begin (void)
{
  return this->hosts_.begin ();
}

//
// begin
//
template <typename T>
CUTS_INLINE
typename CUTS_Deployment_T <T>::const_iterator
CUTS_Deployment_T <T>::begin (void) const
{
  return this->hosts_.begin ();
}

//
// end
//
template <typename T>
CUTS_INLINE
typename CUTS_Deployment_T <T>::iterator
CUTS_Deployment_T <T>::end (void)
{
  return this->hosts_.end ();
}

//
// end
//
template <typename T>
CUTS_INLINE
typename CUTS_Deployment_T <T>::const_iterator
CUTS_Deployment_T <T>::end (void) const
{
  return this->hosts_.end ();
}
