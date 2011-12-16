// Id: CCM_Publisher.cpp.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_Publisher.cpp 3086 2011-01-22 05:53:51Z hillj

#include "Portico_CCM_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher.inl"
#endif

//
// ~Portico_CCM_Publisher
//
Portico_CCM_Publisher::~Portico_CCM_Publisher (void)
{
  if (0 != this->obj_handle_)
    this->rtiamb_->deleteObjectInstance (this->obj_handle_, 0);
}

//
// connect
//
void Portico_CCM_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow the base consumer to a consumer of our type. This way, we
  // can validate the consumer and make sure we are not working with
  // a consumer type we do not know about.
  ::Components::Portico::EventConsumer_var consumer =
    ::Components::Portico::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  this->connect (consumer.in ());
}

//
// connect
//
void Portico_CCM_Publisher::
connect (::Components::Portico::EventConsumer_ptr consumer)
{
  // Let the consumer know what object instance they are observing
  // on this connection. We then need to store a copy of the
  // consumer locally for disconnecting.
  if (this->tag_ != ACE_Utils::UUID::NIL_UUID)
    consumer->observe_object (this->tag_.to_string ()->c_str ());

  this->consumer_ = ::Components::Portico::EventConsumer::_duplicate (consumer);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr Portico_CCM_Publisher::disconnect (void)
{
  if (this->tag_ != ACE_Utils::UUID::NIL_UUID)
    this->consumer_->unobserve_object (this->tag_.to_string ()->c_str ());

  return this->consumer_._retn ();
}

//
// send_event
//
void Portico_CCM_Publisher::
send_event (const RTI::AttributeHandleValuePairSet & attrs)
{
  this->rtiamb_->updateAttributeValues (this->obj_handle_,
                                        attrs,
                                        "");
}

