// $Id$

//
// CUTS_OpenSplice_CCM_Subscriber_T
//
template <typename EVENT>
CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::CUTS_OpenSplice_CCM_Subscriber_T (void)
{

}

//
// ~CUTS_OpenSplice_CCM_Subscriber_T
//
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
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - requesting topic description from consumer\n")));

  ::Components::OpenSplice::EventConsumer_var consumer =
      ::Components::OpenSplice::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an OpenSplice consumer\n")));

    throw ::CORBA::INTERNAL ();
  }

  ::Components::OpenSplice::TopicDescription_var
      topic_desc = consumer->topic_description ();

  // Make sure the type is registered with the participant.
  typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_type * type_temp = 0;

  ACE_NEW_THROW_EX (type_temp,
                    typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_type (),
                    ::CORBA::NO_MEMORY ());

  typename CUTS_OpenSplice_Traits_T <EVENT>::dds_typesupport_var_type type_var (type_temp);

  int retval =
    this->endpoint_.open (this->participant_.in (),
                          type_var.in (),
                          topic_desc->type_name.in (),
                          topic_desc->name.in ());

  if (0 != retval)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open underlying ")
                ACE_TEXT ("endpoint for publisher\n")));

    throw ::CORBA::INTERNAL ();
  }

  // Pass control the base class.
  CUTS_OpenSplice_CCM_Subscriber::connect (consumer.in ());

  this->writer_ =
    CUTS_OpenSplice_Traits_T <EVENT>::writer_type::_narrow (this->abstract_writer_.in ());
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
  //*ev >>= dds_event;

  this->send_event (ev->content ());
}

//                                                                                                                                                                                 // send_event
//
template <typename EVENT>
void CUTS_OpenSplice_CCM_Subscriber_T <EVENT>::
send_event (typename traits_type::dds_event_type & ev)
{
  ::DDS::ReturnCode_t status = this->writer_->write (ev, ::DDS::HANDLE_NIL);
  ACE_UNUSED_ARG (status);
}
