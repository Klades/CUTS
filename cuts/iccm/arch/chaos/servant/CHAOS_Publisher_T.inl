// -*- C++ -*-
// $IdCHAOS_Publisher_T.inl 3086 2011-01-22 05:53:51Z hillj $

namespace iCCM
{

//
// CHAOS_Publisher_T
//
template <typename EVENT>
CUTS_INLINE
CHAOS_Publisher_T <EVENT>::CHAOS_Publisher_T (void)
{

}

//
// ~CHAOS_Publisher_T
//
template <typename EVENT>
CUTS_INLINE
CHAOS_Publisher_T <EVENT>::~CHAOS_Publisher_T (void)
{

}

//
// allocate_event
//
template <typename EVENT>
CUTS_INLINE
EVENT * CHAOS_Publisher_T <EVENT>::allocate_event (void)
{
  // Need to return this->impl_->allocate_event ()
  return 0;
}

//
// send_event
//
template <typename EVENT>
void CHAOS_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  // Need to call into this->impl_->send_event (ev)
}

}
