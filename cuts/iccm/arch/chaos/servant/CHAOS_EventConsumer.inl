// -*- C++ -*-
// $IdCHAOS_CCM_EventConsumer.inl 2687 2009-06-02 21:20:04Z hillj $

namespace iCCM
{

//
// CHAOS_EventConsumer
//
CUTS_INLINE
CHAOS_EventConsumer::CHAOS_EventConsumer (void)
: impl_ (0)
{

}

//
// ~CHAOS_EventConsumer
//
CUTS_INLINE
CHAOS_EventConsumer::~CHAOS_EventConsumer (void)
{

}

//
// activate
//
CUTS_INLINE
void CHAOS_EventConsumer::activate (void)
{
  this->impl_->activate ();
}

//
// passivate
//
CUTS_INLINE
void CHAOS_EventConsumer::passivate (void)
{
  this->impl_->passivate ();
}


}
