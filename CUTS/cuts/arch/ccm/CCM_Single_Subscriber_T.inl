// -*- C++ -*
// $Id$

//
// CUTS_CCM_Single_Subscriber_T
//
template <typename T>
CUTS_INLINE
CUTS_CCM_Single_Subscriber_T <T>::CUTS_CCM_Single_Subscriber_T (void)
{

}

//
// ~CUTS_CCM_Single_Subscriber_T
//
template <typename T>
CUTS_INLINE
CUTS_CCM_Single_Subscriber_T <T>::~CUTS_CCM_Single_Subscriber_T (void)
{

}

//
// disconnect
//
template <typename T>
CUTS_INLINE
::Components::EventConsumerBase_ptr
CUTS_CCM_Single_Subscriber_T <T>::disconnect (void)
{
  return this->consumer_._retn ();
}

