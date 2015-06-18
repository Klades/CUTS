// $IdQpidPB_Publisher_Table_T.cpp 3289 2012-02-10 03:05:18Z hillj $

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_Table_T.inl"
#endif

#include "cuts/iccm/servant/Cookie.h"

namespace iCCM
{

//
// allocate_event
//
template <typename EVENT>
EVENT * QpidPB_Publisher_Table_T <EVENT>::allocate_event (void)
{
  return this->sender_.allocate_event ();
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
QpidPB_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  // Make sure this is a valid consumer.
  ::Components::QpidPB::EventConsumer_var consumer =
    ::Components::QpidPB::EventConsumer::_narrow (consumer_base);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  // Pass control to the base class.
  ::Components::Cookie_var cookie = this->base_type::subscribe (consumer_base);

  // Tell the consumer to connect
  consumer->configure (this->host_.c_str (), this->port_, this->queue_.c_str ());

  return cookie._retn ();
}

//
// unsubscribe
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
QpidPB_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
{
  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer_base = this->base_type::unsubscribe (c);

  // Notify the event consumer they no longer need to observe
  // events from this publisher.
  ::Components::QpidPB::EventConsumer_var consumer =
    ::Components::QpidPB::EventConsumer::_narrow (consumer_base);

  return consumer_base;
}

//
// send_event
//
template <typename EVENT>
void QpidPB_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  this->sender_.send_event (ev);
}

//
// activate
//
template <typename EVENT>
void QpidPB_Publisher_Table_T <EVENT>::activate (void)
{
  QpidPB_Publisher_Table::activate ();
  this->sender_.activate (this->connection_, this->queue_);
}

//
// passivate
//
template <typename EVENT>
void QpidPB_Publisher_Table_T <EVENT>::passivate (void)
{
  this->sender_.passivate ();
  QpidPB_Publisher_Table::passivate ();
}

}
