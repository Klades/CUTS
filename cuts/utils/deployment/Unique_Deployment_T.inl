// -*- C++ -*-
// $Id$

//
// CUTS_Unique_Deployment_T
//
template <typename T>
CUTS_INLINE
CUTS_Unique_Deployment_T <T>::CUTS_Unique_Deployment_T (void)
{

}

//
// ~CUTS_Unique_Deployment_T
//
template <typename T>
CUTS_INLINE
CUTS_Unique_Deployment_T <T>::~CUTS_Unique_Deployment_T (void)
{

}

//
// size
//
template <typename T>
CUTS_INLINE
size_t CUTS_Unique_Deployment_T <T>::size (void) const
{
  return this->deployments_.size ();
}
