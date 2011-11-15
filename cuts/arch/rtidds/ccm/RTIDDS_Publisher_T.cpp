// $Id$

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Publisher_T.inl"
#endif

//
// connect
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  this->consumer_ = ::Components::RTIDDS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (this->consumer_.in ()))
    throw ::Components::InvalidConnection ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - requesting topic description")
              ACE_TEXT (" from consumer\n")));

  // Get the DDS topic string from the consumer.
  using ::Components::RTIDDS::TopicDescription_var;
  TopicDescription_var topic_desc = this->consumer_->topic_description ();

  // First, let's make sure the typename is registered with the
  // paricipant. Otherwise, would could have problems with RTIDDS.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - registering type %s with subscriber\n"),
              topic_desc->type_name.in ()));

  // Register the type with this participant.
  typedef typename CUTS_RTIDDS_Traits_T <EVENT>::dds_typesupport_type dds_typesupport_type;

  ::DDSDomainParticipant * participant = this->publisher_->get_participant ();

  ::DDS_ReturnCode_t retcode =
    dds_typesupport_type::register_type (participant,
                                         topic_desc->type_name.in ());

  if (DDS_RETCODE_OK != retcode)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type %s\n"),
                topic_desc->type_name.in ()));

    throw ::CORBA::INTERNAL ();
  }

  int retval = this->endpoint_.open (participant,
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
  CUTS_RTIDDS_CCM_Publisher::connect (this->consumer_.in ());

  // Store the concrete version of the writer type.
  typedef typename CUTS_RTIDDS_Traits_T <EVENT>::writer_type writer_type;
  this->writer_ = writer_type::narrow (this->abstract_writer_);
}

//
// send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Publisher_T <EVENT>::
send_event (typename traits_type::corba_event_type * ev)
{
  this->send_event (ev->content ());
}

//                                                                                                                                                                                 // send_event
// send_event
//
template <typename EVENT>
void CUTS_RTIDDS_CCM_Publisher_T <EVENT>::
send_event (typename traits_type::dds_event_type & ev)
{
  ::DDS_ReturnCode_t status = this->writer_->write (ev, DDS_HANDLE_NIL);

  if (DDS_RETCODE_OK != status)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to write data [retcode=%d]\n"),
                status));
}
