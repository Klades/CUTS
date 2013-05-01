// $Id$

#if !defined (__CUTS_INLINE__)
#include "Portico_Publisher_T.inl"
#endif

#include "Portico_ObjectClass_Trait_T.h"

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void Portico_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  if (0 != this->factory_.get () && this->tag_ == ACE_Utils::UUID::NIL_UUID)
  {
    // Register a new object instance since one does not exist
    // at the time.
    RTI::ObjectClassHandle objclass_handle = this->factory_->get_handle ();
    this->obj_handle_ = this->rtiamb_->registerObjectInstance (objclass_handle);
    ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (this->tag_);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - managing object instance %d; tag=%s\n"),
                this->obj_handle_,
                this->tag_.to_string ()->c_str ()));
  }

  // Pass control to the base class.
  Portico_Publisher::connect (p);
}

//
// allocate_event
//
template <typename EVENT>
EVENT * Portico_Publisher_T <EVENT>::allocate_event (void)
{
  return this->factory_->create ();
}

//
// send_event
//
template <typename EVENT>
void Portico_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  if (0 == this->obj_handle_)
    return;

  // Cast the event to an Portico_ObjectClass object.
  Portico_ObjectClass * objclass = dynamic_cast <Portico_ObjectClass *> (ev);

  if (0 == objclass)
    throw CORBA::INTERNAL ();

  // Write the attributes.
  std::auto_ptr <RTI::AttributeHandleValuePairSet>
    attrs (RTI::AttributeSetFactory::create (
    Portico_ObjectClass_Trait_T <EVENT>::attr_count));

  objclass->__hla_write_attributes (*attrs);

  // Send the event to the event consumer.
  this->send_event (*attrs);
}

//
// init
//
template <typename EVENT>
void Portico_Publisher_T <EVENT>::init (RTI::RTIambassador * rtiamb)
{
  // Initilize the publisher's factory object.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  objectclass_factory_type * factory = 0;
  ACE_NEW_THROW_EX (factory,
                    objectclass_factory_type (rtiamb),
                    CORBA::NO_MEMORY ());
  this->factory_.reset (factory);

  // Get a list of attributes for this object class. This is done
  // by first allocating a set large enough to hold all the attributes,
  // and then asking the factory to populate the handle set.
  std::auto_ptr <RTI::AttributeHandleSet>
    attrs (RTI::AttributeHandleSetFactory::create (
    Portico_ObjectClass_Trait_T <EVENT>::attr_count));

  this->factory_->get_attributes (*attrs);

  // Let the RTI know that we are publishing these attributes.
  RTI::ObjectClassHandle objclass_handle = this->factory_->get_handle ();
  rtiamb->publishObjectClass (objclass_handle, *attrs);

  // Register a new instance of the object class.
  this->obj_handle_ = rtiamb->registerObjectInstance (objclass_handle);

  // Store the RTI ambassador.
  this->rtiamb_ = rtiamb;
}

//
// disconnect
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
Portico_Publisher_T <EVENT>::disconnect (void)
{
  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer =
    Portico_Publisher::disconnect ();

  if (0 != this->obj_handle_)
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deleting object instance %d\n"),
                this->obj_handle_));

    // Delete this object instance since it is no longer needed.
    this->rtiamb_->deleteObjectInstance (this->obj_handle_, 0);
    this->obj_handle_ = 0;
  }

  return consumer;
}

}
