// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_Object_T
//
template <typename MUTEX>
CUTS_INLINE
CUTS_TCPIP_Object_T <MUTEX>::CUTS_TCPIP_Object_T (void)
: refcount_ (1)
{

}

//
// ~CUTS_TCPIP_Object_T
//
template <typename MUTEX>
CUTS_INLINE
CUTS_TCPIP_Object_T <MUTEX>::~CUTS_TCPIP_Object_T (void)
{

}

//
// incr_refcount
//
template <typename MUTEX>
CUTS_INLINE
void CUTS_TCPIP_Object_T <MUTEX>::incr_refcount (void)
{
  ++ this->refcount_;
}

//
// decr_refcount
//
template <typename MUTEX>
CUTS_INLINE
void CUTS_TCPIP_Object_T <MUTEX>::decr_refcount (void)
{
  if (0 == -- this->refcount_)
    delete this;
}

//
// incr_refcount
//
template <typename MUTEX>
CUTS_INLINE
size_t CUTS_TCPIP_Object_T <MUTEX>::refcount (void) const
{
  return this->refcount_.value ();
}
