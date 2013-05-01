// $Id$

#if !defined (__CUTS_INLINE__)
#include "Portico_EventConsumer_T.inl"
#endif

#include "Portico_ObjectClass_Trait_T.h"

namespace iCCM
{

//
// init
//
template <typename SERVANT, typename EVENT>
void Portico_EventConsumer_T <SERVANT, EVENT>::
init (RTI::RTIambassador * rtiamb)
{
  // Initilize the publisher's factory object.
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

  RTI::ObjectClassHandle obj_class = this->factory_->get_handle ();
  rtiamb->subscribeObjectClassAttributes (obj_class, *attrs);
  rtiamb->tick ();

  // Save the RTI ambassador handle.
  this->rtiamb_ = rtiamb;
}

//
// observe_object
//
template <typename SERVANT, typename EVENT>
void Portico_EventConsumer_T <SERVANT, EVENT>::
observe_object (const char * tag)
{
  Portico_EventConsumer::observe_object (tag);
}

//
// dispatch_event
//
template <typename SERVANT, typename EVENT>
void Portico_EventConsumer_T <SERVANT, EVENT>::
dispatch_event (const RTI::AttributeHandleValuePairSet & attrs)
{
  typedef
    typename Portico_ObjectClass_Trait_T <EVENT>::objectclass_event_type
    objectclass_event_type;

  // Create a new event for the callback.
  std::auto_ptr <objectclass_event_type> objclass (this->factory_->create ());
  objclass->__hla_read_attributes (attrs);

  // Make the callback.
  (this->servant_->*this->callback_)(objclass.get ());
}

}
