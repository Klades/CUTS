// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_ref_t

//
// CUTS_ref_t
//
template <typename T>
CUTS_INLINE
CUTS_ref_t <T>::CUTS_ref_t (T & ref)
: ref_ (ref)
{

}

//
// CUTS_ref_t
//
template <typename T>
CUTS_INLINE
CUTS_ref_t <T>::CUTS_ref_t (const CUTS_ref_t & ref)
: ref_ (ref.ref_)
{

}

//
// ~CUTS_ref_t
//
template <typename T>
CUTS_INLINE
CUTS_ref_t <T>::~CUTS_ref_t (void)
{

}

//
// operator =
//
template <typename T>
CUTS_INLINE
const CUTS_ref_t <T> & CUTS_ref_t <T>::
operator = (const CUTS_ref_t <T> & rhs)
{
  this->ref_ = rhs.ref_;
  return *this;
}

//
// operator T &
//
template <typename T>
CUTS_INLINE
CUTS_ref_t <T>::operator T & (void) const
{
  return this->ref_;
}

//
// CUTS_ref
//
template <typename T>
CUTS_INLINE
CUTS_ref_t <T> CUTS_ref (T & ref)
{
  return CUTS_ref_t <T> (ref);
}

template <typename T>
CUTS_INLINE
T & CUTS_value_of (const CUTS_ref_t <T> & ref)
{
  return ref;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_cref_t

//
// CUTS_cref_t
//
template <typename T>
CUTS_INLINE
CUTS_cref_t <T>::CUTS_cref_t (const T & cref)
: cref_ (cref)
{

}

//
// CUTS_cref_t
//
template <typename T>
CUTS_INLINE
CUTS_cref_t <T>::CUTS_cref_t (const CUTS_cref_t & cref)
: cref_ (cref.cref_)
{

}

//
// ~CUTS_cref_t
//
template <typename T>
CUTS_INLINE
CUTS_cref_t <T>::~CUTS_cref_t (void)
{

}

//
// operator =
//
template <typename T>
CUTS_INLINE
const CUTS_cref_t <T> & CUTS_cref_t <T>::
operator = (const CUTS_cref_t <T> & rhs)
{
  this->cref_ = rhs.cref_;
  return *this;
}

//
// operator T &
//
template <typename T>
CUTS_INLINE
CUTS_cref_t <T>::operator const T & (void) const
{
  return this->cref_;
}

//
// CUTS_ref
//
template <typename T>
CUTS_INLINE
CUTS_cref_t <T> CUTS_cref (const T & cref)
{
  return CUTS_cref_t <T> (cref);
}

//
// CUTS_dereference
//
template <typename T>
CUTS_INLINE
const T & CUTS_value_of (const CUTS_cref_t <T> & ref)
{
  return ref;
}
