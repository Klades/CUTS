// $Id$

#if !defined (__CUTS_INLINE__)
#include "CCM_Single_Subscriber_T.inl"
#endif

//
// connect
//
template <typename T>
void CUTS_CCM_Single_Subscriber_T <T>::
connect (::Components::EventConsumerBase_ptr consumer)
{
  if (!::CORBA::is_nil (this->consumer_.in ()))
    throw ::Components::AlreadyConnected ();

  this->consumer_ = traits_type::consumer_type::_narrow (consumer);

  if (::CORBA::is_nil (this->consumer_.in ()))
    throw ::Components::InvalidConnection ();
}

//
// send_event
//
template <typename T>
void CUTS_CCM_Single_Subscriber_T <T>::send_event (T * ev)
{
  if (!::CORBA::is_nil (this->consumer_.in ()))
    this->consumer_->push_event (ev);
}
