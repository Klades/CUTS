// $Id$

template <typename EVENT>
CUTS_RTIDDS_CCM_Subscriber_T <EVENT>::CUTS_RTIDDS_CCM_Subscriber_T (void)
{

}

template <typename EVENT>
CUTS_RTIDDS_CCM_Subscriber_T <EVENT>::~CUTS_RTIDDS_CCM_Subscriber_T (void)
{

}

//
// connect
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Subscriber_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  // Get the DDS topic string from the consumer.
  ::Components::RTIDDS::EventConsumer_var consumer =
      ::Components::RTIDDS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
    {
      ACE_ERROR ((LM_ERROR,
      "%T (%t) - %M - object is not an RTIDDS consumer\n"));

      throw ::CORBA::INTERNAL ();
    }

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - requesting topic description")
              ACE_TEXT (" from consumer\n")));

  ::Components::RTIDDS::TopicDescription_var topic_desc = consumer->topic_description ();


  // First, let's make sure the typename is registered with the
  // paricipant. Otherwise, would could have problems with RTIDDS.

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - registering type %s with subscriber\n"),
              topic_desc->type_name.in ()));

  typedef typename CUTS_RTIDDS_Traits_T <EVENT>::dds_typesupport_type dds_typesupport_type;

  ::DDS_ReturnCode_t retcode =
    dds_typesupport_type::register_type (this->participant_,
                                         topic_desc->type_name.in ());

  if (DDS_RETCODE_OK != retcode)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s\n"),
                topic_desc->type_name.in ()));

    throw ::CORBA::INTERNAL ();
  }

  int retval = this->endpoint_.open (this->participant_,
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
  CUTS_RTIDDS_CCM_Subscriber::connect (consumer.in ());
  this->writer_ = CUTS_RTIDDS_Traits_T <EVENT>::writer_type::narrow (this->abstract_writer_);
}

//
// send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Subscriber_T <EVENT>::
send_event (typename traits_type::corba_event_type * ev)
{
  // Convert the CORBA event into a DDS event.
  typename traits_type::dds_event_type dds_event;
  *ev >>= dds_event;

  this->send_event (dds_event);
}

//                                                                                                                                                                                 // send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Subscriber_T <EVENT>::
send_event (typename traits_type::dds_event_type & ev)
{
  ::DDS_ReturnCode_t status = this->writer_->write (ev, DDS_HANDLE_NIL);
  ACE_UNUSED_ARG (status);
}
