// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_Servant_Manager_T

//
// CUTS_Servant_Manager_T
//
template <typename T>
CUTS_INLINE
CUTS_Servant_Manager_T <T>::CUTS_Servant_Manager_T (T * servant, bool managed)
: servant_ (servant),
  is_managed_ (managed)
{

}

//
// get
//
template <typename T>
CUTS_INLINE
T * CUTS_Servant_Manager_T <T>::get (void)
{
  return this->servant_;
}

//
// operator ->
//
template <typename T>
CUTS_INLINE
T * CUTS_Servant_Manager_T <T>::operator -> (void)
{
  return this->servant_;
}

//
// operator ->
//
template <typename T>
CUTS_INLINE
bool CUTS_Servant_Manager_T <T>::is_managed (void) const
{
  return this->is_managed_;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Servant_Manager_Ex_T

//
// CUTS_Servant_Manager_Ex_T
//
template <typename T, typename TRAITS>
CUTS_INLINE
CUTS_Servant_Manager_Ex_T <T, TRAITS>::
CUTS_Servant_Manager_Ex_T (T * servant, bool managed)
: CUTS_Servant_Manager_T <T> (servant, managed)
{

}

//
// ~CUTS_Servant_Manager_Ex_T
//
template <typename T, typename TRAITS>
CUTS_INLINE
CUTS_Servant_Manager_Ex_T <T, TRAITS>::~CUTS_Servant_Manager_Ex_T (void)
{
  this->deactivate ();
}

//
// set_trait_value
//
template <typename T, typename TRAITS>
template <typename TRAIT>
CUTS_INLINE
int CUTS_Servant_Manager_Ex_T <T, TRAITS>::
set_trait_value (TRAIT trait, const ACE_CString & value)
{
  return this->traits_.set_value (trait.ID, value);
}

//
// get_trait_value
//
template <typename T, typename TRAITS>
template <typename TRAIT>
CUTS_INLINE
int CUTS_Servant_Manager_Ex_T <T, TRAITS>::
get_trait_value (TRAIT trait, ACE_CString & value)
{
  return this->traits_.get_value (trait.ID, value);
}
