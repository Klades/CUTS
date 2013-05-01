// $Id$

#include "Portico_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_Publisher.inl"
#endif

namespace iCCM
{

//
// ~Portico_Publisher
//
Portico_Publisher::~Portico_Publisher (void)
{
  if (0 != this->obj_handle_)
    this->rtiamb_->deleteObjectInstance (this->obj_handle_, 0);
}

//
// connect
//
void Portico_Publisher::
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
void Portico_Publisher::
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
::Components::EventConsumerBase_ptr
Portico_Publisher::disconnect (void)
{
  if (this->tag_ != ACE_Utils::UUID::NIL_UUID)
    this->consumer_->unobserve_object (this->tag_.to_string ()->c_str ());

  // Return ownership to the caller. This will allow the caller
  // to gracefully destroy the event consumer.
  return this->consumer_._retn ();
}

//
// send_event
//
void Portico_Publisher::
send_event (const RTI::AttributeHandleValuePairSet & attrs)
{
  this->rtiamb_->updateAttributeValues (this->obj_handle_,
                                        attrs,
                                        "");
}

}
