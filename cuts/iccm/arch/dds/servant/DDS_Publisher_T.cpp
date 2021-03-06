// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Publisher_T.inl"
#endif

namespace iCCM
{

//
// configure
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::
configure (publisher_ptr_type publisher,
           const datawriterqos_type & datawriter_qos,
           const topicqos_type & topic_qos,
           const char * topic_name,
           bool isinstance)
{
  // Make sure the type is registered with the participant. This requires
  // us allocating a type support object from the event. Then, we are
  // going to use the type support to get the actual type name. Finally,
  // we are going to register to type with the publisher's participant.
  typedef typename T::domainparticipant_var_type domainparticipant_var_type;
  typedef typename T::returncode_type returncode_type;
  typedef typename event_traits_type::dds_typesupport_type dds_typesupport_type;
  typedef typename T::topic_var_type topic_var_type;

  ACE_CString type_name;
  domainparticipant_var_type participant = publisher->get_participant ();
  returncode_type status = T::template register_type <dds_typesupport_type> (participant, type_name);

  if (status != 0)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to register type [status=%d]\n"),
                status));

    throw ::CORBA::INTERNAL ();
  }

  ACE_CString normalized (topic_name);
  std::replace (normalized.begin (), normalized.end (), '.', '_');

  // Create a topic for the publisher. This will be a combination of the
  // type we just registered and the provided topic name.
  topic_var_type topic =
    participant->create_topic (normalized.c_str (),
                               type_name.c_str (),
                               topic_qos,
                               0, /* ::DDS::TopicListener::_nil () */
                               T::STATUS_MASK_NONE);

  // Finally, pass control to the base class. It will finish configuring
  // this provider object.
  DDS_Publisher <T>::configure (publisher, datawriter_qos, topic);

  // Store the concrete writer type and register an instance.
  writer_type * writer = 0;
  if (isinstance)
  {
    typedef DDS_Registered_Instance_Writer_T <T, EVENT> WRITER_TYPE;
    ACE_NEW_THROW_EX (writer,
                      WRITER_TYPE (this->abs_writer_),
                      ::CORBA::NO_MEMORY ());
  }
  else
  {
    typedef DDS_Unregistered_Instance_Writer_T <T, EVENT> WRITER_TYPE;
    ACE_NEW_THROW_EX (writer,
                      WRITER_TYPE (this->abs_writer_),
                      ::CORBA::NO_MEMORY ());
  }

  this->writer_.reset (writer);
}

//
// connect
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::connect (::Components::EventConsumerBase_ptr p)
{
  // Narrow this to an DDS event consumer. We are then going to
  // tell the consumer what topic to listen.
  ::Components::DDS::EventConsumer_var consumer =
      ::Components::DDS::EventConsumer::_narrow (p);

  if (::CORBA::is_nil (consumer.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an DDS ")
                ACE_TEXT ("event consumer\n")));

    throw ::CORBA::INTERNAL ();
  }

  // Add a topic to the consumer.
  typedef typename T::topic_var_type topic_var_type;

  topic_var_type topic = this->abs_writer_->get_topic ();
  consumer->add_topic (topic->get_name ());
}

//
// activate
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::activate (void)
{
  if (this->writer_.get () != 0)
    this->writer_->activate ();
}

//
// passivate
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::passivate (void)
{
  if (this->writer_.get () != 0)
    this->writer_->passivate ();
}

//
// send_event
//
template <typename T, typename EVENT>
void DDS_Publisher_T <T, EVENT>::send_event (::Components::EventBase * base)
{
  EVENT * ev = dynamic_cast < EVENT * > (base);
  return this->writer_->send_event (ev);
}

}
