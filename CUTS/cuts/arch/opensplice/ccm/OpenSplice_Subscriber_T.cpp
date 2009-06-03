// $Id$

template <typename EVENT>
CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::
CUTS_OpenSplice_CCM_Subscriber_T (::DDS::DomainParticipant_ptr participant)
  : participant_ (participant)
{

}

template <typename EVENT>
CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::~CUTS_OpenSplice_CCM_Subscriber_T (void)
{

}

//
// connect
//
template <typename EVENT>
void CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  // Get the DDS topic string from the consumer.
  ::Components::OpenSplice::EventConsumer_var consumer =
    ::Components::OpenSplice::EventConsumer::_narrow (p);

  ::CORBA::String_var topic = consumer->topic ();

  // Make sure the type is registered with the participant.
  // Register the type for with the participant. This should really
  // be done in the servant's code!!
  typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_type * type_temp = 0;

  ACE_NEW_THROW_EX (type_temp,
                    typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_var_type type_var (type_temp);
  ::CORBA::String_var type_name = type_var->get_type_name ();

  ::DDS::ReturnCode_t status = 
      type_var->register_type (this->participant_.in (), type_name.in ());

  // Next, we can create the topic for the event consumer.
  this->dds_topic_ = 
    this->participant_->create_topic (topic.in (),
				      type_name.in (),
				      TOPIC_QOS_DEFAULT,
				      ::DDS::TopicListener::_nil (),
				      ::DDS::ANY_STATUS);

  // Now, register for the topic. Subscribing an event consumer to
  // will enable a component to register for this topic.
  this->publisher_ = 
    this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
					  ::DDS::PublisherListener::_nil (),
					  ::DDS::ANY_STATUS);

  // The last part is to create a data reader.
  ::DDS::DataWriter_var writer =
      this->publisher_->create_datawriter (this->dds_topic_.in (),
					   DATAWRITER_QOS_DEFAULT,
					   0,
					   ::DDS::ANY_STATUS);

  this->writer_ =
    CUTS_OpenSplice_Traits_T <EVENT>::writer_type::_narrow (writer.in ());

  ACE_UNUSED_ARG (status);
}

//
// send_event
//
template <typename EVENT>
void CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::
send_event (typename traits_type::corba_event_type * ev)
{
  // Convert the CORBA event into a DDS event.
  typename traits_type::dds_event_type dds_event;
  *ev >>= dds_event;

  // Send the event to the DDS server.
  ::DDS::ReturnCode_t status 
      = this->writer_->write (dds_event, ::DDS::HANDLE_NIL);

  ACE_UNUSED_ARG (status);
}

//
// disconnect
//
template <typename EVENT>
::Components::EventConsumerBase_ptr 
CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::disconnect (void)
{
  // We should unregister our topic since we can't consume anymore!!

  return this->consumer_._retn ();
}
