// Id: CCM_Publisher_Table.cpp.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_Publisher_Table.cpp 3086 2011-01-22 05:53:51Z hillj

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher_Table_T.inl"
#endif

#include "ace/OS_NS_unistd.h"
#include "fedtime.hh"

//
// init
//
template <typename EVENT>
void Portico_CCM_Publisher_Table_T <EVENT>::init (RTI::RTIambassador * rtiamb)
{
  // Initilize the publisher's factory object.
  typedef typename
    Portico_ObjectClass_Trait_T <EVENT>::objectclass_factory_type
    objectclass_factory_type;

  objectclass_factory_type * factory = 0;
  ACE_NEW_THROW_EX (factory,
                    objectclass_factory_type (rtiamb),
                    ::CORBA::NO_MEMORY ());
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
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - notifying RTI that ObjectClass ")
              ACE_TEXT ("type %d is being published\n"),
              objclass_handle));

  rtiamb->publishObjectClass (objclass_handle, *attrs);
  rtiamb->tick ();

  // Register a new instance of the object class. Regardless of the
  // number of consumers connected to this publisher, there is only
  // one object class instance from a publisher table. We create this
  // instance on demand to help safe resources.
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (this->tag_);
  this->obj_handle_ =
    rtiamb->registerObjectInstance (objclass_handle,
                                    this->tag_.to_string ()->c_str ());

  rtiamb->tick ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - publishing instance <%s> with ")
              ACE_TEXT ("object handle <%d>\n"),
              this->tag_.to_string ()->c_str (),
              this->obj_handle_));

  // Store the RTI ambassador.
  this->rtiamb_ = rtiamb;
}

//
// subscribe
//
template <typename EVENT>
::Components::Cookie *
Portico_CCM_Publisher_Table_T <EVENT>::
subscribe (::Components::EventConsumerBase_ptr consumer_base)
{
  // Pass control to the base class.
  ::Components::Cookie_var cookie = this->base_type::subscribe (consumer_base);

  // Notify the event consumer what event they are observing as
  // part of this connection.
  ::Components::Portico::EventConsumer_var consumer =
    ::Components::Portico::EventConsumer::_narrow (consumer_base);

  if (::CORBA::is_nil (consumer.in ()))
    throw ::CORBA::INTERNAL ();

  consumer->observe_object (this->tag_.to_string ()->c_str ());
  return cookie._retn ();
}

//
// unsubscribe
//
template <typename EVENT>
::Components::EventConsumerBase_ptr
Portico_CCM_Publisher_Table_T <EVENT>::unsubscribe (::Components::Cookie * c)
{
  // Pass control to the base class.
  ::Components::EventConsumerBase_ptr consumer_base = this->base_type::unsubscribe (c);

  // Notify the event consumer they no longer need to observe
  // events from this publisher.
  ::Components::Portico::EventConsumer_var consumer =
    ::Components::Portico::EventConsumer::_narrow (consumer_base);

  if (!::CORBA::is_nil (consumer.in ()))
    consumer->unobserve_object (this->tag_.to_string ()->c_str ());

  return consumer_base;
}

//
// allocate_event
//
template <typename EVENT>
EVENT * Portico_CCM_Publisher_Table_T <EVENT>::allocate_event (void)
{
  return this->factory_->create ();
}

//
// send_event
//
template <typename EVENT>
void Portico_CCM_Publisher_Table_T <EVENT>::send_event (EVENT * ev)
{
  // Cast the event to an Portico_ObjectClass object.
  Portico_ObjectClass * objclass = dynamic_cast <Portico_ObjectClass *> (ev);

  if (0 == objclass)
    throw ::CORBA::INTERNAL ();

  // Write the attributes.
  const RTI::ULong count = Portico_ObjectClass_Trait_T <EVENT>::attr_count;
  std::auto_ptr <RTI::AttributeHandleValuePairSet> attrs (RTI::AttributeSetFactory::create (count));
  objclass->__hla_write_attributes (*attrs);

  // Update the attribute value. We do not have to iterate over all
  // consumers that have subscribed. This is because updating the
  // values of this object instance will cause the update to propagate
  // to all federates. The federates will then forward the information
  // to components that are observing the event (i.e., have an explicit
  // connection) in the deployment.
  this->rtiamb_->tick ();

  try
  {
    if (0 != this->rtiamb_ && 0 != this->obj_handle_)
      this->rtiamb_->updateAttributeValues (this->obj_handle_, *attrs, "Hi!");
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR, "sooo\n"));
  }
}
